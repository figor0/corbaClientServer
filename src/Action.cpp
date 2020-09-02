#include <Action.h>
#include <ctype.h>
#include <vector>
#include <algorithm>

void InvectAction::prepare(MyInterface::Entries *entries)
{
	size_t size = entries->m_entries.length();
	for (size_t i = 0; i < size/2; i++){
		std::swap(entries->m_entries[i], entries->m_entries[size - 1 - i]);
	}
}

void toLowerAction::prepare(MyInterface::Entries *entries)
{
	for (size_t i = 0; i < entries->m_entries.length(); i++){
		toLower(entries->m_entries[i]);
	}
}

void toLowerAction::toLower(EntryIdl &entry)
{
	toLower(entry.first_name);
	toLower(entry.last_name);
	toLower(entry.father_name);
}

void toLowerAction::toLower(::CORBA::String_member &str){
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		str[i] = tolower(str[i]);
	}
}

void toUpperAction::prepare(MyInterface::Entries *entries)
{
	for (size_t i = 0; i < entries->m_entries.length(); i++)
	{
		toUpper(entries->m_entries[i]);
	}
}

void toUpperAction::toUpper(EntryIdl &entry){
	toUpper(entry.first_name);
	toUpper(entry.last_name);
	toUpper(entry.father_name);
}

void toUpperAction::toUpper(::CORBA::String_member &str){
	for (size_t i = 0; str[i] != '\0'; i++)
	{
		str[i] = toupper(str[i]);
	}
}
