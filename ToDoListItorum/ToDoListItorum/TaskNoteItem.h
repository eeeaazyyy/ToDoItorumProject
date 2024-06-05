#pragma once
#include <QString>
#include <QObject>

/*
* root item in task
* its has: 
* Text - Text of task
* TaskState - check/unchek of task
*/
struct TaskData {
	QString Text;
	Qt::CheckState TaskState;
};
