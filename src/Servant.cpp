#include <Servant.h>
#include <iostream>
#include <cpp2idlEntry.h>


MyInterfaceImpl::MyInterfaceImpl(const std::vector<Entry>& entries_vector)
	: m_entries(vect2corbaEntries(entries_vector))
{}

void MyInterfaceImpl::load(::CORBA::Long action,
							MyInterface::Entries_out ent)
{
	auto visitor = createVisitor(action);
	ent = new MyInterface::Entries;
	ent->m_entries.length(m_entries->m_entries.length());
	ent->m_entries = m_entries->m_entries;
	if (visitor != nullptr)
		visitor->prepare(ent.ptr());
}

void MyInterfaceImpl::changeRequest(::CORBA::Long action, MyInterface::Entries &entr)
{
	auto visitor = createVisitor(action);
	if (visitor != nullptr)
		visitor->prepare(&entr);
}

MyInterfaceImpl::Entries_sptr MyInterfaceImpl::entries() const
{
	return m_entries;
}

std::shared_ptr<Action> createVisitor(int type)
{
	std::shared_ptr<Action> result;
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
