#pragma once
#include <QObject>
#include <memory>
#include <CORBA.h>
#include <CorbaLoader.h>

class QQmlContext;

class EntriesModel;
class Entry;

class ModelManager: public QObject{
	Q_OBJECT
public:
	using EntriesModel_ptr = std::shared_ptr<EntriesModel>;
	using CorbaLoader_ptr = std::shared_ptr<CorbaLoader>;
	ModelManager(CorbaLoader_ptr loader, QObject* parent = nullptr);
	Q_INVOKABLE bool load(int action = 0);
	Q_INVOKABLE void change(const int action = 0);
	void registration( QQmlContext* context_ptr,
						const QString& model_name,
						const QString& model_manager_name);
private:
	QString m_db_path;
	CorbaLoader_ptr m_loader;
	MyInterface::Entries_var m_entries_ptr;
	EntriesModel_ptr m_model_ptr;
};
