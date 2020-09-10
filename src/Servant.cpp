#include <Servant.h>
#include <iostream>
#include <cpp2idlEntry.h>
#include <Action.h>


MyInterfaceImpl::MyInterfaceImpl(MyInterface::Entries_var entries_var)
	: m_entries(entries_var)
{}

void MyInterfaceImpl::load(::CORBA::Long action_id,
							MyInterface::Entries_out ent)
{
	auto action = createAction(action_id);
	ent = new MyInterface::Entries;
	ent->m_entries.length(m_entries->m_entries.length());
	ent->m_entries = m_entries->m_entries;
	if (action != nullptr)
		action->prepare(ent.ptr());
}

void MyInterfaceImpl::changeRequest(::CORBA::Long action_id, MyInterface::Entries &entr)
{
	auto  action = createAction(action_id);
	if (action != nullptr)
		action->prepare(&entr);
}

std::shared_ptr<Action> createAction(int type)
{
	std::shared_ptr<Action> result;
	switch (type) {
	case 1:
		result = std::make_shared<InvertAction>();
		break;
	case 2:
		result = std::make_shared<toLowerAction>();
		break;
	case 3:
		result = std::make_shared<toUpperAction>();
		break;
	}
	return result;
}
