#pragma once
#include <QListView>
#include "TaskListModel.h"

class QStandardItemModel;

/*
* A model that allows you to display all completed/unfulfilled tasks in a note
*/
class TaskListView : public QListView
{
	Q_OBJECT
public:
	TaskListView(QWidget* parent = nullptr);
	~TaskListView();

public:
	QList<TaskData*> getItemsTask();
private:
	TaskListModel* modelStandard;
protected:
	void keyPressEvent(QKeyEvent* event) override;
public slots:
	void slotAddTaskByKey(); 
public:
	void addTask(TaskData* task);
};