#ifndef CONNECTION
#define CONNECTION

#include <contest.hpp>
#include "err.hpp"
#include "IA1_0/IA.hpp"

class Connection{
private:
	std::string pseudo;
	Session session;
public:
	Connection(std::string ip,int port,std::string pseudo);
	void start(IA & ia);
	~Connection();
};

#endif