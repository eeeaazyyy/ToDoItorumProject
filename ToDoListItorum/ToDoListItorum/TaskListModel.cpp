#include "TaskListModel.h"
#include "NotesListModel.h"

TaskListModel::TaskListModel(QObject* parent)
{
}

TaskListModel::~TaskListModel()
{
}

int TaskListModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

int TaskListModel::rowCount(const QModelIndex& parent) const
{
	return m_data.size();
}

// View data item
QVariant TaskListModel::data(const QModelIndex& index, int role) const
{
	if (m_data.isEmpty())
		return QVariant();
	switch (role)
	{
	case NoteTypeData::TextNote:
		return m_data.at(index.row())->Text;
	case NoteTypeData::CheckState:
		return m_data.at(index.row())->TaskState;
	case Qt::DisplayRole:
	case Qt::EditRole:
		return m_data.at(index.row())->Text;
	default:
		return QVariant();
	}
}
/*
* Set Data item & role (text & check/uncheck)
*/
bool TaskListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (m_data.isEmpty())
		return false;
	
	if (role == NoteTypeData::TextNote || role == Qt::DisplayRole)
	{
		
		m_data.at(index.row())->Text = value.toString();
		emit dataChanged(index, index, { role });
		return true;
	}
	else if (role == Qt::EditRole)
	{
		
		m_data.at(index.row())->Text = value.toString();
		emit dataChanged(index, index, { role });
		return true;
	}
	else if (role == Qt::CheckStateRole)
	{
		m_data.at(index.row())->TaskState = (m_data.at(index.row())->TaskState == Qt::Checked) ? Qt::Unchecked : Qt::Checked;
		emit dataChanged(index, index, { role });
		return true;
	}
	return false;
}

QModelIndex TaskListModel::index(int row, int column, const QModelIndex& parent) const
{
	return createIndex(row, column, (void*)&m_data[row]);
}

QModelIndex TaskListModel::parent(const QModelIndex& index) const
{
	return QModelIndex();
}

/*
* Remove ONE row at selected
*/
bool TaskListModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(rows);
	qDebug() << "Remove rows";
	beginRemoveRows(parent, position, position);
	TaskData* itemToRemove = m_data.at(position);
	m_data.removeAt(position);
	endRemoveRows();

	return true; // ¬озвращаем true, если удаление прошло успешно
}

/*
* Method can append task on TaskListView with custom parameters
*/
void TaskListModel::appendTask(TaskData* TaskItem)
{
	
	int row = m_data.size();
	beginInsertRows(QModelIndex(), row, row);
	insertRow(row);

	m_data.append(TaskItem);
	setData(index(row, 0, QModelIndex()), TaskItem->Text, NoteTypeData::TextNote);

	endInsertRows();
	emit layoutChanged();
}

/*
* Create index by item
*/
QModelIndex TaskListModel::indexByItem(TaskData* TaskItem) const
{
	int index = m_data.indexOf(TaskItem);
	return createIndex(index, 0, (void*)&m_data[index]);
}

/*
* Set Custom flags for items
*/
Qt::ItemFlags TaskListModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsEditable | QAbstractItemModel::flags(index) | Qt::ItemIsUserCheckable;
}

/*
* Get all items in model
*/
QList<TaskData*> TaskListModel::getItems() const
{
	QList<TaskData*> m_dataCopy{};
	m_dataCopy = m_data;
	return m_dataCopy;
}
