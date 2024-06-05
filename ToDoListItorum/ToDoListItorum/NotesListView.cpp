#include "NotesListView.h"
#include "ListViewDelegate.h"

#include <QStandardItemModel>
#include <QDateTime>
#include <QMenu>
#include <QAction>
#include <QMouseEvent>
#include <QMutex>


NotesListView::NotesListView(QWidget* parent) 
	: QListView(parent)
{	
	// Set custom style view
	QPalette listPalette(palette());
	setCustomColorPalette(listPalette);
	
	this->setFrameStyle(QFrame::NoFrame);
	this->setPalette(listPalette);
	this->setFont(QFont("MSShellDlg 2", 12));
	
	// set model & delegate view
	auto* ViewDelegate = new ListViewDelegate(this);
	ViewDelegate->setContentsMargins(8, 8, 8, 8);
	ViewDelegate->setHorizontalSpacing(8);
	ViewDelegate->setVerticalSpacing(4);

	this->setItemDelegate(ViewDelegate);
	this->setModel(new NotesListModel(this));
}

NotesListView::~NotesListView()
{
}

// select item in listview
void NotesListView::mouseDoubleClickEvent(QMouseEvent* e)
{
	QModelIndex index = this->indexAt(e->pos());
	QAbstractItemView::mouseDoubleClickEvent(e);
	emit signalNoteSelected(getItem(index));
}

// misc options on right click event
void NotesListView::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		QPoint pos = event->pos();
		showContextMenu(pos);
	}
	else
	{
		QListView::mousePressEvent(event);
	}
}

// add note to list view
void NotesListView::addNote(const QString& Title, const QList<TaskData*> Tasks)
{
	auto* itemModel = new NotesListItem(Title, QDateTime::currentDateTime().toString("dd.MM.yyyy"), Tasks);
	((NotesListModel*)this->model())->appendNote(itemModel);
	this->scrollToBottom();
}

// clear all notes
void NotesListView::clearAll()
{
	((NotesListModel*)this->model())->clear();
}

// get item by index
NotesListItem* NotesListView::getItem(const QModelIndex& index)
{

	if (NotesListItem* item = ((NotesListModel*)this->model())->getItemByIndex(index.row()); item != nullptr)
	{
		return item;
	}
	
	return nullptr;
}

// context menu with "delete" & "save"
void NotesListView::showContextMenu(const QPoint& pos)
{	
	QModelIndex index = indexAt(pos);
	if (!index.isValid()) return;

	QMenu menu;
	QAction saveAction(tr("Save note"));
	QAction removeAction(tr("Delete"));
	

	//connect(&removeAction, &QAction::triggered, [this, index]() {emit signalDeleteItem(index.row(), 1, index); });
	connect(&saveAction, &QAction::triggered, [this, index]()
			{
				QMutex mtx; 
				mtx.lock();
				NotesListItem* item = getItem(index);
				NotesListItem* itemCopy(item);
				emit saveItemNote(itemCopy);
				mtx.unlock();
			});
	connect(&removeAction, &QAction::triggered, [this, index]() {emit signalDeleteItem(index.row(), 1, index); });
	menu.addActions({ &removeAction, &saveAction });
	menu.exec(mapToGlobal(pos));
}

// setcustom colors of palette
void NotesListView::setCustomColorPalette(QPalette& listPalette)
{
	listPalette.setBrush(QPalette::WindowText, QColor("#ffffff"));
	listPalette.setBrush(QPalette::Base, QColor(Qt::transparent));
	listPalette.setBrush(QPalette::Light, QColor("#282828"));
	listPalette.setBrush(QPalette::Midlight, QColor("#D3D6D8"));
	listPalette.setBrush(QPalette::Mid, QColor("#C5C9Cb"));
	listPalette.setBrush(QPalette::Dark, QColor("#9AA0A4"));
	listPalette.setBrush(QPalette::Text, QColor("#616b71"));
	listPalette.setBrush(QPalette::Highlight, QColor("#3c3c3c"));
}

