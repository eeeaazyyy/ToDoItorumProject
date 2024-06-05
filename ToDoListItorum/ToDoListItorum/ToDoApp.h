#pragma once
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QScopedPointer>
#include <QThread>

#include "NotesListView.h"
#include "WriteXMLNote.h"

class QGridLayout;
class QLabel;

struct TaskData;
class NotesListItem;


class ToDoApp : public QMainWindow
{
	Q_OBJECT
public:
	ToDoApp(QWidget* parent = nullptr);
	~ToDoApp();

private:
	QPushButton* btnCreateNote, *btnMiscOption;
	QWidget* mainSettingsWidget;
	QStackedWidget* mainStackWdg;
	QLabel* labelNote;
	QGridLayout* layoutMainSettWdg;
	QScopedPointer<NotesListView> NotesList;

private:
	void setStyleMainWindow();
	void initWidgets();
	void initLayout();
	void initMainWidget();
public slots:
	void loadNoteFile(const QString& title, const QList<TaskData*>data);

private slots:
	void createPageOfNote();
	void createPageByNote(NotesListItem* Item);
	void slotSaveNote(NotesListItem* Item);
	void slotOpenNote();
	
signals:
	void saveFile(NotesListItem* item, const QString& fileName);
	void loadFile(const QString& fileName);
	void finishedApp();
};