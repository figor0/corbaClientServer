#include <QCoreApplication>
#include <QQmlContext>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <fstream>
#include <iostream>
#include <CORBA.h>
#include <APhonesModel.h>
#include <EntriesModel.h>

#include <memory>
#include <ModelManager.h>
#include <APhonesModelManager.h>

void registration(APhonesModel* model_ptr,
				  const QString& model_name,
				  APhonesModelManager* manager_ptr,
				  const QString& manager_name,
				  QQmlContext* context_ptr)
{
	context_ptr->setContextProperty(model_name, model_ptr);
	context_ptr->setContextProperty(manager_name, manager_ptr);
}

int main(int argc, char* argv[])
{
	QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
	QGuiApplication app(argc, argv);
	QQmlApplicationEngine engine;
	CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
	auto corba_loader_ptr = std::make_shared<CorbaLoader>(orb);
	ModelManager model_manager(corba_loader_ptr);
	std::shared_ptr<APhonesModel> model_ptr(new EntriesModel);
	model_manager.setModel(model_ptr);
	registration(model_ptr.get(),
				 "entries", &model_manager,
				 "entries_manager",
				 engine.rootContext());
	const QUrl url(QStringLiteral("qrc:/main.qml"));
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
					 &app, [url](QObject *obj, const QUrl &objUrl) {
		if (!obj && url == objUrl)
			QCoreApplication::exit(-1);
	}, Qt::QueuedConnection);
	engine.load(url);
	return app.exec();
}
