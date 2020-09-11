#pragma once
#include <object.hh>
#include <omniORB4/CORBA.h>
#include <omnithread.h>
#include <Servant.h>
#include <QString>

class Server{
public:
	enum class ServerState{
		Stoped,
		Started
	};
	using InterfaceImpl_ptr = PortableServer::Servant_var<MyInterfaceImpl>;
	Server(const QString& db_path,
		   CORBA::ORB_var orb);
	CORBA::String_var getRef();
	void start();
	void stop();
	ServerState getState() const;
	MyInterfaceImpl *getServant_ptr() const;
private:
	ServerState m_state = ServerState::Stoped;
	CORBA::String_var m_ref;
	InterfaceImpl_ptr m_servant_ptr;
	CORBA::ORB_var m_orb_ptr;
};


