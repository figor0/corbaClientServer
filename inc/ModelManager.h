#pragma once
#include <QObject>
#include <memory>
#include <CORBA.h>
#include <CorbaLoader.h>
#include <object.hh>
#include <APhonesModelManager.h>
#include <APhonesModel.h>

class QQmlContext;

class ModelManager: public APhonesModelManager{
	Q_OBJECT
public:
	using Sequence = _CORBA_Unbounded_Sequence<EntryIdl>;
	using CorbaLoader_ptr = std::shared_ptr<CorbaLoader>;
	ModelManager(CorbaLoader_ptr loader,
				 QObject* parent = nullptr);
	void resetData(const Sequence& sequence);
	bool setEntry(const size_t index, const EntryIdl& entry);
	EntryIdl getEntry(const size_t row_number) const;
	Sequence getEntries() const;
private:
	bool private_load(int action = 0) override;
	bool private_chagne(const int action) override;
	CorbaLoader_ptr m_loader;
	MyInterface::Entries_var m_entries_ptr;
};
