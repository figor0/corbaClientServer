#pragma once
#include <object.hh>
#include <omniORB4/CORBA.h>
#include <omnithread.h>
#include <Entry.h>
#include <memory>
#include <vector>

class MyInterfaceImpl: public POA_MyInterface
{
public:
	using Entries_sptr = std::shared_ptr<MyInterface::Entries>;
	MyInterfaceImpl(const std::vector<Entry>& entries);
	void load(::CORBA::Long action_id, MyInterface::Entries_out ent) override;
	void changeRequest(::CORBA::Long action_id, MyInterface::Entries& entr) override;
	Entries_sptr entries() const;
private:
	Entries_sptr m_entries;
public:
};

class Action;
std::shared_ptr<Action> createAction(int type);
