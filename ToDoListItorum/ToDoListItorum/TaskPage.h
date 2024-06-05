#pragma once
#include <QObject>
#include <QWidget>

#include "NotesListModel.h"

class QPushButton;
class QLineEdit;
class QGridLayout;
class TaskListView;

struct TaskData;

/*
* A dialog widget that provides note data
*/
class TaskPage : public QWidget
{
	Q_OBJECT
public:
	TaskPage(NotesListItem* Note, QWidget* parent = nullptr);
	TaskPage(QWidget* parent = nullptr);
	~TaskPage();

	
private:
	NotesListItem*	NoteItem;
	QPushButton*	btnBack;
	QLineEdit*		lineEdTitleNote;
	TaskListView*	ListTasks;
	QGridLayout*	grMainLayout;

private:
	void initStyle();
	void initForm();
	void initLayout();
	void setInfo();
private slots:
	void slotBtnBackClicked();
	void slotBtnBackCreatableItem();
signals:
	void noteCreated(const QString& Title, const QList<TaskData*> Tasks);
	void finished();
	void noteUpdate(const QString& Title, const QList<TaskData*> Tasks);
protected:
	void keyPressEvent(QKeyEvent* event) override;
};