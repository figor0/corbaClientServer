#pragma once
#include <QAbstractTableModel>
#include <vector>
#include <memory>

class Entry;

class EntriesModel: public QAbstractTableModel
{
	Q_OBJECT
public:
	using Entries_ptr = std::shared_ptr<std::vector<Entry>>;
	enum Roles{
		FirstName = Qt::UserRole + 1,
		LastName,
		FatherName,
		Phone
	};
	EntriesModel(Entries_ptr entries_ptr, QObject* parent = nullptr);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
	void resetData(const std::vector<Entry>& data);
	QHash<int, QByteArray> roleNames() const;
	std::vector<Entry> entries() const;
private:
	Entries_ptr m_entries_ptr;
};
