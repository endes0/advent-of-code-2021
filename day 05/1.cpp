#include <array>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct Point {
  unsigned int x;
  unsigned int y;
  Point(unsigned int ini_x, unsigned int ini_y);
};

Point::Point(unsigned int ini_x, unsigned int ini_y) {
  x = ini_x;
  y = ini_y;
}

class Line {
 protected:
  unsigned int min_x;
  unsigned int max_x;
  unsigned int min_y;
  unsigned int max_y;

 public:
  Line(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2);
  ~Line();
  bool is_horizontal_vertical();
  std::vector<Point> get_points();
};

Line::Line(unsigned int x1, unsigned int x2, unsigned int y1, unsigned int y2) {
  min_x = (x1 > x2) ? x2 : x1;
  min_y = (y1 > y2) ? y2 : y1;

  max_x = (x1 > x2) ? x1 : x2;
  max_y = (y1 > y2) ? y1 : y2;
}

std::vector<Point> Line::get_points() {
  std::vector<Point> result;

  for (size_t y = min_y; y <= max_y; y++) {
    for (size_t x = min_x; x <= max_x; x++) {
      result.push_back(Point(x, y));
    }
  }

  return result;
}

Line::~Line() {}

bool Line::is_horizontal_vertical() { return min_x == max_x || min_y == max_y; }

int main(int argc, char const* argv[]) {
  std::array<std::array<unsigned int, 1000>, 1000> canvas;
  std::vector<Line> lines;

  for (size_t i = 0; i < 1000; i++) {
    for (size_t j = 0; j < 1000; j++) {
      canvas[i][j] = 0;
    }
  }

  while (std::cin) {
    std::string next_line;

    std::getline(std::cin, next_line);
    if (next_line.length() < 2) {
      break;
    }

    std::stringstream next_line_stream(next_line);
    std::string token;

    unsigned int x1, y1, x2, y2;

    getline(next_line_stream, token, ',');
    x1 = std::stoi(token);
    getline(next_line_stream, token, ' ');
    y1 = std::stoi(token);

    getline(next_line_stream, token, ' ');

    getline(next_line_stream, token, ',');
    x2 = std::stoi(token);
    getline(next_line_stream, token, '\n');
    y2 = std::stoi(token);

    // std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;

    lines.push_back(Line(x1, x2, y1, y2));
  }

  for (auto line : lines) {
    if (line.is_horizontal_vertical()) {
      std::vector<Point> points = line.get_points();
      for (auto point : points) {
        canvas[point.x][point.y] += 1;
      }
    }
  }

  int tot = 0;

  for (size_t i = 0; i < 1000; i++) {
    for (size_t j = 0; j < 1000; j++) {
      if (canvas[j][i] == 0) {
        std::cout << '.';
      } else {
        std::cout << canvas[j][i];
      }

      if (canvas[i][j] > 1) {
        tot++;
      }
    }
    std::cout << std::endl;
  }

  std::cout << tot << std::endl;

  return 0;
}