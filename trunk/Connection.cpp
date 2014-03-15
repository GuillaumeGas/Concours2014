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

void Connection::start(IA & ia){
cout<<"start"<<endl;
ia.set_session(&session);
if(session.waitInit()){
	cout<<"game started"<<endl;
	while(true){
		session.waitRoundStarting();
		GameData gd = session.gameData();
		ia.read_data(gd);
		ia.choose();
		session.sendOrders();

	}
}else{
	throw session.lastError().c_str();
}
}



Connection::~Connection(){
	session.disconnect();
}