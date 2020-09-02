#pragma once
#include <object.hh>
#include <Entry.h>
#include <memory>
#include <vector>

EntryIdl entry2corbaEntry(const Entry &entry);
Entry corbaEntry2entry(const EntryIdl& corba_entry);

std::shared_ptr<MyInterface::Entries>
vect2corbaEntries(const std::vector<Entry> &entries_vector);

std::vector<Entry> corbaEntries2Entries(const MyInterface::Entries& corba_entries);
