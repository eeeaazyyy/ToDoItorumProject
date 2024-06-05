#pragma once
#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>


class NotesListItem;
struct TaskData;

class WriteXMLNote : public QObject
{
	Q_OBJECT
public:
	WriteXMLNote(QObject* parent = nullptr);
	~WriteXMLNote();
public slots:
	//void writeXMLFile(NotesListItem* item, const QString& fileName);
	void loadXMLFile(const QString& fileName);
	void writeXMLFile(NotesListItem* item, const QString& fileName);
signals:
	void signalFinished();
	void noteLoaded(const QString& title, const QList<TaskData*>data);

};