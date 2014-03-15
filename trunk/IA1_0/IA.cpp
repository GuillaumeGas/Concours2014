#include "IA.hpp"

void IA::choose(){
	if(state == "ATTACK")
		pass_rowAtt();
	else
		pass_rowDef();
}

void IA::load_info(){
	planet = planets();
	ScanResultList L;
	L = scanResults();
	auto it(L.begin()):
	for(it;it != L.end(); it++){
		if(information.find(it->planetId) != information.end()){
			information.erase(planetId);
		}
		information[planetId] = pair<int,scanResult>(my_info.currentRoundld,*it)
	}
}

void IA::create_sheepDef(int planet_Id){
	for(auto it : planet){
		if(it.planetId == planet_Id){
			orderBuild(planet_Id,it.shipBuildCountLimit-1)
		}
	}
}

void IA::pass_rowDef(){
	RoundState R;
	R = waitRoundStarting();
	if(R = ROUND_NORMAL){
		load_info();
		for(auto it : planet){
			create_sheepDef(it->planetId);
		}
	}
}