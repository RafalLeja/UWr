/*
 * Rafał Leja 340879
 * MIA 2025
 * Zadanie B, Lista 1
 * 07.10.2025
 */
#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  int testy;
  cin >> testy;

  for (int t = 0; t < testy; ++t) {
    int num;
    cin >> num;

    vector<int> arr(num);
    for (int i = 0; i < num; ++i) {
      cin >> arr[i];
    }

    vector<int> dp(num, 0);
    vector<deque<int>> start(num + 1);
    vector<int> ilosc(num + 1, 0);

    if (arr[0] == 1) {
      dp[0] = 1;
    }
    ilosc[arr[0]] = 1;
    start[arr[0]].push_back(0);

    for (int i = 1; i < num; ++i) {
      start[arr[i]].push_back(i);
      ilosc[arr[i]]++;
      if (start[arr[i]].size() > arr[i]) {
        start[arr[i]].pop_front();
      }

      int bierz = 0;
      if (ilosc[arr[i]] >= arr[i]) {
        int poprzedni_index = start[arr[i]][0];
        int poprzednie = (poprzedni_index > 0) ? dp[poprzedni_index - 1] : 0;
        bierz = arr[i] + poprzednie;
      }

      int zostaw = dp[i - 1];

      dp[i] = max(bierz, zostaw);
    }

    cout << dp[num - 1] << endl;
  }

  return 0;
}
