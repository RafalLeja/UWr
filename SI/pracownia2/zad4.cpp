#include <string>
#include <tuple>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <queue>
#include <fstream>
#include <unordered_set>

using namespace std;

set<pair<int, int>> goals;
set<pair<int, int>> walls;

map<string, pair<int, int>> moves = {
  {"U", make_pair(0, -1)},
  {"D", make_pair(0, 1)},
  {"L", make_pair(-1, 0)},
  {"R", make_pair(1, 0)}
};

class State {
  public:
    set<pair<int, int>> commandos;
    string moves;
    int f;
    State(string moves, set<pair<int, int>> commandos){
      this->moves = moves;
      this->commandos = commandos;
      this->f = moves.length();

      int max = 0;
      for (auto commando : this->commandos) {
        for (auto goal : goals) {
          int dist = abs(commando.first - goal.first) + abs(commando.second - goal.second);
          if (dist > max) {
            max = dist;
          }
        }
      }

      this->f += max * 2;
    };
};

class gtState {
  public:
    bool operator()(const State& s1, const State& s2) const {
      if (s1.f == s2.f){
        return s1.moves.length() > s2.moves.length();
      }
      return s1.f > s2.f;
    }
};

State move(State state, string move){
  set<pair<int, int>> new_commandos;
  pair<int, int> move_tuple = moves[move];
  for (auto commando : state.commandos){
    pair<int, int> new_pos = make_pair(commando.first + move_tuple.first, commando.second + move_tuple.second);
    if (walls.find(new_pos) == walls.end()){
      new_commandos.insert(new_pos);
    }else{
      new_commandos.insert(commando);
    }
  }
  return State(state.moves + move, new_commandos);
}

string to_string(set<pair<int, int>> commandos){
  string result = "";
  for (auto commando : commandos){
    result += to_string(commando.first) + "." + to_string(commando.second) + " ";
  }
  return result;
}

bool is_goal(State state){
  if (to_string(state.commandos) == to_string(goals)){
    return true;
  }

  for (auto commando : state.commandos){
    if (goals.find(commando) == goals.end()){
      return false;
    }
  }
  return true;
}


int main(){
  ifstream inputFile;
  inputFile.open("zad_input.txt");

  ofstream outputFile;
  outputFile.open("zad_output.txt");

  unordered_set<string> visited;
  set<pair<int, int>> commandos;

  int x = 0, y = 0;
  while (!inputFile.eof()){
    x = 0;
    string line;
    getline(inputFile, line);
    for (char c : line){
      if (c == 'G'){
        goals.insert(make_pair(x, y));
      }else if (c == '#'){
        walls.insert(make_pair(x, y));
      }else if (c == 'B'){
        commandos.insert(make_pair(x, y));
        goals.insert(make_pair(x, y));
      }else if (c == 'S'){
        commandos.insert(make_pair(x, y));
      }
      x++;
    }
    y++;
  }

  State start = State("", commandos);
  // cout << start.f << endl;

  priority_queue<State, vector<State>, gtState> q;
  q.push(start);

  while (!q.empty()){
    State current = q.top();
    q.pop();

    // cout << current.f << endl;
    // cout << q.size() << endl;

    if (visited.find(to_string(current.commandos)) != visited.end()){
      continue;
    }
    visited.insert(to_string(current.commandos));

    if (is_goal(current)){
      outputFile << current.moves << endl;
      break;
    }

    for (auto dir : {"U", "D", "L", "R"}){
      State new_state = move(current, dir);
      q.push(new_state);
    }
  }

  inputFile.close();
  outputFile.close();
  return 0;
  
}
