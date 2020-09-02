#include <Action.h>
#include <ctype.h>

void InvertVisitor::prepare(MyInterface::Entries *entries)
{
	size_t size = entries->m_entries.length();
	for (size_t i = 0; i < size/2; i++){
		std::swap(entries->m_entries[i], entries->m_entries[size - 1 - i]);
	}
}

void toLowerVisitor::prepare(MyInterface::Entries *entries)
{
	for (size_t i = 0; i < entries->m_entries.length(); i++){
		toLower(entries->m_entries[i]);
	}
}

void toLowerVisitor::toLower(EntryIdl &entry)
{
	toLower(entry.first_name);
	toLower(entry.last_name);
	toLower(entry.father_name);
}

void toLowerVisitor::toLower(::CORBA::String_member &str){
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		str[i] = tolower(str[i]);
	}
}

void toUpperVisitor::prepare(MyInterface::Entries *entries)
{
	for (size_t i = 0; i < entries->m_entries.length(); i++)
	{
		toUpper(entries->m_entries[i]);
	}
}

void toUpperVisitor::toUpper(EntryIdl &entry){
	toUpper(entry.first_name);
	toUpper(entry.last_name);
	toUpper(entry.father_name);
}

void toUpperVisitor::toUpper(::CORBA::String_member &str){
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		str[i] = toupper(str[i]);
	}
}
