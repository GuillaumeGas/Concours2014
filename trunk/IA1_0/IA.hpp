#ifndef _IA
#define _IA

#include <iostream>
#include <map>

#define List std::vector
#define String std::string
typedef List<Planet> PlanetList;
typedef List<ScanResult> ScanResultList;
typedef List<Fleet> FleetList;
typedef List<Ennemy> EnnemyList;
typedef List<FightReport> FightReportList;

class IA {

  enum State_t {
    ATTACK, DEFENSE
  };


  IA ( );
  void change_state();
  void read_data( GameInfos );
  void load_info();

  void choose();



  void pass_rowAtt();
  void pass_rowDef();

  

  //ATTACK
  void choose_Planet(); //choisi la planete a attaque
  void attack_planet(int Planet_Id); // attaque une planete 
  void create_sheepAtt(int Planete_Id); // creer les vaisseau d'une planete
  
  

  //DEF
  void create_sheepDef(int planet_Id); //creer les vaisseau d'un planete Nb = (RP/X) - 1
  void move_fleet(int Planet_Id); //deplace les vaisseau vers une autre planete
  void fuir(int Planet_Id); //fuis la planete car elle est attaque
  void construct_all_sheep(int Planet_Id); //construis tout les vaisseau d'une planete toute pour defense
  void read_planet(int Planet_Id); //lis les donnes d'une planete
  void read_attack (); //lis toute les attaques ennemis

private:

  GameInfos my_info;
  std::map < int, std::pair < int, ScanResult > > information;
  State_t state;
  PlanetList planet;

};







#endif
