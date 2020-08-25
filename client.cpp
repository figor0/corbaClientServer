#include <QCoreApplication>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <fstream>
#include <iostream>
#include <CORBA.h>

#include<ModelManager.h>

int main(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;

	CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
	auto corba_loader_ptr = std::make_shared<CorbaLoader>(orb);
	ModelManager model_manager(corba_loader_ptr);
	model_manager.registration(engine.rootContext(), "entries", "entries_manager");

	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);
	return app.exec();
}
