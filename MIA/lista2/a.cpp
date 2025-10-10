#include <algorithm>
#include <iostream>
#include <vector>

int t;
int n;
std::vector<int> f_min;
std::vector<int> s_min;
int f_sum = 0;
int s_sum = 0;

int main(int argc, char *argv[]) {

  std::cin >> t;
  for (int test = 0; test < t; test++) {
    std::cin >> n;
    f_min.clear();
    s_min.clear();
    f_sum = 0;
    s_sum = 0;
    for (int i = 0; i < n; i++) {
      int m;
      std::cin >> m;
      for (int j = 0; j < m; j++) {
        int number, f, s;
        std::cin >> number;
        if (number < f) {
          f = number;
        } else if (number < s) {
          s = number;
        }
        f_min.push_back(f);
        s_min.push_back(s);
      }
      f_sum += f_min[i];
      s_sum += s_min[i];
      std::cout << f_min[i] << s_min[i];
    }

    int wynik = s_sum - *std::min_element(s_min.begin(), s_min.end()) +
                *std::min_element(f_min.begin(), f_min.end());
    std::cout << wynik;
  }

  return 0;
}
