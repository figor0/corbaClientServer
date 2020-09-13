#pragma once
#include <APhonesModel.h>
#include <memory>
#include <object.hh>

class EntriesModel: public APhonesModel
{
	Q_OBJECT
public:
	using Sequence = _CORBA_Unbounded_Sequence<EntryIdl>;
	EntriesModel(QObject* parent = nullptr);
	~EntriesModel() override = default;
	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;
	QVariant data(const QModelIndex &index = QModelIndex(), int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
	bool insertRows(int row, int count, const QModelIndex &parent) override;
	bool removeRows(int row, int count, const QModelIndex &parent) override;
private:
	MyInterface::Entries_var m_entries_ptr;
};
