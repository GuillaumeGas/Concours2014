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


void IA::change_state(State_t state) {
  this->state = state;
}



void IA::create_sheepDef(int planet_Id){
	for(auto it : planet){
		if(it.planetId == planet_Id){
			session->orderBuild(planet_Id,it.shipBuildCountLimit-1);
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

void IA::get_distances() {
  m_game_info = my_info->globalInformations();
  for(int i = 0; i < m_game_info.planetCount; i++) {
    for(int j = 0; j < m_game_info.planetCount; j++) {
      m_distances.insert(pair<pair<int, int>, int >(pair<int, int>(i, j), my_info->distance(i, j)));
    }			 
  }
}


void IA::pass_rowLuck() {
  if ( my_info->globalInformations().currentRoundId < 3 ) {    
    if ( planet.size() >  0 ) {
      int id = planet[0].planetId;
      int nb = 0;
      for ( int i = 0 ; i < m_game_info.planetCount ; i++ ) {
	if ( m_distances.find ( pair< int, int >(id, i ) )->second == 1 && nb < 3 ) {
	  //move_fleet( i , id );
	  nb++;
	}
      }
    }
  } else {
    change_state(DEFENSE);
  }
}

void IA::show_distances() {
  for(auto it : m_distances) {
    cout << "distance " << it.first.first << " - " << it.first.second << " = " << it.second << endl;
  }
}
