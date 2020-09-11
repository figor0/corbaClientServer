#include <EntriesModel.h>
#include <DBManager.h>
#include <QByteArray>

EntriesModel::EntriesModel( MyInterface::Entries_var entries_ptr,
							QObject *parent): QAbstractTableModel(parent),
	m_entries_ptr(entries_ptr)
{}

int EntriesModel::rowCount(const QModelIndex &parent) const
{
	return m_entries_ptr->m_entries.length();
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
			result.setValue(QString(m_entries_ptr->m_entries[index.row()].first_name));
		break;
	case Roles::LastName:
			result.setValue(QString(m_entries_ptr->m_entries[index.row()].last_name));
		break;
	case Roles::FatherName:
			result.setValue(QString(m_entries_ptr->m_entries[index.row()].father_name));
		break;
	case Roles::Phone:
			result.setValue(QString(m_entries_ptr->m_entries[index.row()].phone));
		break;
	}
	return result;
}

bool EntriesModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
	bool result = true;
	auto& item_ref = m_entries_ptr->m_entries[index.row()];
	switch (role) {
	case Roles::FirstName:
			item_ref.first_name = CORBA::string_dup(value.toString().toStdString().data());
		break;
	case Roles::LastName:
			item_ref.last_name = CORBA::string_dup(value.toString().toStdString().data());
		break;
	case Roles::FatherName:
			item_ref.father_name = CORBA::string_dup(value.toString().toStdString().data());
		break;
	case Roles::Phone:
			item_ref.phone = CORBA::string_dup(value.toString().toStdString().data());
		break;
	default:
		result = false;
	}
	dataChanged(createIndex(0,0), createIndex(rowCount() - 1, 0));
	return result;
}

void EntriesModel::resetData(const EntriesModel::Sequence &data)
{
	if (data.length() == m_entries_ptr->m_entries.length()){
		m_entries_ptr->m_entries = data;
	} else if (data.length() > m_entries_ptr->m_entries.length()){
		beginInsertRows(QModelIndex(), m_entries_ptr->m_entries.length() - 1,
						data.length()-1);
		m_entries_ptr->m_entries = data;
		endInsertRows();
	} else if (data.length() < m_entries_ptr->m_entries.length()){
		beginRemoveRows(QModelIndex(), data.length()-1, m_entries_ptr->m_entries.length()-1);
		m_entries_ptr->m_entries = data;
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

MyInterface::Entries EntriesModel::entries() const
{
	return m_entries_ptr;
}
