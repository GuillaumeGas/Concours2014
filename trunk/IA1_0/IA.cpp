#include "IA.hpp"
using namespace std;

void IA::choose(){
  load_info();
  jouer = false;
  change_state(LUCK);
  while (!jouer) {
    if(state == ATTACK)
      pass_rowAtt();
    else if ( state == DEFENSE )
      pass_rowDef();
    else 
      pass_rowLuck();

  }
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



int IA::get_nearest_friend(int Planet_Id) {
  int _planet;
  int min = -1;
  for ( auto it : planet ){
    auto it2 = m_distances.find( pair<int, int>( Planet_Id, it.planetId ) );
    if ( (it2->second < min || min == -1 ) && it2->second != 0) {
      min = it2->second;
      _planet = it.planetId;
    }
  }
  return _planet;
}


void IA::fuir( int Planet_Id ) {
  vector<Ennemy> v = my_info->enemies();
  for ( auto it : v ) {
    if ( it.destinationPlanetId == Planet_Id ) {
      if ( it.shipCount >= planet[Planet_Id].shipCount ) {

	      

	session->orderMove( get_nearest_friend(Planet_Id), Planet_Id, planet[Planet_Id].shipCount );

      }
    }
  }
}


void IA::create_sheepDef(int planet_Id,int nb){
  session->orderBuild(planet_Id,nb);
}

void IA::pass_rowDef(){

  int res(0);
  for(auto it : planet){
    res+= it.resources;
  }
  res/=my_info->globalInformations().shipCost;
  if(my_info->globalInformations().shipCost == 0) {
    cout << "ERROOOOOOOOOOOOOOOOOOOOOR" << endl;
  }

  int min(100000);
  for(auto it : planet){
    if(it.shipCount < min)
      min = it.shipCount;
  }
  cout << "min" << min << endl;
  PlanetList L;
  for(auto it : planet){
    if(min == it.shipCount)
      L.push_back(it);
  }
  
if(L.size() == 0) {
    cout << "ERRROOOOOR = " << L.size() << endl;
  }
  int nb = res/L.size();
  
  int rst = res - nb*L.size();
	for(auto it : L){
		create_sheepDef(it.planetId,nb);
		//cout << "pla : " << it.planetId << endl;
	}
  create_sheepDef(L[0].planetId,rst);
	cout << "jouer" << endl;
	jouer = true;
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
      return;
    }
  }
  jouer = true;
}

void IA::move_fleet(int planet_Id, int From, int nb){
  //for( auto it : planet){
  //if(it.planetId == planet_Id){
  //if(it.shipCount > 2){
  session->orderMove(From,planet_Id,nb);
  //	}
  //		}
  //	}
}
void IA::get_distances() {
  m_game_info = my_info->globalInformations();
  for(int i = 0; i < m_game_info.planetCount; i++) {
    for(int j = 0; j < m_game_info.planetCount; j++) {
      m_distances.insert(pair<pair<int, int>, int >(pair<int, int>(i, j), my_info->distance(i, j)));
    }			 
  }
}



int IA::get_nearest(int planet_id, int & dist, int far) {
  int planet = 0;
  dist = -1;
  for ( int i = 0 ; i < m_game_info.planetCount ; i++ ) {
    auto it = m_distances.find ( ( pair< int, int >(planet_id, i ) ));
    if ( (it->second < dist && it->second > far ) || dist == -1 ) {
      planet = i;
      dist = it->second;
    }
  }
  return planet;
}


vector <int> IA::get_near( int planet_id , int dist ) {
  vector<int> v;
  for ( int i = 0 ; i < m_game_info.planetCount ; i++ ) {
    auto it = m_distances.find ( ( pair< int, int >(planet_id, i )));
    if (it->second == dist) {
      v.push_back(i);
    }
  }
  return v;
}


void IA::pass_rowLuck() {
  cout << "test 1" << endl;
  if ( my_info->globalInformations().currentRoundId % 5 == 1 ) {    
    cout << "test2" << endl;
    cout << "plante : " << planet.size() << endl;
    if ( planet.size() >  0 ) {
      for(int j = 0; j < planet.size(); j++) {
	cout << "pass row luck" << endl;
	int id = planet[j].planetId;
	int nb = planet[j].shipCount/2;
	int dist = 0;
	int dist_r = -1;
	while ( nb >= 0 && dist != dist_r) { 
	  dist_r = dist;
	  int i = get_nearest ( planet[j].planetId , dist, dist_r);
	  cout << "dist = " << dist << endl;
	  vector<int> v = get_near(planet[j].planetId, dist);
	  for ( int i = 0 ; i < v.size() && nb > 0; i++ ) {
	    move_fleet( v[i], planet[j].planetId, nb/v.size());
	    nb--;
	  }
	}
	create_sheepDef( planet[j].planetId, 2);
      }
      jouer =true;
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
