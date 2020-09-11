#include <Server.h>
#include <generate.h>
#include <fstream>
#include <iostream>
#include <CORBA.h>
#include <DBManager.h>
#include <QFile>
#include <thread>

const QString db_global_path = "./db";
const size_t g_entries_size = 20;

QString dbPrepare()
{
	QFile file(db_global_path);
	if (file.exists()){
		file.remove();
	}
	QString result;
	auto& saver = DBManager::instance();
	auto generated_data = generator::entriesGenerator(g_entries_size);
	if (saver.save(db_global_path, generated_data) == generated_data.length()){
		result = db_global_path;
	}
	return result;
}

bool dbClear()
{
	return QFile::remove(db_global_path);
}

std::ostream& operator<<(std::ostream& reader, const CORBA::Exception& ex){
	reader << ex._name() << '\n';
	reader << ex._rep_id() << '\n';
	return reader;
}

static CORBA::Boolean bindObjectToName(CORBA::ORB_ptr orb, CORBA::Object_ptr objref);

int main(int argc, char* argv[])
{
	try
	{
		std::cout << "Подготовка демонстрационной базы данных" << std::endl;
		dbPrepare();
		CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
		CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
		PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);
		std::cout << "Подготовка сервера" << std::endl;
		Server server("./db", orb);
//		PortableServer::ObjectId_var myechoid = poa->activate_object(server.getServant_ptr());
		// Obtain a reference to the object, and register it in
		// the naming service.
		obj = server.getServant_ptr()->_this();
		if (!bindObjectToName(orb, obj))
			return 1;
		PortableServer::POAManager_var pman = poa->the_POAManager();
		pman->activate();

		std::cout << "Запуск сервера в другом потоке" << std::endl;
		server.startInOtherThread();
		std::cout << "Введите любой символ для выхода" << std::endl;
		getchar();
		std::cout << "Остановка сервера" << std::endl;
		server.stop();
		std::cout << "Очистка демонстрационной базы данных" << std::endl;
		dbClear();
		return 0;
	}
	catch (CORBA::SystemException& ex) {
		std::cerr << "Caught CORBA::" << ex._name() << std::endl;
		return 1;
	}
	catch (CORBA::Exception& ex) {
		std::cerr << "Caught CORBA::Exception: " << ex._name() << std::endl;
		return 1;
	}
}

// копипаста из omniorb guide
static CORBA::Boolean
bindObjectToName(CORBA::ORB_ptr orb, CORBA::Object_ptr objref)
{
	CosNaming::NamingContext_var rootContext;
	try {
		// Obtain a reference to the root context of the Name service:
		CORBA::Object_var obj = orb->resolve_initial_references("NameService");
		// Narrow the reference returned.
		rootContext = CosNaming::NamingContext::_narrow(obj);
		if (CORBA::is_nil(rootContext)) {
			std::cerr << "Failed to narrow the root naming context." << std::endl;
			return 0;
		}
	}
	catch (CORBA::NO_RESOURCES&) {
		std::cerr << "Caught NO_RESOURCES exception. You must configure omniORB "
		<< "with the location" << std::endl
		<< "of the naming service." << std::endl;
		return 0;
	}
	catch (CORBA::ORB::InvalidName&) {
		// This should not happen!
		std::cerr << "Service required is invalid [does not exist]." << std::endl;
		return 0;
	}
	try {
	// Bind a context called "test" to the root context:
		CosNaming::Name contextName;
		contextName.length(1);
		contextName[0].id = (const char*) "test"; // string copied
		contextName[0].kind = (const char*) "my_context"; // string copied
		// Note on kind: The kind field is used to indicate the type
		// of the object. This is to avoid conventions such as that used
		// by files (name.type -- e.g. test.ps = postscript etc.)
		CosNaming::NamingContext_var testContext;
	try {
	// Bind the context to root.
		testContext = rootContext->bind_new_context(contextName);
	}
	catch(CosNaming::NamingContext::AlreadyBound& ex) {
	// If the context already exists, this exception will be raised.
	// In this case, just resolve the name and assign testContext
	// to the object returned:
		CORBA::Object_var obj = rootContext->resolve(contextName);
		testContext = CosNaming::NamingContext::_narrow(obj);
		if (CORBA::is_nil(testContext)) {
			std::cerr << "Failed to narrow naming context." << std::endl;
			return 0;
		}
	}
	// Bind objref with the testContext:
	CosNaming::Name objectName;
	objectName.length(1);
	objectName[0].id = (const char*) "Loader"; // string copied
	objectName[0].kind = (const char*) "Object"; // string copied
	try {
	testContext->bind(objectName, objref);
	}
	catch(CosNaming::NamingContext::AlreadyBound& ex) {
	testContext->rebind(objectName, objref);
	}
	// Note: Using rebind() will overwrite any Object previously bound
	// to /test/Echo with obj.
	// Alternatively, bind() can be used, which will raise a
	// CosNaming::NamingContext::AlreadyBound exception if the name
	// supplied is already bound to an object.
	}
	catch (CORBA::TRANSIENT& ex) {
	std::cerr << "Caught system exception TRANSIENT -- unable to contact the "
	<< "naming service." << std::endl
	<< "Make sure the naming server is running and that omniORB is "
	<< "configured correctly." << std::endl;
	return 0;
	}
	catch (CORBA::SystemException& ex) {
	std::cerr << "Caught a CORBA::" << ex._name()
	<< " while using the naming service." << std::endl;
	return 0;
	}
	return 1;
}
