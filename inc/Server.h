#pragma once
#include <object.hh>
#include <omniORB4/CORBA.h>
#include <omnithread.h>
#include <Entry.h>
#include <vector>
#include <QtSql>
#include <QSqlRecord>
#include <QString>
#include <map>
#include <DBManager.h>
#include <Servant.h>

class Server{
public:
	enum class ServerState{
		Stoped,
		Started
	};
	using InterfaceImp_ptr = std::shared_ptr<MyInterfaceImpl>;
	Server(const QString& db_path,
		   CORBA::ORB_var orb);
	CORBA::String_var getRef();
	void start();
	void stop();
	ServerState getState() const;
//	InterfaceImp_ptr getServant_ptr() const;
	MyInterfaceImpl *getServant_ptr() const;

private:
	ServerState m_state = ServerState::Stoped;
	std::thread m_worker;
	CORBA::String_var m_ref;
//	InterfaceImp_ptr m_servant_ptr;
	MyInterfaceImpl* m_servant_ptr;
	CORBA::ORB_var m_orb_ptr;
};

MyInterfaceImpl::Entries_sptr vect2corbaEntries(const std::vector<Entry>& entries_vector);

EntryIdl entry2corbaEntry(const Entry& entry);

