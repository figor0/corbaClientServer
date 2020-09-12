#pragma once
#include <QAbstractTableModel>
#include <memory>
#include <object.hh>


class EntriesModel: public QAbstractTableModel
{
	Q_OBJECT
public:
	enum Roles{
		FirstName = Qt::UserRole + 1,
		LastName,
		FatherName,
		Phone
	};
	using Sequence = _CORBA_Unbounded_Sequence<EntryIdl>;
	EntriesModel(MyInterface::Entries_var entries_ptr, QObject* parent = nullptr);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	void resetData(const Sequence& data);
	QHash<int, QByteArray> roleNames() const;
	MyInterface::Entries entries() const;
private:
	MyInterface::Entries_var m_entries_ptr;
};
