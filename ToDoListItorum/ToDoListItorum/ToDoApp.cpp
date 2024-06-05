#include "ToDoApp.h"

#include <QGroupBox>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QDateTime>
#include <QMutex>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QFileDialog>
#include <QApplication>

#include "TaskPage.h"

ToDoApp::ToDoApp(QWidget* parent) : QMainWindow(parent)
{	
	resize(750, 400);
	setMinimumSize(700, 400);

	setStyleMainWindow();
	initWidgets();
	initLayout();
	initMainWidget();
		
	// Connections
	connect(NotesList.data(),	&NotesListView::signalNoteSelected, this,				 &ToDoApp::createPageByNote);
	connect(NotesList.data(),	&NotesListView::signalDeleteItem,	NotesList->model(),	 &QAbstractItemModel::removeRows);
	connect(btnCreateNote,		&QPushButton::clicked,				this,				 &ToDoApp::createPageOfNote);
	connect(NotesList.data(),	&NotesListView::saveItemNote,		this,				 &ToDoApp::slotSaveNote);
	connect(btnMiscOption,		&QPushButton::clicked,				this,				 &ToDoApp::slotOpenNote);
}

ToDoApp::~ToDoApp()
{
	emit finishedApp();
}

void ToDoApp::createPageOfNote()
{
	TaskPage* PageOfTask = new TaskPage(mainStackWdg);
	mainStackWdg->addWidget(PageOfTask);
	
	
	connect(PageOfTask, &TaskPage::finished, [this, PageOfTask]()
			{
				mainStackWdg->setCurrentIndex(0); 
				mainStackWdg->removeWidget(PageOfTask);
				PageOfTask->deleteLater();
				
});
	connect(PageOfTask, &TaskPage::noteCreated, NotesList.data(), &NotesListView::addNote);
	mainStackWdg->setCurrentIndex(1);
}

void ToDoApp::setStyleMainWindow()
{
	//Set Style for ToDoApp
	QFile file(":/styles/ToDoApp_style.qss", this);
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	this->setStyleSheet(styleSheet);
	file.close();
}

void ToDoApp::initWidgets()
{
	// Create widgets
	NotesList.reset(new NotesListView(this));

	// Set style for create button
	btnCreateNote = new QPushButton(this);
	btnCreateNote->setObjectName("btnCreateNote");
	btnCreateNote->setToolTip("Create Note..");
	btnCreateNote->setFixedSize(30, 30);
	btnCreateNote->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);


	// Set Style for loaded button
	btnMiscOption = new QPushButton(this);
	btnMiscOption->setToolTip("Load Note..");
	btnMiscOption->setObjectName("btnMiscOption");
	btnMiscOption->setFixedSize(28, 28);
	btnMiscOption->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	// Central widget
	mainSettingsWidget = new QWidget(this);
	mainSettingsWidget->setMinimumSize(600, 350);

	labelNote = new QLabel("Notes", mainSettingsWidget);
	labelNote->setObjectName("labelNote");

	labelNote->setAlignment(Qt::AlignHCenter);
	labelNote->setMinimumSize(140, 28);
	labelNote->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);	
}

void ToDoApp::initLayout()
{
	layoutMainSettWdg = new QGridLayout(mainSettingsWidget);
	layoutMainSettWdg->setColumnStretch(1, 1);
	layoutMainSettWdg->setColumnMinimumWidth(0, 28);
	// add widget on layout

	layoutMainSettWdg->addWidget(labelNote, 0, 1);
	layoutMainSettWdg->addWidget(btnMiscOption, 0, 2);
	layoutMainSettWdg->addWidget(btnCreateNote, 2, 2, Qt::AlignRight);
	layoutMainSettWdg->addWidget(NotesList.data(), 1, 0, 1, 3);
	mainSettingsWidget->setLayout(layoutMainSettWdg);
}

void ToDoApp::initMainWidget()
{
	// add stackWidget
	mainStackWdg = new QStackedWidget(this);
	mainStackWdg->addWidget(mainSettingsWidget);
	mainStackWdg->layout()->setAlignment(mainSettingsWidget, Qt::AlignHCenter);
	mainStackWdg->setCurrentIndex(0);

	// spacers
	QSpacerItem* spacerLeft	 = new QSpacerItem(40, 30, QSizePolicy::Expanding);
	QSpacerItem* spacerRight = new QSpacerItem(40, 30, QSizePolicy::Expanding);

	// add spacer and main widget in layout
	QWidget* mainWidget = new QWidget(this);

	QHBoxLayout* layoutMainWidget = new QHBoxLayout(mainWidget);

	layoutMainWidget->addSpacerItem(spacerLeft);
	layoutMainWidget->addWidget(mainStackWdg);
	layoutMainWidget->addSpacerItem(spacerRight);

	mainWidget->setLayout(layoutMainWidget);

	this->setCentralWidget(mainWidget);
	this->layout()->setAlignment(mainStackWdg, Qt::AlignHCenter);
}

void ToDoApp::createPageByNote(NotesListItem* Item)
{
	TaskPage* pageNote = new TaskPage(Item, mainStackWdg);
	mainStackWdg->addWidget(pageNote);

	mainStackWdg->setCurrentIndex(1);
	connect(pageNote, &TaskPage::finished, [this, pageNote]() {mainStackWdg->setCurrentIndex(0); pageNote->deleteLater(); });
}

void ToDoApp::slotSaveNote(NotesListItem* Item)
{
	QString fileName = QFileDialog::getSaveFileName(this, "Save File",
													QApplication::applicationDirPath(),
													"Text Files (*.xml);;All Files (*)");
	if (fileName.isEmpty())
		return;
	emit saveFile(Item, fileName);
}

void ToDoApp::slotOpenNote()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open Note",
													QApplication::applicationDirPath(),
													"Text Files (*.xml);;All Files (*)");
	if (fileName.isEmpty())
		return;
	emit loadFile(fileName);
}


void ToDoApp::loadNoteFile(const QString& title, const QList<TaskData*>data)
{
	NotesList.data()->addNote(title, data);
}