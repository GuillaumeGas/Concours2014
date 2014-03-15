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
  
  session.login("supergrossevache");

  session.waitInit();
  //compute_preprocessing();

  while(session.waitRoundStarting() == ROUND_NORMAL)
    //compute_one_round(session);

  return 0;
}
