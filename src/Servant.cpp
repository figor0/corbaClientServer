#include <Servant.h>
#include <iostream>

EntryIdl entry2corbaEntry(const Entry &entry)
{
	EntryIdl result;
	result.first_name = CORBA::string_dup(entry.first_name.toStdString().data());
	result.last_name = CORBA::string_dup(entry.last_name.toStdString().data());
	result.father_name = CORBA::string_dup(entry.father_name.toStdString().data());
	result.phone = CORBA::string_dup(entry.phone.toStdString().data());
	return result;
}

MyInterfaceImpl::Entries_sptr vect2corbaEntries(const std::vector<Entry> &entries_vector)
{
	auto result = std::make_shared<MyInterface::Entries>();
	result->m_entries.length((entries_vector.size()));
	for (size_t i = 0; i < result->m_entries.length(); i++){
		result->m_entries[i] = entry2corbaEntry(entries_vector.at(i));
	}
	return result;
}


MyInterfaceImpl::MyInterfaceImpl(const std::vector<Entry>& entries_vector)
	: m_entries(vect2corbaEntries(entries_vector))
{}

void MyInterfaceImpl::load(::CORBA::Long action,
							MyInterface::Entries_out ent)
{
	auto visitor = createVisitor(action);
	std::cout << "Parametr " << action << std::endl;
	ent = new MyInterface::Entries;
	ent->m_entries.length(m_entries->m_entries.length());
	ent->m_entries = m_entries->m_entries;
	if (visitor != nullptr)
		visitor->prepare(ent.ptr());
}

MyInterfaceImpl::Entries_sptr MyInterfaceImpl::entries() const
{
	return m_entries;
}

Entry corbaEntry2entry(const EntryIdl &corba_entry){
	Entry result;
	result.first_name = QString(corba_entry.first_name);
	result.last_name = QString(corba_entry.last_name);
	result.father_name = QString(corba_entry.father_name);
	result.phone = QString(corba_entry.phone);
	return result;
}

std::vector<Entry> corbaEntries2Entries(MyInterface::Entries* corba_entries)
{
	std::vector<Entry> result(corba_entries->m_entries.length());
	for (size_t i = 0; i < result.size(); i++){
		result[i] = corbaEntry2entry(corba_entries->m_entries[i]);
	}
	return result;
}

std::shared_ptr<Visitor> createVisitor(int type)
{
	std::shared_ptr<Visitor> result;
	switch (type) {
	case 1:
		result = std::make_shared<InvertVisitor>();
		break;
	case 2:
		result = std::make_shared<toLowerVisitor>();
		break;
	case 3:
		result = std::make_shared<toUpperVisitor>();
		break;
	}
	return result;
}
