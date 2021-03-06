#pragma once
#include <QString>
#include <CORBA.h>
#include <object.hh>
#include <iostream>

class CorbaLoader
{
public:
	using Sequence = _CORBA_Unbounded_Sequence<EntryIdl>;
	CorbaLoader(CORBA::ORB_var orb);
	MyInterface::Entries_var load(const int type);
	void change(const int type, MyInterface::Entries& entries);
private:
	CORBA::ORB_var m_orb;
};
