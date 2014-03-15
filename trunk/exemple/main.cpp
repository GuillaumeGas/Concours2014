#include <contest.hpp>
#include <iostream>

using namespace std;



int main() {
  Session session;

  session.connect("127.0.0.1", 9999);
  if(session.isConnected()) {
    cout << "ok" << endl;
  }
  cout << session.lastError() << endl;
  
  LoginResult res_log = session.login("supergrossevache");
  if(res_log != LOGIN_OK) {
    check_err(res_log);
    return -1;
  }

  session.waitInit();
  //compute_preprocessing();

  while(session.waitRoundStarting() == ROUND_NORMAL)
    //compute_one_round(session);

  return 0;
}
