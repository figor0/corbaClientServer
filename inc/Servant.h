#pragma once
#include <object.hh>
#include <omniORB4/CORBA.h>
#include <omnithread.h>
#include <Entry.h>
#include <memory>
#include <vector>
#include <QString>


class MyInterfaceImpl: public POA_MyInterface
{
public:
	using Entries_sptr = std::shared_ptr<MyInterface::Entries>;
	MyInterfaceImpl(const std::vector<Entry>& entries);
	MyInterface::Entries *load() override;
	Entries_sptr entries() const;
private:
	Entries_sptr m_entries;
};

EntryIdl entry2corbaEntry(const Entry &entry);
Entry corbaEntry2entry(const EntryIdl& corba_entry);
MyInterfaceImpl::Entries_sptr vect2corbaEntries(const std::vector<Entry> &entries_vector);
std::vector<Entry> corbaEntries2Entries(MyInterface::Entries* corba_entries);
