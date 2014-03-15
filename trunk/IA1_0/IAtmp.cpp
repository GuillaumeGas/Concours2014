void IA::pass_rowLuck() {
  if ( my_info->globalInformations().currentRoundId < 3 ) {    
    if ( planet.size >  0 ) {
      int id = planet[0].planetId;
      int nb = 0;
      for ( int i = 0 ; i < my_info->globalInformations() ; i++ ) {
	if ( m_distance.find ( pair< int, int >(id, i ) )->second == 1 && nb < 3 ) {
	  move_fleet( i , id );
	  nb++;
	}
      }
    }
  } else {
    change_state(DEFENSE);
  }
}
