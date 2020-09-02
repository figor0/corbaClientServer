#include <cpp2idlEntry.h>

Entry corbaEntry2entry(const EntryIdl &corba_entry){
	Entry result;
	result.first_name = QString(corba_entry.first_name);
	result.last_name = QString(corba_entry.last_name);
	result.father_name = QString(corba_entry.father_name);
	result.phone = QString(corba_entry.phone);
	return result;
}

std::vector<Entry> corbaEntries2Entries(const MyInterface::Entries& corba_entries)
{
	std::vector<Entry> result(corba_entries.m_entries.length());
	for (size_t i = 0; i < result.size(); i++){
		result[i] = corbaEntry2entry(corba_entries.m_entries[i]);
	}
	return result;
}

EntryIdl entry2corbaEntry(const Entry &entry)
{
	EntryIdl result;
	result.first_name = CORBA::string_dup(entry.first_name.toStdString().data());
	result.last_name = CORBA::string_dup(entry.last_name.toStdString().data());
	result.father_name = CORBA::string_dup(entry.father_name.toStdString().data());
	result.phone = CORBA::string_dup(entry.phone.toStdString().data());
	return result;
}

std::shared_ptr<MyInterface::Entries> vect2corbaEntries(const std::vector<Entry> &entries_vector)
{
	auto result = std::make_shared<MyInterface::Entries>();
	result->m_entries.length((entries_vector.size()));
	for (size_t i = 0; i < result->m_entries.length(); i++){
		result->m_entries[i] = entry2corbaEntry(entries_vector.at(i));
	}
	return result;
}
