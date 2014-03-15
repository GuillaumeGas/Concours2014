#ifndef CONNECTION
#define CONNECTION

#include <contest.hpp>
#include "err.hpp"

class Connection{
private:
	std::string pseudo;
	Session session;
public:
	Connection(std::string ip,std::string port,std::string pseudo);
	~Connection();
};

#endif