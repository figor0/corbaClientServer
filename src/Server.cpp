#include <Server.h>
#include <DBManager.h>
#include <memory>


Server::Server(const QString &db_path,
			   CORBA::ORB_var orb)
{
	auto& manager = DBManager::instance();
	MyInterface::Entries_var entries = new MyInterface::Entries;
	entries->m_entries = manager.load(db_path);
	m_orb_ptr = orb;
	m_servant_ptr = new MyInterfaceImpl(entries);
	m_ref = m_orb_ptr->object_to_string(m_servant_ptr->_this());
}

CORBA::String_var Server::getRef(){
	return m_ref;
}

void Server::startInOtherThread()
{
	m_worker = std::thread(&CORBA::ORB::run, m_orb_ptr);
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
