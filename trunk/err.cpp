#include "err.hpp"

using namespace std;

void check_err_log(LoginResult r) {
  switch(r) {
  case LOGIN_NO_MORE_ROOM:
    cout << "[ERR] Serveur plein." << endl;
    break;
  case LOGIN_INVALID:
    cout << "[ERR] Login invalide." << endl;
    break;
  case LOGIN_ALREADY_USED:
    cout << "[ERR] Login deja pris." << endl;
    break;
  case LOGIN_NETWORK_ERROR:
    cout << "[ERR] Erreur reseau." << endl;
    break;
  default:
    cout << "[ERR] Erreur]" << endl;
  }
}

void check_err_round(RoundState r) {
  switch(r) {
  case ROUND_END_OF_GAME:
    cout << "Partie terminee !" << endl;
    break;
  case ROUND_NETWORK_ERROR:
    cout << "[ERR] Erreur reseau" << endl;
    break;
  case default:
    cout << "[ERR]" << endl;
  }
}
