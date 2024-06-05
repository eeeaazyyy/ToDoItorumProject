#pragma once

#include <QObject>
#include <QAbstractItemModel>

#include "TaskNoteItem.h"

class TaskListModel;

enum NoteTypeData
{
	TitleNote = Qt::DisplayRole,
	DateNote =  Qt::UserRole,
	CheckState = Qt::CheckStateRole,
	TextNote =  257
};


class NotesListItem {
public: 
	NotesListItem(const QString& TitleNote, 
				  const QString& _dateNote = QString(), 
				  const QList<TaskData*> task = {});
	~NotesListItem();
	NotesListItem(const NotesListItem&) = default;
	
public:
	QString getTitleNote();
	QString getDateOfNote();
	QList<TaskData*> getTask();

	void setInfoNotesItem(const QString& _Title, const QString& _dateNote, QList<TaskData*> task);
private:
	QString TitleNote;
	QString dateNote;
	QList<TaskData*> tasksList;

	friend class NotesListModel;
	friend class TaskListModel;
};


class NotesListModel : public QAbstractItemModel
{
	Q_OBJECT
	QList<NotesListItem*> m_data;
public:
	NotesListModel(QObject* parent = nullptr);
	~NotesListModel();


	// Model interface implementation
	virtual int columnCount(const QModelIndex& parent) const;
	virtual int rowCount(const QModelIndex& parent) const;

	virtual QVariant data(const QModelIndex& index, int role) const;
	virtual bool	 setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

	virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
	virtual QModelIndex parent(const QModelIndex& index) const;

	virtual bool removeRows(int position, int rows, const QModelIndex& parent = QModelIndex()) override;

	// customs methods
	virtual void appendNote(NotesListItem* ItemNote = nullptr);
	virtual void clear();
	virtual NotesListItem* getItemByIndex(int row) const;
};