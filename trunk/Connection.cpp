#include "Connection.hpp"
using namespace std;

Connection::Connection(string ip,int port , string pseudo){
	session.connect(ip,port);
	if(session.isConnected()){
		LoginResult lr = session.login(pseudo);
		if(lr!=LOGIN_OK){
			throw session.lastError().c_str();
		}
	}else{
		throw session.lastError().c_str();
	}
}

void Connection::start(/*IA & ia*/){
cout<<"start"<<endl;
if(session.waitInit()){
	cout<<"game started"<<endl;
	while(true){
		session.waitRoundStarting();
			//ia.readData(session.gameData());
	}
}else{
	throw session.lastError().c_str();
}
}

Connection::~Connection(){
	session.disconnect();
}