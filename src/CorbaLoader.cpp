#include <CorbaLoader.h>
#include <Servant.h>
#include <iostream>

CorbaLoader::CorbaLoader(const QString &servant_ref, CORBA::ORB_var orb)
	: m_servant_ref(servant_ref), m_orb(orb)
{}

std::vector<Entry> CorbaLoader::load()
{
	std::vector<Entry> result;
	try
	{
		CORBA::Object_var obj = m_orb->string_to_object(m_servant_ref.toStdString().data());
		MyInterface_var oRef = MyInterface::_narrow (obj);
		if (CORBA::is_nil(oRef))
		{
			std::cout << "Failure during getting of object"
						 " reference\n";
		}
		else
		{
			auto entries = oRef->load();
			std::cout << "Entries: " << '\n';
			for (size_t i = 0; i < entries->length(); i++)
			{
				std::cout << " First_name: " << entries->operator[](i).first_name
						<< " Last_name: " << entries->operator[](i).last_name
						<< " Father_name: " << entries->operator[](i).father_name
						<< " Phone: " << entries->operator[](i).phone << '\n';
			}
			result = corbaEntries2Entries(entries);
		}
	}
	catch(const CORBA::Exception& e)
	{
		std::cerr << e._name() << std::endl;
	}
	return result;
}
