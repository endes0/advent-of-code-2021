#include <algorithm>
#include <array>
#include <iostream>
#include <set>
#include <string>
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
};

void propagate(Point p, std::vector<Point> &points,
               std::vector<std::vector<int>> &map) {
  if (p.y != 0 && map[p.y - 1][p.x] < 9 &&
      std::find(points.begin(), points.end(), Point(p.x, p.y - 1)) ==
          points.end())  // Up
  {
    points.push_back(Point(p.x, p.y - 1));
    propagate(Point(p.x, p.y - 1), points, map);
  }
  if (p.y != map.size() - 1 && map[p.y + 1][p.x] < 9 &&
      std::find(points.begin(), points.end(), Point(p.x, p.y + 1)) ==
          points.end())  // Down
  {
    points.push_back(Point(p.x, p.y + 1));
    propagate(Point(p.x, p.y + 1), points, map);
  }

  if (p.x != 0 && map[p.y][p.x - 1] < 9 &&
      std::find(points.begin(), points.end(), Point(p.x - 1, p.y)) ==
          points.end())  // Left
  {
    points.push_back(Point(p.x - 1, p.y));
    propagate(Point(p.x - 1, p.y), points, map);
  }
  if (p.x != map[p.y].size() - 1 && map[p.y][p.x + 1] < 9 &&
      std::find(points.begin(), points.end(), Point(p.x + 1, p.y)) ==
          points.end())  // Right
  {
    points.push_back(Point(p.x + 1, p.y));
    propagate(Point(p.x + 1, p.y), points, map);
  }
}

bool comp(std::vector<Point> i, std::vector<Point> j) {
  return (i.size() < j.size());
}

int main(int argc, char const *argv[]) {
  std::vector<std::vector<int>> map;
  std::vector<Point> low_points;
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
        low_points.push_back(Point(j, i));
      }
    }
  }

  std::vector<std::vector<Point>> basins;
  for (auto point : low_points) {
    std::vector<Point> basin{point};
    propagate(point, basin, map);

    basins.push_back(basin);
  }

  std::sort(basins.begin(), basins.end(), comp);

  for (auto basin : basins) {
    std::cout << basin.size() << std::endl;
  }

  return 0;
}