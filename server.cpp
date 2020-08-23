#include <Server.h>
#include <generate.h>
#include <fstream>
#include <iostream>
#include <CORBA.h>

const QString db_global_path = "./db";
const size_t g_entries_size = 20;

QString dbPrepare()
{
	QFile file(db_global_path);
	if (file.exists()){
		file.remove();
	}
	QString result;
	DBManager saver;
	auto generated_data = entriesGenerator(g_entries_size);
	if (saver.save(db_global_path, generated_data) == generated_data.size()){
		result = db_global_path;
	}
	return result;
}

bool dbClear()
{
	return QFile::remove(db_global_path);
}


int main(int argc, char* argv[])
{
	try
	{
		dbPrepare();
		CORBA::ORB_var orb = CORBA::ORB_init(argc, argv);
		CORBA::Object_var obj_ptr = orb->resolve_initial_references("RootPOA");
		PortableServer::POA_var poa_ptr = PortableServer::POA::_narrow(obj_ptr);
		Server server(db_global_path, orb);
		std::ofstream oref_file ("MyORef.ior");
		CORBA::String_var str = server.getRef();
		oref_file.write (str, strlen(str)+1);
		oref_file.close();
		PortableServer::POAManager_var pmanager = poa_ptr->the_POAManager();
		pmanager->activate();
		std::cout << "Waiting for client requests..." << std::endl;
		orb->run();
		dbClear();
	}
	catch(const CORBA::Exception& e)
	{
		std::cerr << e._name() << std::endl;
		return(1);
	}
	return 0;
}
