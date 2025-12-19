#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int n, d;
  cin >> n >> d;
  vector<int> players(n);
  for (int i = 0; i < n; ++i) {
    cin >> players[i];
  }
  sort(players.rbegin(), players.rend());
  int wins = 0;
  while (!players.empty()) {
    int rest = d / players[0];
    if ((int)players.size() < rest + 1) {
      break;
    }
    if (rest != 0) {
      players.erase(players.begin());
      players.erase(players.end() - rest, players.end());
    } else {
      players.erase(players.begin());
    }
    wins++;
  }
  cout << wins << endl;
  return 0;
}
