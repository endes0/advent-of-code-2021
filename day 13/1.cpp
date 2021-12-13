#include <array>
#include <iostream>
#include <set>
#include <sstream>
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
};

void check_insert(std::vector<Point> &points, Point p) {
  bool found = false;
  for (auto point : points) {
    if (point == p) {
      found = true;
      break;
    }
  }

  if (!found) {
    points.push_back(p);
  }
}

std::vector<Point> fold_paper(std::vector<Point> points, Point fold_line) {
  std::vector<Point> new_paper;
  for (auto p : points) {
    if (fold_line.x == 0) {
      if (p.y > fold_line.y) {
        int dist = p.y - fold_line.y;

        check_insert(new_paper, Point(p.x, fold_line.y - dist));
      } else {
        check_insert(new_paper, p);
      }

    } else {
      if (p.x > fold_line.x) {
        int dist = p.x - fold_line.x;

        check_insert(new_paper, Point(fold_line.x - dist, p.y));
      } else {
        check_insert(new_paper, p);
      }
    }
  }

  return new_paper;
}

int main(int argc, char const *argv[]) {
  std::vector<Point> points;
  std::vector<Point> folds;

  std::string line;
  while (std::getline(std::cin, line)) {
    if (line == "") {
      break;
    }

    std::stringstream line_stream(line);
    std::string token1;
    std::string token2;

    std::getline(line_stream, token1, ',');
    std::getline(line_stream, token2, ',');

    points.push_back(Point(std::stoi(token1), std::stoi(token2)));
  }

  while (std::getline(std::cin, line)) {
    std::stringstream line_stream(line);
    std::string token1;
    std::string token2;

    std::getline(line_stream, token1, '=');
    std::getline(line_stream, token2, '=');

    if (token1 == "fold along y") {
      folds.push_back(Point(0, std::stoi(token2)));
    } else {
      folds.push_back(Point(std::stoi(token2), 0));
    }
  }

  std::vector<Point> final_paper = points;
  for (auto fold : folds) {
    final_paper = fold_paper(final_paper, fold);
  }

  std::cout << final_paper.size() << std::endl;

  std::array<std::array<bool, 100>, 100> map;
  for (size_t i = 0; i < 100; i++) {
    for (size_t j = 0; j < 100; j++) {
      map[i][j] = false;
    }
  }

  for (auto p : final_paper) {
    map[p.x][p.y] = true;
  }

  for (size_t i = 0; i < 100; i++) {
    for (size_t j = 0; j < 100; j++) {
      std::cout << map[j][i];
    }
    std::cout << std::endl;
  }

  return 0;
}
