#include "IA.hpp"
using namespace std;

void IA::choose(){
	if(state == ATTACK)
		pass_rowAtt();
	else
		pass_rowDef();
}

void IA::load_info(){
	planet = my_info->planets();
	ScanResultList L;
	L = my_info->scanResults();
	auto it(L.begin());
	for(it;it != L.end(); it++){
		if(information.find(it->planetId) != information.end()){
			information.erase(it->planetId);
		}
		information[it->planetId] = pair<int,ScanResult>(my_info->globalInformations().currentRoundId,*it);
	}
}


void IA::set_session(Session * s){
	session=s;
}




void IA::create_sheepDef(int planet_Id){
	for(auto it : planet){
		if(it.planetId == planet_Id){
			int max(it.shipBuildCountLimit);
			if(max < it.resources/my_info->globalInformations().shipCost;{
				session->orderBuild(planet_Id,max);
			}
		}
	}
}

void IA::pass_rowDef(){
	load_info();
	for(auto it : planet){
		create_sheepDef(it.planetId);
	}
}

int IA::choose_Planet(int & nbship) {
  int planet = -1;
  int min = -1;
  for ( auto it : information ) {    
    if ( it.second.first == my_info->globalInformations().currentRoundId ) {
      if ( min > it.second.second.shipCount || min == -1 ) {
       min = it.second.second.shipCount;
       planet = it.first;
       nbship = min;
     }
   }
 } 
 return planet;
}

void IA::read_data ( GameData & info ) {
  my_info = &info;
}




void IA::attack_planet ( int Planet_Id, int From ) {
  int nb = 0;
  for ( auto it : planet ) {
    if ( it.planetId == From ) {
      nb = it.shipCount;
    }
  }
  session->orderMove ( From, Planet_Id, nb );
}


void IA::create_sheepAtt( int Planet_Id ) {
  int nb = my_info->globalInformations().resources*my_info->globalInformations().shipCost;
  if ( nb > planet[Planet_Id].shipBuildCountLimit) {
    nb =  planet[Planet_Id].shipBuildCountLimit;
  }
  session->orderBuild( Planet_Id, nb);
}



void IA::pass_rowAtt() {
  int planet_att;/* = choose_att();*/
  int nbShip;
  int planet_to = choose_Planet(nbShip);
  
  for ( auto it : planet ) {
    if ( planet_att == it.planetId && it.shipCount > nbShip ) {
      create_sheepAtt( planet_att );
      attack_planet( planet_att, planet_to );
    } else {
      //change_state();
    }
  }
}

void IA::move_fleet(int planet_Id, int From){
	for( auto it : planet){
		if(it.planetId == planet_Id){
			if(it.shipCount > 2){
				session->orderMove(planet_Id,From,2);
			}
		}
	}
}
