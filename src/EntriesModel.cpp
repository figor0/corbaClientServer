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

void EntriesModel::removeRow(const int index){
	beginRemoveRows(QModelIndex(), index, 1);
	m_entries_ptr->erase(index);
	endRemoveRows();
}

void EntriesModel::appendRow(const Entry &entry)
{
	beginInsertRows(QModelIndex(), rowCount() - 1, 1);
	if (m_entries_ref_ptr != nullptr){
		m_entries_ref_ptr->push_back(entry);
	} else {
		m_entries_ptr->push_back(entry);
	}
	endInsertRows();
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

void EntriesModel::filtration(const QString &filter){
	beginRemoveRows(QModelIndex(), 0, rowCount());
	endRemoveRows();
	m_entries_ref_ptr.reset();
	if (filter != ""){
		m_entries_ref_ptr = std::make_shared<EntriesRef>(m_entries_ptr.get(), filter);
	}
}
