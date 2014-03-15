#include "Connection.hpp"
#include <iostream>
using namespace std;

int main(int argc,char ** argv){
	try{
		Connection(argv[1],argv[2],"TeamPower");	
	}catch(const char * e){
		cerr<<e<<endl;
		return -1;
	}
	return 0;
}