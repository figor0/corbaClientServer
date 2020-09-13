#include <EntriesModel.h>
#include <DBManager.h>
#include <QByteArray>
#include <PhoneGeneral.h>

EntriesModel::EntriesModel( QObject *parent): QAbstractTableModel(parent),
	m_entries_ptr(new MyInterface::Entries)
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
	case PhoneEntryRoles::FirstName:
			result.setValue(QString(m_entries_ptr->m_entries[index.row()].first_name));
		break;
	case PhoneEntryRoles::LastName:
			result.setValue(QString(m_entries_ptr->m_entries[index.row()].last_name));
		break;
	case PhoneEntryRoles::FatherName:
			result.setValue(QString(m_entries_ptr->m_entries[index.row()].father_name));
		break;
	case PhoneEntryRoles::Phone:
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
	case PhoneEntryRoles::FirstName:
			item_ref.first_name = CORBA::string_dup(value.toString().toStdString().data());
		break;
	case PhoneEntryRoles::LastName:
			item_ref.last_name = CORBA::string_dup(value.toString().toStdString().data());
		break;
	case PhoneEntryRoles::FatherName:
			item_ref.father_name = CORBA::string_dup(value.toString().toStdString().data());
		break;
	case PhoneEntryRoles::Phone:
			item_ref.phone = CORBA::string_dup(value.toString().toStdString().data());
		break;
	default:
		result = false;
	}
	dataChanged(createIndex(0,0), createIndex(rowCount() - 1, 0));
	return result;
}

bool EntriesModel::insertRows(int row, int count, const QModelIndex &parent)
{
	size_t size = rowCount();
	if (row <= static_cast<int>(size)){
		beginInsertRows(QModelIndex(), row, row + count);
		m_entries_ptr->m_entries.length(m_entries_ptr->m_entries.length() + count);
		if (row != static_cast<int>(size)){
			for (size_t i = 0; i < static_cast<size_t>(count); i++){
				m_entries_ptr->m_entries[i + row + count] = m_entries_ptr->m_entries[i+row];
			}
		}
		endInsertRows();
		return true;
	}
	return false;
}

bool EntriesModel::removeRows(int row, int count, const QModelIndex &parent)
{
	if (row+count <= rowCount()){
		beginRemoveRows(parent, row, row+count);
		EntriesModel::Sequence buffer;
		buffer.length(m_entries_ptr->m_entries.length() - count);
		for (size_t i = row; i < buffer.length(); i++){
			buffer[i] = m_entries_ptr->m_entries[i+ row + count];
		}
		m_entries_ptr->m_entries.length(m_entries_ptr->m_entries.length() - count);
		for (size_t i = 0; i < buffer.length(); i++){
			m_entries_ptr->m_entries[i + row] = buffer[i];
		}
		endRemoveRows();
		return true;
	}
	return false;
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
