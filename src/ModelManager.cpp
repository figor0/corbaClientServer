#include <ModelManager.h>
#include <QQmlContext>
#include <CorbaLoader.h>


ModelManager::ModelManager(ModelManager::CorbaLoader_ptr loader_ptr,
						   QObject *parent): APhonesModelManager(parent),
	m_loader(loader_ptr)
{}

void ModelManager::resetData(const ModelManager::Sequence &sequence)
{
	if (m_model_ptr == nullptr)
		throw std::invalid_argument("Model are not exitst");
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
	if (m_model_ptr == nullptr)
		throw std::invalid_argument("Model are not exitst");
	bool right = false;
	right = m_model_ptr->setData(m_model_ptr->index(index, 0),
						 QVariant(entry.first_name), APhonesModel::FirstName);
	right = m_model_ptr->setData(m_model_ptr->index(index, 0),
						 QVariant(entry.last_name), APhonesModel::LastName);
	right = m_model_ptr->setData(m_model_ptr->index(index, 0),
						 QVariant(entry.father_name), APhonesModel::FatherName);
	right = m_model_ptr->setData(m_model_ptr->index(index, 0),
						 QVariant(entry.phone), APhonesModel::Phone);
	return right;
}

EntryIdl ModelManager::getEntry(const size_t row_number) const
{
	if (m_model_ptr == nullptr)
		throw std::invalid_argument("Model are not exitst");
	return {
		m_model_ptr->data(m_model_ptr->index(row_number, 0),
							APhonesModel::FirstName).toString().toStdString().data(),
		m_model_ptr->data(m_model_ptr->index(row_number, 0),
							APhonesModel::LastName).toString().toStdString().data(),
		m_model_ptr->data(m_model_ptr->index(row_number, 0),
							APhonesModel::FatherName).toString().toStdString().data(),
		m_model_ptr->data(m_model_ptr->index(row_number, 0),
							APhonesModel::Phone).toString().toStdString().data(),
	};
}

ModelManager::Sequence ModelManager::getEntries() const
{
	if (m_model_ptr == nullptr)
		throw std::invalid_argument("Model are not exitst");
	Sequence entries;
	entries.length(m_model_ptr->rowCount());
	for (size_t i = 0; i < entries.length(); i++)
	{
		entries[i] = getEntry(i);
	}
	return entries;
}

bool ModelManager::private_load(int action)
{
	bool result = true;
	auto data = m_loader->load(action);
	resetData(data->m_entries);
	return result;
}

bool ModelManager::private_chagne(const int action){
	MyInterface::Entries_var entries_ptr = new MyInterface::Entries;
	entries_ptr->m_entries = getEntries();
	m_loader->change(action, entries_ptr);
	resetData(entries_ptr->m_entries);
	return true;
}

