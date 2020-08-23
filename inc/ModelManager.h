#include <QObject>
#include <memory>
#include <EntriesModel.h>
#include <Entry.h>
#include <CORBA.h>
#include <CorbaLoader.h>

class QQmlContext;

class ModelManager: public QObject{
	Q_OBJECT
public:
	using EntriesModel_ptr = std::shared_ptr<EntriesModel>;
	using Entries_ptr = std::shared_ptr<std::vector<Entry>>;
	using CorbaLoader_ptr = std::shared_ptr<CorbaLoader>;
	ModelManager(CorbaLoader_ptr loader, QObject* parent = nullptr);
	Q_INVOKABLE bool load();
	void registration( QQmlContext* context_ptr,
						const QString& model_name,
						const QString& model_manager_name);
private:
	QString m_db_path;
	CorbaLoader_ptr m_loader;
	Entries_ptr m_entries_ptr;
	EntriesModel_ptr m_model_ptr;
};
