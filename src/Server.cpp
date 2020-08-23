#include <Server.h>
#include <DBManager.h>
#include <memory>
#include <thread>

MyInterfaceImpl::MyInterfaceImpl(const std::vector<Entry>& entries_vector)
	: m_entries(vect2corbaEntries(entries_vector))
{}

MyInterface::Entries *MyInterfaceImpl::load()
{
	MyInterface::Entries *result_rptr = new MyInterface::Entries;
	result_rptr->length(m_entries->length());
	for (size_t i = 0; i < result_rptr->length(); i++)
	{
		(*result_rptr)[i] = (*m_entries)[i];
	}
	return result_rptr;
}

MyInterfaceImpl::Entries_sptr MyInterfaceImpl::entries() const
{
	return m_entries;
}


EntryIdl entry2corbaEntry(const Entry &entry)
{
	EntryIdl result;
	result.first_name = CORBA::string_dup(entry.first_name.toStdString().data());
	result.last_name = CORBA::string_dup(entry.last_name.toStdString().data());
	result.father_name = CORBA::string_dup(entry.father_name.toStdString().data());
	result.phone = CORBA::string_dup(entry.phone.toStdString().data());
	return result;
}

MyInterfaceImpl::Entries_sptr vect2corbaEntries(const std::vector<Entry> &entries_vector)
{
	auto result = std::make_shared<MyInterface::Entries>();
	result->length(entries_vector.size());
	for (size_t i = 0; i < result->length(); i++){
		result->operator[](i) = entry2corbaEntry(entries_vector.at(i));
	}
	return result;
}

Server::Server(const QString &db_path,
			   CORBA::ORB_var orb)
{
	DBManager manager;
	auto data_vector = manager.load(db_path);
	m_orb_ptr = orb;
//	m_servant_ptr = std::make_shared<MyInterfaceImpl>(data_vector);
	m_servant_ptr = new MyInterfaceImpl(data_vector);
	m_ref = m_orb_ptr->object_to_string(m_servant_ptr->_this());
}

CORBA::String_var Server::getRef(){
	return m_ref;
}

void Server::start()
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

//Server::InterfaceImp_ptr Server::getServant_ptr() const
//{
//    return m_servant_ptr;
//}

