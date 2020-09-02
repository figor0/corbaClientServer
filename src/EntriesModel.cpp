#include <EntriesModel.h>

EntriesModel::EntriesModel( EntriesModel::Entries_ptr entries_ptr,
							QObject *parent): QAbstractTableModel(parent),
	m_entries_ptr(entries_ptr)
{}

int EntriesModel::rowCount(const QModelIndex &parent) const
{
	return m_entries_ptr->size();
}

int EntriesModel::columnCount(const QModelIndex &parent) const
{
	return 1;
}

QVariant EntriesModel::data(const QModelIndex &index, int role) const
{
	QVariant result;
	switch (role) {
	case Roles::FirstName:
			result.setValue(m_entries_ptr->at(index.row()).first_name);
		break;
	case Roles::LastName:
			result.setValue(m_entries_ptr->at(index.row()).last_name);
		break;
	case Roles::FatherName:
			result.setValue(m_entries_ptr->at(index.row()).father_name);
		break;
	case Roles::Phone:
			result.setValue(m_entries_ptr->at(index.row()).phone);
		break;
	}
	return result;
}

bool EntriesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	bool result = true;
	switch (role) {
	case Roles::FirstName:
			m_entries_ptr->operator[](index.row()).first_name = value.toString();
		break;
	case Roles::LastName:
			m_entries_ptr->operator[](index.row()).last_name = value.toString();
		break;
	case Roles::FatherName:
			m_entries_ptr->operator[](index.row()).father_name = value.toString();
		break;
	case Roles::Phone:
			m_entries_ptr->operator[](index.row()).phone = value.toString();
		break;
	default:
		result = false;
	}
	dataChanged(createIndex(0,0), createIndex(rowCount() - 1, 0));
	return result;
}

void EntriesModel::resetData(const std::vector<Entry> &data)
{
	if (data.size() == m_entries_ptr->size()){
		*m_entries_ptr = data;
	} else if (data.size() > m_entries_ptr->size()){
		beginInsertRows(QModelIndex(), m_entries_ptr->size() - 1, data.size()-1);
		*m_entries_ptr = data;
		endInsertRows();
	} else if (data.size() < m_entries_ptr->size()){
		beginRemoveRows(QModelIndex(), data.size()-1, m_entries_ptr->size()-1);
		*m_entries_ptr = data;
		endRemoveRows();
	}
	emit dataChanged(createIndex(0, 0), createIndex(rowCount() - 1, 0));
}

QHash<int, QByteArray> EntriesModel::roleNames() const
{
	return {
		{FirstName, "first_name"},
		{LastName, "last_name"},
		{FatherName, "father_name"},
		{Phone, "phone"}
	};
}

std::vector<Entry> EntriesModel::entries() const
{
	return *m_entries_ptr;
}
