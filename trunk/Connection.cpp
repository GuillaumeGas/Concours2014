#include "Connection.hpp"
using namespace std;

Connection::Connection(string ip,int port , string pseudo){
	session.connect(ip,port);
	if(session.isConnected()){
		string err = check_err_log(session.login(pseudo));
		if(err!="LOGIN_OK"){
			throw session.lastError().c_str();
		}
	}else{
		throw session.lastError().c_str();
	}
}

Connection::start(/*IA & ia*/){
	if(session.waitInit()){
		while(session.waitRoundStarting()){
			//ia.readData(session.gameData());
		}
	}else{
		throw session.lastError().c_str();
	}
}

Connection::~Connection(){
	session.disconnect();
}