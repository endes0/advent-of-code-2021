#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Point {
  unsigned int x, y;

  Point(unsigned int x_, unsigned int y_) {
    x = x_;
    y = y_;
  }

  Point() {}

  friend bool operator==(const Point &lhs, const Point &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
  }

  friend bool operator<(const Point &l, const Point &r) {
    return l.x < r.x || (l.x == r.x && l.y < r.y);  // keep the same order
  }

  friend bool operator>(const Point &l, const Point &r) {
    return l.x > r.x || (l.x == r.x && l.y > r.y);  // keep the same order
  }
};

struct Risk {
  Point p;
  int risk;

  Risk(Point p_, int risk_) {
    p = p_;
    risk = risk_;
  }

  friend bool operator<(const Risk &l, const Risk &r) {
    return l.risk < r.risk;  // keep the same order
  }

  friend bool operator>(const Risk &l, const Risk &r) {
    return l.risk > r.risk;  // keep the same order
  }
};

void get_path(
    std::priority_queue<Risk, std::vector<Risk>, std::greater<Risk>> &points,
    std::set<Point> &visited, std::vector<std::vector<int>> &map,
    std::vector<std::vector<int>> &new_map) {
  Point point = points.top().p;
  points.pop();
  int current_risk = new_map[point.y][point.x];

  if (visited.find(point) != visited.end()) {
    return;
  }

  if (point.y == map.size() - 1 && point.x == map[point.y].size() - 1) {
    std::cout << new_map[point.y][point.x] << std::endl;
  }

  std::vector<Risk> risks;

  if (point.y != 0) {
    int up_risk = map[point.y - 1][point.x];
    risks.push_back(Risk(Point(point.x, point.y - 1), current_risk + up_risk));
  }
  if (point.y != map.size() - 1) {
    int down_risk = map[point.y + 1][point.x];
    risks.push_back(
        Risk(Point(point.x, point.y + 1), current_risk + down_risk));
  }
  if (point.x != 0) {
    int left_risk = map[point.y][point.x - 1];
    risks.push_back(
        Risk(Point(point.x - 1, point.y), current_risk + left_risk));
  }
  if (point.x != map[point.y].size() - 1) {
    int right_risk = map[point.y][point.x + 1];
    risks.push_back(
        Risk(Point(point.x + 1, point.y), current_risk + right_risk));
  }

  for (auto risk : risks) {
    if (visited.find(risk.p) == visited.end()) {
      if (new_map[risk.p.y][risk.p.x] > risk.risk) {
        new_map[risk.p.y][risk.p.x] = risk.risk;
      }
      points.push(Risk(risk.p, new_map[risk.p.y][risk.p.x]));
    }
  }
  visited.insert(point);
}

int main(int argc, char const *argv[]) {
  std::vector<std::vector<int>> map;

  std::string line;
  while (std::cin >> line) {
    std::vector<int> row;
    for (auto c : line) {
      row.push_back(c - '0');
    }
    map.push_back(row);
  }

  size_t y_dim = map.size();
  size_t x_dim = map[0].size();
  for (size_t i = 0; i < y_dim * 5; i++) {
    if (i >= map.size()) {
      map.push_back({});
    }

    for (size_t j = 0; j < x_dim * 5; j++) {
      size_t start_x = j % x_dim;
      size_t start_y = i % y_dim;

      size_t x_repet = j / x_dim;
      size_t y_repet = i / y_dim;

      if (j >= map[i].size()) {
        map[i].push_back(-1);
      }

      int val = (map[start_y][start_x] + x_repet + y_repet - 1) % 9 + 1;
      map[i][j] = val;
    }
  }

  for (auto row : map) {
    for (auto elem : row) {
      std::cout << elem;
    }

    std::cout << std::endl;
  }

  std::set<Point> visited;
  std::vector<std::vector<int>> new_map;

  for (size_t i = 0; i < map.size(); i++) {
    new_map.push_back({});
    for (size_t j = 0; j < map[0].size(); j++) {
      new_map[i].push_back(10000);
    }
  }
  new_map[0][0] = 0;

  std::priority_queue<Risk, std::vector<Risk>, std::greater<Risk>> points;
  points.push(Risk(Point(0, 0), 0));

  while (points.size() > 0) {
    get_path(points, visited, map, new_map);
  }

  for (auto row : new_map) {
    for (auto elem : row) {
      std::cout << std::setw(3) << elem << " ";
    }

    std::cout << std::endl;
  }

  return 0;
}
