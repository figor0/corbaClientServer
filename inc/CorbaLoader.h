#include <QString>
#include <CORBA.h>
#include <vector>
#include <Entry.h>
#include <Servant.h>
#include <iostream>

class CorbaLoader
{
public:
	CorbaLoader(CORBA::ORB_var orb);
	std::vector<Entry> load(const int type);
private:
	CORBA::ORB_var m_orb;
};
