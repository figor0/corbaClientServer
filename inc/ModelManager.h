#pragma once
#include <QObject>
#include <memory>
#include <CORBA.h>
#include <CorbaLoader.h>
#include <object.hh>

class QQmlContext;

class QAbstractTableModel;

class ModelManager: public QObject{
	Q_OBJECT
public:
	using Sequence = _CORBA_Unbounded_Sequence<EntryIdl>;
	using EntriesModel_ptr = std::shared_ptr<QAbstractTableModel>;
	using CorbaLoader_ptr = std::shared_ptr<CorbaLoader>;
	ModelManager(CorbaLoader_ptr loader,
				 QObject* parent = nullptr);
	bool setModel(EntriesModel_ptr model_ptr);
	Q_INVOKABLE bool load(int action = 0);
	Q_INVOKABLE void change(const int action = 0);
	void registration( QQmlContext* context_ptr,
						const QString& model_name,
						const QString& model_manager_name);
	void resetData(const Sequence& sequence);
	bool setEntry(const size_t index, const EntryIdl& entry);
	EntryIdl getEntry(const size_t row_number) const;
	Sequence getEntries() const;
private:
	CorbaLoader_ptr m_loader;
	MyInterface::Entries_var m_entries_ptr;
	EntriesModel_ptr m_model_ptr;
};
