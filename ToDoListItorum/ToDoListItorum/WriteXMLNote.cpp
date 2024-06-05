#include "WriteXMLNote.h"

#include "NotesListModel.h"
#include "TaskNoteItem.h"

#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QThread>
#include <QDateTime>
#include <QDomDocument>

WriteXMLNote::WriteXMLNote(QObject* parent) : QObject(parent)
{
}

WriteXMLNote::~WriteXMLNote()
{
}


void WriteXMLNote::loadXMLFile(const QString& fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Error opening file:" << file.errorString();
        return;
    }

    QString Title{};
    QList<TaskData*> dataList{};


    QXmlStreamReader xmlReader(&file);
    while (!xmlReader.atEnd() && !xmlReader.hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader.readNext();
        if (token == QXmlStreamReader::StartElement)
        {
            QString name = xmlReader.name().toString();
            if (name == "Title")
            {
                QXmlStreamAttributes attrs = xmlReader.attributes();
                if (attrs.hasAttribute("Title"))
                {
                    Title = attrs.value("Title").toString();
                }
            }
            else if (name == "Task")
            {
                QXmlStreamAttributes attrs = xmlReader.attributes();
                // Проверяем наличие интересующих нас атрибутов
                
                if (attrs.hasAttribute("ChecKState"))
                {

                    qDebug() << "ChecKState attribute value:" << attrs.value("ChecKState").toString();
                }
                if (attrs.hasAttribute("Text"))
                {
                    qDebug() << "Text attribute value:" << attrs.value("Text").toString();
                }
                Qt::CheckState state = attrs.value("ChecKState").toString() == "true" ? Qt::Checked : Qt::Unchecked;
                QString Text = attrs.value("Text").toString();
                TaskData* item = new TaskData{ Text, state };
                dataList.append(item);
                // Теперь читаем текст элемента
                qDebug() << name << " " << xmlReader.readElementText();

            }
      
        }
    }

    if (xmlReader.hasError())
    {
        qDebug() << "Error:" << xmlReader.errorString();
        return;
    }
    file.close();
    emit noteLoaded(Title, dataList);
}

void WriteXMLNote::writeXMLFile(NotesListItem* item, const QString& fileName)
{
    QFile xmlFile(fileName);
    if (!xmlFile.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << "Already opened or there is another issue";
        xmlFile.close();
    }
    QTextStream xmlContent(&xmlFile);

    QDomDocument document;

    //make the root element
    QDomElement root = document.createElement("NoteList");
    //add it to document
    document.appendChild(root);

    QDomElement Note = document.createElement("Title");
    Note.setAttribute("Title", item->getTitleNote());
    root.appendChild(Note);


    Note = document.createElement("Tasks");
    
    QList<TaskData*> data = item->getTask();
    for (auto task : data)
    {
        QDomElement tag = document.createElement("Task");
        tag.setAttribute("ChecKState", task->TaskState == 0 ? QStringLiteral("false") : QStringLiteral("true"));
        tag.setAttribute("Text", task->Text);
        Note.appendChild(tag);
    }
    root.appendChild(Note);
    xmlContent << document.toString();
    qDebug() << "Successful save: " << xmlFile.fileName();
    xmlFile.close();
    emit signalFinished();
}