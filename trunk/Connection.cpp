#include "Connection.hpp"

Connection::Connection(string ip, string port, string pseudo){
	session.connect(ip,port);
	if(session.isConnected()){
		string err = check_error_log(session.login(pseudo))
		if(err!="LOGIN_OK"){
			throw session.lastError();
		}
	}else{
		return session.lastError();
	}
}

Connection::~Connection(){
	session.disconnect();
}