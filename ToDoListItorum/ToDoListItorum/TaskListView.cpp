
#include <QStandardItemModel>
#include <QKeyEvent>
#include <QItemDelegate>

#include "TaskListView.h"
#include "NotesListModel.h"


// Constructor View 
TaskListView::TaskListView(QWidget* parent) : QListView(parent)
{
	this->setFont(QFont("MSShellDlg 2", 12));
	modelStandard = new TaskListModel(this);
	this->setModel(modelStandard);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

// Destructor
TaskListView::~TaskListView()
{
}

/*
* Overriding the keyPressEvent method to add a task by clicking a button
* or delete task
*/
void TaskListView::keyPressEvent(QKeyEvent* event)
{
	switch (event->key())
	{
	case Qt::Key_Enter:
	case Qt::Key_Return:
	{
		slotAddTaskByKey();
		event->accept();
		break;
	}
	case Qt::Key_Backspace:
	{
			QModelIndex index = currentIndex(); 
			if (index.isValid())
			{
				int row = index.row();
				model()->removeRows(row, 0);
				emit dataChanged(index, index); 
				
			}
			event->ignore();
	}
	default:
		QListView::keyPressEvent(event);
		break;
	}
  
}
/*
* method add task in model by TaskData
*/
void TaskListView::addTask(TaskData* task)
{
	modelStandard->appendTask(task);
	setCurrentIndex(modelStandard->indexByItem(task));
}

/*
* Get all tasks from model
*/
QList<TaskData*> TaskListView::getItemsTask()
{
	return modelStandard->getItems();
}

/*
* Method add task in model FOR keyPressEvent
*/
void TaskListView::slotAddTaskByKey()
{
	TaskData* item = new TaskData{ "", Qt::Unchecked };
	modelStandard->appendTask(item);
	setCurrentIndex(modelStandard->indexByItem(item));
	edit(modelStandard->indexByItem(item));

}