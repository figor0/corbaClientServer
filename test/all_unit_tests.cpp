#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include <Server.h>
#include <DBManager.h>
#include <generate.h>
#include <QString>
#include <QFile>
#include <iostream>

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
	auto generated_data = entriesGenerator(20);
	if (saver.save(db_global_path, generated_data) == generated_data.size()){
		result = db_global_path;
	}
	return result;
}

bool dbClear()
{
	return QFile::remove(db_global_path);
}

BOOST_AUTO_TEST_SUITE(Server_test)
BOOST_AUTO_TEST_CASE(general_test)
{
	BOOST_CHECK(dbPrepare() == db_global_path);
	{
		CORBA::ORB_var orb = CORBA::ORB_init(
					boost::unit_test::framework::master_test_suite().argc,
					boost::unit_test::framework::master_test_suite().argv);
		Server server(db_global_path, orb);
		server.start();
		sleep(1);
		qDebug() << "Object description " << server.getRef();
		CORBA::Object_var client_object = orb->string_to_object(server.getRef());
		MyInterface_var client_ref = MyInterface::_narrow(client_object);
		BOOST_CHECK(CORBA::is_nil(client_ref) == false);
		MyInterface::Entries *loaded_data = client_ref->load();
		BOOST_CHECK(loaded_data->length() == g_entries_size);
		server.stop();
	}
	BOOST_CHECK(dbClear() == true);
}
BOOST_AUTO_TEST_SUITE_END()
