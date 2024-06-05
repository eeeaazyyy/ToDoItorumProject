#include "NotesListModel.h"
#include <QtAlgorithms>


NotesListModel::NotesListModel(QObject* parent) : QAbstractItemModel(parent),
m_data({})
{

}

NotesListModel::~NotesListModel()
{
	qDeleteAll(m_data);
	m_data.clear();
}

int NotesListModel::columnCount(const QModelIndex& parent) const
{
	return 1;
}

int NotesListModel::rowCount(const QModelIndex& parent) const
{
	return m_data.size();
}

QVariant NotesListModel::data(const QModelIndex& index, int role) const
{
	if (m_data.isEmpty())
		return QVariant();
	switch (role)
	{
	case NoteTypeData::TitleNote:
		return m_data.at(index.row())->TitleNote;

	case NoteTypeData::DateNote:
		return m_data.at(index.row())->dateNote;


	default:
		return QVariant();
	}

}

bool NotesListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	if (m_data.isEmpty())
		return false;


	if (role == NoteTypeData::TitleNote)
	{
		m_data.at(index.row())->TitleNote = value.toString();
		return true;
	}
	else if (role == NoteTypeData::DateNote)
	{
		m_data.at(index.row())->dateNote = value.toString();
		return true;
	}

	return false;
}


QModelIndex NotesListModel::index(int row, int column, const QModelIndex& parent) const
{
	return createIndex(row, column, (void*)&m_data[row]);
}

QModelIndex NotesListModel::parent(const QModelIndex& index) const
{
	return QModelIndex();
}

void NotesListModel::appendNote(NotesListItem* ItemNote)
{
	int row = m_data.size();
	insertRow(row);

	m_data.append(ItemNote);
	setData(index(row, 0, QModelIndex()), ItemNote->TitleNote, NoteTypeData::TitleNote);
	setData(index(row, 0, QModelIndex()), ItemNote->dateNote, NoteTypeData::DateNote);
	emit layoutChanged();

}

void NotesListModel::clear()
{
	beginResetModel();

	removeRows(m_data.size(), 0);
	qDeleteAll(m_data);
	m_data.clear();

	endResetModel();

}

NotesListItem* NotesListModel::getItemByIndex(int row) const
{
	if (row <= m_data.size())
	{
		return m_data[row];
	}
	return nullptr;
}

bool NotesListModel::removeRows(int position, int rows, const QModelIndex& parent)
{
	Q_UNUSED(rows);
	qDebug() << "Remove rows";
	beginRemoveRows(parent, position, position);
	m_data.removeAt(position);
	endRemoveRows();

	return true; // Возвращаем true, если удаление прошло успешно
}


NotesListItem::NotesListItem(const QString& _TitleNote, const QString& _dateNote, const QList<TaskData*> _Tasks)
	: TitleNote(_TitleNote), dateNote(_dateNote), tasksList(_Tasks)
{
}

NotesListItem::~NotesListItem()
{
	dateNote.clear();
	TitleNote.clear();
}

QString NotesListItem::getTitleNote()
{
	return TitleNote;
}

QString NotesListItem::getDateOfNote()
{
	return dateNote;
}

QList<TaskData*> NotesListItem::getTask()
{
	return tasksList;
}

void NotesListItem::setInfoNotesItem(const QString& _Title, 
									 const QString& _dateNote, 
									 QList<TaskData*> task)
{
	TitleNote = std::move(_Title);
	dateNote = std::move(_dateNote);
	tasksList = task;
}


