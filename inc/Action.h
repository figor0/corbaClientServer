#include <vector>
#include <object.hh>
#include <algorithm>

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

class InvertVisitor: public Action
{
public:
	~InvertVisitor() override = default;
	void prepare(MyInterface::Entries* entries) override;
};

class toLowerVisitor: public Action
{
public:
	~toLowerVisitor() override = default;
	void prepare(MyInterface::Entries* entries) override;
private:
	void toLower(EntryIdl& entry);
	void toLower(::CORBA::String_member& str);
};

class toUpperVisitor: public Action
{
public:
	~toUpperVisitor() override = default;
	void prepare(MyInterface::Entries* entries) override;
private:
	void toUpper(EntryIdl& entry);
	void toUpper(::CORBA::String_member& str);
};


