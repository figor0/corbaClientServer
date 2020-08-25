#include <CorbaLoader.h>
#include <Servant.h>
#include <iostream>

CorbaLoader::CorbaLoader( CORBA::ORB_var orb)
	:  m_orb(orb)
{}

static CORBA::Object_ptr
getObjectReference(CORBA::ORB_ptr orb)
{
	CosNaming::NamingContext_var rootContext;
	try {
		// Obtain a reference to the root context of the Name service:
		CORBA::Object_var obj;
		obj = orb->resolve_initial_references("NameService");
		// Narrow the reference returned.
		rootContext = CosNaming::NamingContext::_narrow(obj);
		if (CORBA::is_nil(rootContext)) {
		std::cerr << "Failed to narrow the root naming context." << std::endl;
		return CORBA::Object::_nil();
		}
	}
	catch (CORBA::NO_RESOURCES&) {
		std::cerr << "Caught NO_RESOURCES exception. You must configure omniORB "
		<< "with the location" << std::endl
		<< "of the naming service." << std::endl;
		return CORBA::Object::_nil();
	}
	catch (CORBA::ORB::InvalidName& ex) {
		// This should not happen!
		std::cerr << "Service required is invalid [does not exist]." << std::endl;
		return CORBA::Object::_nil();
	}
	// Create a name object, containing the name test/context:
	CosNaming::Name name;
	name.length(2);
	name[0].id = (const char*) "test"; // string copied
	name[0].kind = (const char*) "my_context"; // string copied
	name[1].id = (const char*) "Loader";
	name[1].kind = (const char*) "Object";
	// Note on kind: The kind field is used to indicate the type
	// of the object. This is to avoid conventions such as that used
	// by files (name.type -- e.g. test.ps = postscript etc.)
	try {
		// Resolve the name to an object reference.
		return rootContext->resolve(name);
	}
	catch (CosNaming::NamingContext::NotFound& ex) {
		// This exception is thrown if any of the components of the
		// path [contexts or the object] aren’t found:
		std::cerr << "Context not found." << std::endl;
	}
	catch (CORBA::TRANSIENT& ex) {
		std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
		<< "naming service." << std::endl
		<< "Make sure the naming server is running and that omniORB is "
		<< "configured correctly." << std::endl;
	}
	catch (CORBA::SystemException& ex) {
		std::cerr << "Caught a CORBA::" << ex._name()
		<< " while using the naming service." << std::endl;
	}
	return CORBA::Object::_nil();
}

std::vector<Entry> CorbaLoader::load()
{
	std::vector<Entry> result;
	try
	{
		CORBA::Object_var o = getObjectReference(m_orb);
		MyInterface_ptr oRef = MyInterface::_narrow (o);
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
