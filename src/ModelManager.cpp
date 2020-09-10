#include <ModelManager.h>
#include <QQmlContext>
#include <EntriesModel.h>
#include <Entry.h>
#include <CorbaLoader.h>


ModelManager::ModelManager(ModelManager::CorbaLoader_ptr loader_ptr,
						   QObject *parent): QObject(parent),
	m_loader(loader_ptr),
	m_entries_ptr(new MyInterface::Entries),
	m_model_ptr(std::make_shared<EntriesModel>(m_entries_ptr))
{}

void ModelManager::change(const int action)
{
	auto input_entries = m_model_ptr->entries();
	m_loader->change(action, input_entries);
	m_model_ptr->resetData(input_entries.m_entries);
}

bool ModelManager::load(const int action)
{
	bool result = true;
	auto data = m_loader->load(action);
	m_model_ptr->resetData(data.m_entries);
	return result;
}

void ModelManager::registration(QQmlContext* context_ptr,
								const QString &model_name,
								const QString &model_manager_name)
{
	context_ptr->setContextProperty(model_name, m_model_ptr.get());
	context_ptr->setContextProperty(model_manager_name, this);
}

