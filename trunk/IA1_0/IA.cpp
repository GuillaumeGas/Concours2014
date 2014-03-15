  #include "IA.hpp"

void IA::choose(){
	if(state == "ATTACK")
		pass_rowAtt();
	else
		pass_rowDef();
}

void IA::load_info(){
	planet = my_info.planets();
	ScanResultList L;
	L = my_info.scanResults();
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

int IA::choose_Planet() {
  int planet = -1;
  int min = -1;
  for ( auto it : information ) {    
    if ( it.second.first == my_info.currentRoundId ) {
      if ( min > it.second.second.shipCount || min == -1 ) {
	min = it.second.second.shipCount;
	planet = it.first;
      }
    }
  } 
  return planet;
}

void IA::read_data ( Gamedata info ) {
  my_info = info;
}




void IA::attack_planet ( int Planet_Id, int From ) {
  int nb = 0;
  for ( auto it : planet ) {
    if ( it.planetId == From ) {
      nb = it.shipCount();
    }
  }
  orderMove ( from, Planet_Id, nb );
}


void IA::create_sheepAtt( int Planet_Id ) {
  int nb = my_info.resources*my_info.shipCost;
  if ( nb > planet[Planet_Id].shipBuildCountLimit) {
    nb =  planet[Planet_Id].shipBuildCountLimit;
  }
  orderBuild( Planet_Id, nb);
}



void IA::pass_rowAtt() {
  int planet_att = choose_att();
  int nbShip;
  int planet_to = choose_Planet(nbShip);
  
  for ( auto it : planet ) {
    if ( planet_att == it.planetId && it.shipCount > nbShip ) {
      create_sheepAtt( planet_att );
      attack_planet( planet_att, planet_to );
    } else {
      change_state();
    }
  }
}
