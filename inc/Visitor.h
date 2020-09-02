#include <vector>
#include <object.hh>
#include <algorithm>

enum class VisitorsType
{
	Invert,
	toLower,
	ToUpper
};

class Visitor
{
public:
	virtual ~Visitor() = default;
	virtual void prepare(MyInterface::Entries* entries) = 0;
};

class InvertVisitor: public Visitor
{
public:
	~InvertVisitor() override = default;
	void prepare(MyInterface::Entries* entries) override;
};

class toLowerVisitor: public Visitor
{
public:
	~toLowerVisitor() override = default;
	void prepare(MyInterface::Entries* entries) override;
private:
	void toLower(EntryIdl& entry);
	void toLower(::CORBA::String_member& str);
};

class toUpperVisitor: public Visitor
{
public:
	~toUpperVisitor() override = default;
	void prepare(MyInterface::Entries* entries) override;
private:
	void toUpper(EntryIdl& entry);
	void toUpper(::CORBA::String_member& str);
};


