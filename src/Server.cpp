#include <Server.h>
#include <DBManager.h>
#include <memory>
#include <thread>


Server::Server(const QString &db_path,
			   CORBA::ORB_var orb)
{
	DBManager manager;
	auto data_vector = manager.load(db_path);
	m_orb_ptr = orb;
	m_servant_ptr = new MyInterfaceImpl(data_vector);
	m_ref = m_orb_ptr->object_to_string(m_servant_ptr->_this());
}

CORBA::String_var Server::getRef(){
	return m_ref;
}

void Server::start()
{
	m_orb_ptr->run();
}

void Server::stop()
{
	m_orb_ptr->shutdown(true);
	m_worker.join();
}

Server::ServerState Server::getState() const
{
	return m_state;
}

MyInterfaceImpl *Server::getServant_ptr() const
{
	return m_servant_ptr;
}
