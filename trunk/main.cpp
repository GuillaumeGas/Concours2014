#include "Connection.hpp"
#include <iostream>
using namespace std;

int main(){
	try{
		Connection("127.0.0.1",4242,"*team->power(socket&)");	
	}catch(const char * e){
		cerr<<e<<endl;
		return -1;
	}
	return 0;
}