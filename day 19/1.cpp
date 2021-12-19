#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Point {
  int x, y, z;

  Point(unsigned int x_, unsigned int y_, unsigned int z_) {
    x = x_;
    y = y_;
    z = z_;
  }

  Point() {}

  // 0 to 5, 6 posibilities
  void change_dir(unsigned int dir) {
    unsigned int tmp;

    switch (dir) {
      case 2:  //
        tmp = x;
        x = y;
        y = z;
        z = tmp;
        break;
      case 4:  //
        tmp = x;
        x = z;
        z = y;
        y = tmp;
        break;

      case 3:
        tmp = y;
        y = z;
        z = tmp;
        break;
      case 1:
        tmp = x;
        x = z;
        z = tmp;
        break;
      case 5:
        tmp = x;
        x = y;
        y = tmp;
        break;
      default:
        break;
    }
  }

  // 0 to 3, 4 inversions
  void change_norm(unsigned int dir) {
    unsigned int tmp;

    switch (dir) {
      case 1:
        x = -x;
        y = -y;
        break;
      case 2:
        x = -x;
        z = -z;
        break;
      case 3:
        y = -y;
        z = -z;
        break;
      default:
        break;
    }
  }

  friend bool operator==(const Point &l, const Point &r) {
    return l.x == r.x && l.y == r.y && l.z == r.z;  // keep the same order
  }

  friend bool operator<(const Point &l, const Point &r) {
    return l.x < r.x || (l.x == r.x && l.y < r.y) ||
           (l.x == r.x && l.y == r.y && l.z < r.z);  // keep the same order
  }

  friend Point operator+(const Point &l, const Point &r) {
    return Point(l.x + r.x, l.y + r.y, l.z + r.z);  // keep the same order
  }

  friend Point operator-(const Point &l, const Point &r) {
    return Point(l.x - r.x, l.y - r.y, l.z - r.z);  // keep the same order
  }
};

std::vector<std::vector<Point>> get_rotations(
    std::vector<Point> scanner_input) {
  std::vector<std::vector<Point>> final;
  for (size_t i = 0; i < 6; i++) {
    for (size_t j = 0; j < 4; j++) {
      std::vector<Point> new_points;
      for (auto point : scanner_input) {
        point.change_dir(i);
        point.change_norm(j);
        if (i % 2 != 0) {
          point = Point(0, 0, 0) - point;
        }

        new_points.push_back(point);
      }
      final.push_back(new_points);
    }
  }

  return final;
}

int main(int argc, char const *argv[]) {
  std::vector<std::vector<Point>> scanners;
  std::string line;

  while (std::getline(std::cin, line)) {
    if (line[1] == '-') {
      scanners.push_back({});
    } else if (line != "") {
      std::stringstream line_stream(line);
      std::string x;
      std::string y;
      std::string z;
      std::getline(line_stream, x, ',');
      std::getline(line_stream, y, ',');
      std::getline(line_stream, z, ',');
      Point point(std::stoi(x), std::stoi(y), std::stoi(z));

      scanners.back().push_back(point);
    }
  }

  std::set<Point> map;
  std::set<Point> scanners_map;
  for (auto point : scanners[0]) {
    map.insert(point);
  }

  for (size_t i = 1; i < scanners.size(); i++) {
    bool found = false;
    for (auto points : get_rotations(scanners[i])) {
      for (auto map_reference_point : map) {
        for (auto scan_reference_point : points) {
          size_t coincidences = 0;
          std::vector<Point> not_coincide;

          for (auto point : points) {
            if (point == scan_reference_point) {
              continue;
            }

            Point should_coincide =
                point - scan_reference_point + map_reference_point;
            if (should_coincide.x == 1135 && should_coincide.y == -1161 &&
                should_coincide.z == 1235) {
            }

            if (map.find(should_coincide) != map.end()) {
              coincidences++;
            } else {
              not_coincide.push_back(should_coincide);
            }
          }

          if (coincidences > 10) {
            scanners_map.insert(map_reference_point - scan_reference_point);
            for (auto new_point : not_coincide) {
              map.insert(new_point);
            }
            found = true;
            break;
          }
        }

        if (found) {
          break;
        }
      }
      if (found) {
        break;
      }
    }
    if (!found) {
      std::cout << "ups " << i << std::endl;
      scanners.push_back(scanners[i]);
    }
  }

  std::cout << map.size() << std::endl;
  for (auto beacon : map) {
    std::cout << beacon.x << "," << beacon.y << "," << beacon.z << std::endl;
  }

  std::cout << std::endl;

  unsigned int max_dist = 0;
  for (auto scanner : scanners_map) {
    std::cout << scanner.x << "," << scanner.y << "," << scanner.z << std::endl;
    for (auto scanner2 : scanners_map) {
      unsigned int dist = abs(scanner.x - scanner2.x) +
                          abs(scanner.y - scanner2.y) +
                          abs(scanner.z - scanner2.z);
      if (dist > max_dist) {
        max_dist = dist;
      }
    }
  }

  std::cout << max_dist << std::endl;

  return 0;
}
