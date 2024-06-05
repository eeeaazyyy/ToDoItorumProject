#include "TaskPage.h"

#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDateTime>
#include <QKeyEvent>
#include <QFile>


#include "TaskListView.h"
#include "TaskListModel.h"
#include "NotesListModel.h"


TaskPage::TaskPage(NotesListItem* Note, QWidget* parent) 
	: NoteItem(Note), QWidget(parent)
{

	initStyle();
	initForm();
	initLayout();
	setInfo();
	
	connect(btnBack, &QPushButton::clicked, this, &TaskPage::slotBtnBackClicked);
}


TaskPage::TaskPage(QWidget* parent) : QWidget(parent), NoteItem(new NotesListItem("Title.."))
{
	initStyle();
	initForm();
	initLayout();
	setInfo();
	
	connect(btnBack, &QPushButton::clicked, this, &TaskPage::slotBtnBackClicked);
}

TaskPage::~TaskPage()
{
	qDebug() << "Delete page";
}

void TaskPage::initStyle()
{
	QFile file(":/styles/TaskPage_style.qss", this);
	file.open(QFile::ReadOnly);
	QString styleSheet = QLatin1String(file.readAll());
	file.close();
	this->setStyleSheet(styleSheet);
}

void TaskPage::initForm()
{

	btnBack = new QPushButton("", this);
	btnBack->setFixedSize(32, 32);
	btnBack->setObjectName("btnBack");

	ListTasks = new TaskListView(this);
	ListTasks->setObjectName("ListTasks");

	lineEdTitleNote = new QLineEdit(this);
	lineEdTitleNote->setObjectName("lineEdTitleNote");
}

void TaskPage::initLayout()
{
	grMainLayout = new QGridLayout(this);
	grMainLayout->addWidget(btnBack, 0, 0);
	grMainLayout->addWidget(lineEdTitleNote, 0, 1, 1, 2);
	grMainLayout->addWidget(ListTasks, 1, 1, 1, 2);

	setLayout(grMainLayout);
}

void TaskPage::setInfo()
{
	lineEdTitleNote->setText(NoteItem->getTitleNote());
	for (auto iterTask : NoteItem->getTask())
	{
		ListTasks->addTask(iterTask);
	}

}

void TaskPage::slotBtnBackClicked()
{
	QString Title = lineEdTitleNote->text();
	ListTasks->getItemsTask();
	
	NoteItem->setInfoNotesItem(Title, QDateTime::currentDateTime().toString(), ListTasks->getItemsTask());
	emit noteCreated(Title, ListTasks->getItemsTask());
	emit finished();
}

void TaskPage::slotBtnBackCreatableItem()
{
	QString Title = lineEdTitleNote->text();
	ListTasks->getItemsTask();
	NoteItem->setInfoNotesItem(Title, QDateTime::currentDateTime().toString(), ListTasks->getItemsTask());
	emit finished();
}

void TaskPage::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_Enter:
	case Qt::Key_Return:
	{
		ListTasks->slotAddTaskByKey();
		event->accept();
		break;
	}
	default:
		QWidget::keyPressEvent(event);
		break;
	}
}
