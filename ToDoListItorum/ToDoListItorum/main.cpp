// ToDoListItorum.cpp: определяет точку входа для приложения.
//

#include <QApplication>
#include <iostream>
#include <QThread>

#include "ToDoApp.h"
#include "WriteXMLNote.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);
	ToDoApp window;

	QThread* writerThread = new QThread;
	writerThread->setObjectName("Writer thread");

	WriteXMLNote writer;
	writer.moveToThread(writerThread);

	QObject::connect(&window, &ToDoApp::saveFile, &writer, &WriteXMLNote::writeXMLFile);
	QObject::connect(&window, &ToDoApp::loadFile, &writer, &WriteXMLNote::loadXMLFile);
	QObject::connect(&writer, &WriteXMLNote::noteLoaded, &window, &ToDoApp::loadNoteFile);

	QObject::connect(&window, &ToDoApp::finishedApp, writerThread, &QThread::quit);
	QObject::connect(writerThread, &QThread::finished, writerThread, &QThread::deleteLater);

	writerThread->start();

	window.show();
	return app.exec();
}
