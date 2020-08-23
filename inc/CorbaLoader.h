#include <QString>
#include <CORBA.h>
#include <vector>
#include <Entry.h>
#include <Servant.h>
#include <iostream>

class CorbaLoader
{
public:
	CorbaLoader(const QString& servant_ref, CORBA::ORB_var orb);
	std::vector<Entry> load();
private:
	QString m_servant_ref;
	CORBA::ORB_var m_orb;
};
