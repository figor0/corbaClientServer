#pragma once
#include <object.hh>
#include <omniORB4/CORBA.h>
#include <omnithread.h>
#include <memory>
#include <vector>

class MyInterfaceImpl: public POA_MyInterface
{
public:
	using Entries_sptr = MyInterface::Entries_var;
	MyInterfaceImpl(MyInterface::Entries_var entries_var);
	void load(::CORBA::Long action_id, MyInterface::Entries_out ent) override;
	void changeRequest(::CORBA::Long action_id, MyInterface::Entries& entr) override;
private:
	MyInterface::Entries_var m_entries;
};

class Action;
std::shared_ptr<Action> createAction(int type);
