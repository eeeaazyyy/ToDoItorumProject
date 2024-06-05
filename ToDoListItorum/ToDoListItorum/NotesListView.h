#pragma once
#include <QListView>
#include "NotesListModel.h"

class NotesListItem;
class QMenu;
class QAction;

class NotesListView : public QListView
{
	Q_OBJECT
public:
	NotesListView(QWidget* parent = nullptr);
	~NotesListView();
private:
	void showContextMenu(const QPoint& pos);
	void setCustomColorPalette(QPalette& listPalette);

protected:
	void mouseDoubleClickEvent(QMouseEvent* e) override;
	void mousePressEvent(QMouseEvent* event) override;
public slots:
	void addNote(const QString& Title, const QList<TaskData*> Tasks);
	void clearAll();
	NotesListItem* getItem(const QModelIndex& index);


signals:
	void signalNoteSelected(NotesListItem* item = nullptr);
	void signalDeleteItem(int pos, int rows, const QModelIndex& parent);
	void saveItemNote(NotesListItem* item);
	
};