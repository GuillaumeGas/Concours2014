#ifndef _IA
#define _IA

#include <iostream>
#include <contest.hpp>
#include <map>

#define List std::vector
#define String std::string
typedef List<Planet> PlanetList;
typedef List<ScanResult> ScanResultList;
typedef List<Fleet> FleetList;
typedef List<Ennemy> EnnemyList;
typedef List<FightReport> FightReportList;

class IA {
public:
  enum State_t {
    ATTACK, DEFENSE, LUCK
  };
  IA(){state = LUCK;}
  void change_state(State_t);
  void read_data( GameData & info );
  void load_info();
  void set_session(Session * s);

  void choose();



  void pass_rowAtt();
  void pass_rowDef();
  void pass_rowLuck(); 


  //a lancer au démarrage
  void get_distances();
  void show_distances(); //fonction de test

  //ATTACK
  int choose_Planet(int & nbship); //choisi la planete a attaque
  void attack_planet(int Planet_Id, int From); // attaque une planete 
  void create_sheepAtt(int Planete_Id); // creer les vaisseau d'une planete
  //int choose_att();
  

  //DEF
  void create_sheepDef(int planet_Id); //creer les vaisseau d'un planete Nb = (RP/X) - 1
  void move_fleet(int Planet_Id, int From); //deplace les vaisseau vers une autre planete
  void fuir(int Planet_Id); //fuis la planete car elle est attaque
  void construct_all_sheep(int Planet_Id); //construis tout les vaisseau d'une planete toute pour defense
  void read_planet(int Planet_Id); //lis les donnes d'une planete
  void read_attack (); //lis toute les attaques ennemis

private:

  Session * session;
  GameData * my_info;
  GameInfos m_game_info;
  std::map < int, std::pair < int, ScanResult > > information;
  std::map < std::pair< int, int >, int > m_distances;
  State_t state;
  PlanetList planet;

};







#endif
