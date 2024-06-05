#pragma once
#include <QAbstractItemModel>

class NotesListItem;
struct TaskData;


class TaskListModel : public QAbstractItemModel
{
	Q_OBJECT
private:
	QList<TaskData*> m_data; // root data
public:
	TaskListModel(QObject* parent = nullptr);
	~TaskListModel();

public:

	virtual int columnCount(const QModelIndex& parent) const;
	virtual int rowCount(const QModelIndex& parent) const;
	virtual QVariant data(const QModelIndex& index, int role) const;

	virtual bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
	virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
	virtual QModelIndex parent(const QModelIndex& index) const;
	virtual bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;


	// custom methods
	void appendTask(TaskData* TaskItem); // add new task in TaskPage

	QModelIndex		 indexByItem(TaskData* TaskItem) const;	// get item
	Qt::ItemFlags	 flags(const QModelIndex& index) const;	// set enabled & editable & checked
	QList<TaskData*> getItems() const;						// get all items

};