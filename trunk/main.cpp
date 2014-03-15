#include "Connection.hpp"
#include <cstdlib>
#include <iostream>
#include "IA1_0/IA.hpp"
using namespace std;

int main(int argc,char ** argv){
	IA ia;
	try{
		Connection game(argv[1],atoi(argv[2]),"TeamPower");
		game.start(ia);
	}catch(const char * e){
		cerr<<e<<endl;
		return -1;
	}
	return 0;
}
