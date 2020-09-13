#include <ModelManager.h>
#include <QQmlContext>
#include <EntriesModel.h>
#include <CorbaLoader.h>


ModelManager::ModelManager(ModelManager::CorbaLoader_ptr loader_ptr,
						   QObject *parent): QObject(parent),
	m_loader(loader_ptr),
	m_model_ptr(std::make_shared<EntriesModel>())
{}

void ModelManager::change(const int action)
{
	MyInterface::Entries_var entries_ptr = new MyInterface::Entries;
	entries_ptr->m_entries = getEntries();
	m_loader->change(action, entries_ptr);
	resetData(entries_ptr->m_entries);
}

bool ModelManager::load(const int action)
{
	bool result = true;
	auto data = m_loader->load(action);
	resetData(data->m_entries);
	return result;
}

void ModelManager::registration(QQmlContext* context_ptr,
								const QString &model_name,
								const QString &model_manager_name)
{
	context_ptr->setContextProperty(model_name, m_model_ptr.get());
	context_ptr->setContextProperty(model_manager_name, this);
}

void ModelManager::resetData(const ModelManager::Sequence &sequence)
{
	if (m_model_ptr->rowCount() != sequence.length()){
		m_model_ptr->removeRows(0, m_model_ptr->rowCount(), QModelIndex());
		m_model_ptr->insertRows(0, sequence.length(), QModelIndex());
	}
	for (size_t i = 0; i < sequence.length(); i++){
		setEntry(i, sequence[i]);
	}

}

bool ModelManager::setEntry(const size_t index, const EntryIdl& entry)
{
	bool right = false;
	right = m_model_ptr->setData(m_model_ptr->index(index, 0),
						 QVariant(entry.first_name), EntriesModel::Roles::FirstName);
	right = m_model_ptr->setData(m_model_ptr->index(index, 0),
						 QVariant(entry.last_name), EntriesModel::Roles::LastName);
	right = m_model_ptr->setData(m_model_ptr->index(index, 0),
						 QVariant(entry.father_name), EntriesModel::Roles::FatherName);
	right = m_model_ptr->setData(m_model_ptr->index(index, 0),
						 QVariant(entry.phone), EntriesModel::Roles::Phone);
	return right;
}

EntryIdl ModelManager::getEntry(const size_t row_number) const
{
	return {
		m_model_ptr->data(m_model_ptr->index(row_number, 0),
						  EntriesModel::Roles::FirstName).toString().toStdString().data(),
		m_model_ptr->data(m_model_ptr->index(row_number, 0),
						  EntriesModel::Roles::LastName).toString().toStdString().data(),
		m_model_ptr->data(m_model_ptr->index(row_number, 0),
						  EntriesModel::Roles::FatherName).toString().toStdString().data(),
		m_model_ptr->data(m_model_ptr->index(row_number, 0),
						  EntriesModel::Roles::Phone).toString().toStdString().data(),
	};
}

ModelManager::Sequence ModelManager::getEntries() const
{
	Sequence entries;
	entries.length(m_model_ptr->rowCount());
	for (size_t i = 0; i < entries.length(); i++)
	{
		entries[i] = getEntry(i);
	}
	return entries;
}

