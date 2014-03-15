#include "err.hpp"

using namespace std;

string check_err_log(LoginResult r) {
  string msg;
  switch(r) {
  case LOGIN_NO_MORE_ROOM:
    msg = "[ERR] Serveur plein.";
    break;
  case LOGIN_INVALID:
    msg = "[ERR] Login invalide.";
    break;
  case LOGIN_ALREADY_USED:
    msg = "[ERR] Login deja pris.";
    break;
  case LOGIN_NETWORK_ERROR:
    msg = "[ERR] Erreur reseau.";
    break;
  default:
    msg = "[ERR] Erreur]";
  }
  cout << msg << endl;
  return msg;
}

string check_err_round(RoundState r) {
  string msg;
  switch(r) {
  case ROUND_END_OF_GAME:
    msg = "Partie terminee !";
    break;
  case ROUND_NETWORK_ERROR:
    msg = "[ERR] Erreur reseau";
    break;
  case default:
    msg = "[ERR]";
  }
  cout << msg << endl;
  return msg;
}
