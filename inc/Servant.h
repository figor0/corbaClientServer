#pragma once
#include <object.hh>
#include <omniORB4/CORBA.h>
#include <omnithread.h>
#include <Entry.h>
#include <memory>
#include <vector>
#include <QString>
#include <Action.h>

class MyInterfaceImpl: public POA_MyInterface
{
public:
	using Entries_sptr = std::shared_ptr<MyInterface::Entries>;
	MyInterfaceImpl(const std::vector<Entry>& entries);
	void load(::CORBA::Long action, MyInterface::Entries_out ent) override;
	void changeRequest(::CORBA::Long action, MyInterface::Entries& entr) override;
	Entries_sptr entries() const;
private:
	Entries_sptr m_entries;
public:
};

std::shared_ptr<Action> createAction(int type);
