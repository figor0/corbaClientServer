#pragma once
#include <object.hh>

enum class VisitorsType
{
	Invert,
	toLower,
	ToUpper
};

class Action
{
public:
	virtual ~Action() = default;
	virtual void prepare(MyInterface::Entries* entries) = 0;
};

class InvertAction: public Action
{
public:
	~InvertAction() override = default;
	void prepare(MyInterface::Entries* entries) override;
};

class toLowerAction: public Action
{
public:
	~toLowerAction() override = default;
	void prepare(MyInterface::Entries* entries) override;
private:
	void toLower(EntryIdl& entry);
	void toLower(::CORBA::String_member& str);
};

class toUpperAction: public Action
{
public:
	~toUpperAction() override = default;
	void prepare(MyInterface::Entries* entries) override;
private:
	void toUpper(EntryIdl& entry);
	void toUpper(::CORBA::String_member& str);
};


