#include <array>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <vector>

struct Point {
  unsigned int x, y;

  Point(unsigned int x_, unsigned int y_) {
    x = x_;
    y = y_;
  }

  friend bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  friend bool operator<(const Point &l, const Point &r) {
    return l.x < r.x || (l.x == r.x && l.y < r.y);  // keep the same order
  }
};

long flash(Point octopus, std::array<std::array<int, 10>, 10> &map,
           std::set<Point> &already_flash) {

  long result = 1;
  map[octopus.x][octopus.y] = 0;
  already_flash.insert(octopus);

  for (int diff_x = -1; diff_x <= 1; diff_x++) {
    for (int diff_y = -1; diff_y <= 1; diff_y++) {
      if ((octopus.x + diff_x < 0) || (octopus.x + diff_x >= map.size()) ||
          (octopus.y + diff_y < 0) ||
          (octopus.y + diff_y >= map[octopus.x].size()) ||
          (diff_y == 0 && diff_x == 0)) {
        continue;
      }

      Point next_octopus(octopus.x + diff_x, octopus.y + diff_y);
      if (map[next_octopus.x][next_octopus.y] != 0) {
        map[next_octopus.x][next_octopus.y]++;
        if (map[next_octopus.x][next_octopus.y] > 9) {
          result += flash(next_octopus, map, already_flash);
        }
      }
    }
  }

  return result;
}

int main(int argc, char const *argv[]) {
  std::array<std::array<int, 10>, 10> map;
  long total = 0;

  std::string line;
  size_t y = 0;
  while (std::cin >> line) {
    for (size_t i = 0; i < line.length(); i++) {
      map[i][y] = line[i] - '0';
    }
    y++;
  }

  for (size_t i = 0; i < 100; i++) {
    std::cout << "===============" << std::endl;
    for (size_t x = 0; x < map.size(); x++) {
      for (size_t y = 0; y < map[x].size(); y++) {
        std::cout << map[y][x];
      }
      std::cout << std::endl;
    }
    std::cout << std::endl;

    for (size_t x = 0; x < map.size(); x++) {
      for (size_t y = 0; y < map[x].size(); y++) {
        map[x][y]++;
      }
    }

    for (size_t x = 0; x < map.size(); x++) {
      for (size_t y = 0; y < map[x].size(); y++) {
        if (map[x][y] > 9) {
          Point octopus(x, y);
          std::set<Point> already_flash;
          total += flash(octopus, map, already_flash);
        }
      }
    }

    std::cout << i + 1 << ": " << total << std::endl;
  }

  std::cout << total << std::endl;

  return 0;
}
