#include <ModelManager.h>
#include <QQmlContext>
#include <EntriesModel.h>


ModelManager::ModelManager(QObject *parent): QObject(parent),
	m_entries_ptr(std::make_shared<std::vector<Entry>>()),
	m_model_ptr(std::make_shared<EntriesModel>(m_entries_ptr))
{}

bool ModelManager::load()
{
	bool result = true;
	m_model_ptr.reset();
	m_entries_ptr.reset();
	m_entries_ptr = std::make_shared<std::vector<Entry>>(m_db_manager.load(m_db_path));
	m_model_ptr = std::make_shared<EntriesModel>(m_entries_ptr);
	return result;
}

void ModelManager::registration(QQmlContext* context_ptr,
								const QString &model_name,
								const QString &model_manager_name)
{
	context_ptr->setContextProperty(model_name, m_model_ptr.get());
	context_ptr->setContextProperty(model_manager_name, this);
}

