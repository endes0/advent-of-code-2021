#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<std::vector<int>> map;
  std::vector<int> low_points;
  int total = 0;
  std::string line;
  while (std::cin >> line) {
    std::vector<int> new_x;
    for (auto c : line) {
      new_x.push_back(c - '0');
    }
    map.push_back(new_x);
  }

  for (size_t i = 0; i < map.size(); i++) {
    for (size_t j = 0; j < map[i].size(); j++) {
      if ((i == 0 || map[i][j] < map[i - 1][j]) &&               // Up
          (j == 0 || map[i][j] < map[i][j - 1]) &&               // Left
          (i == map.size() - 1 || map[i][j] < map[i + 1][j]) &&  // Down
          (j == map[i].size() - 1 || map[i][j] < map[i][j + 1])  // Right
      ) {
        low_points.push_back(map[i][j]);
        total += map[i][j] + 1;
      }
    }
  }

  std::cout << total << std::endl;

  return 0;
}