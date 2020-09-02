#include <ModelManager.h>
#include <QQmlContext>
#include <EntriesModel.h>


ModelManager::ModelManager(ModelManager::CorbaLoader_ptr loader_ptr,
						   QObject *parent): QObject(parent),
	m_loader(loader_ptr),
	m_entries_ptr(std::make_shared<std::vector<Entry>>()),
	m_model_ptr(std::make_shared<EntriesModel>(m_entries_ptr))
{}

bool ModelManager::load()
{
	bool result = true;
	std::vector<Entry> loaded_data = m_loader->load(0);
	m_model_ptr->resetData(loaded_data);
	return result;
}

void ModelManager::registration(QQmlContext* context_ptr,
								const QString &model_name,
								const QString &model_manager_name)
{
	context_ptr->setContextProperty(model_name, m_model_ptr.get());
	context_ptr->setContextProperty(model_manager_name, this);
}

