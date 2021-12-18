#include <iostream>
#include <string>

struct Point {
  long x, y;

  Point(long x_, long y_) {
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
};

int main(int argc, char const *argv[]) {
  long min_x, max_x, min_y, max_y;
  std::cin >> min_x >> max_x >> min_y >> max_y;
  Point last_max_p;
  long last_max = -1;
  unsigned int count = 0;

  for (size_t i = 0; i <= 1000; i++) {
    for (int j = -89; j < 1000; j++) {
      Point current_pos(0, 0);
      Point current_vel(i, j);
      Point current_max_y;
      long current_max = -2;

      while (true) {
        current_pos.x += current_vel.x;
        current_pos.y += current_vel.y;

        current_vel.x += (current_vel.x < 0) ? 1 : (current_vel.x > 0) ? -1 : 0;
        current_vel.y -= 1;

        if (current_vel.y == 0) {
          current_max = current_pos.y;
          current_max_y = Point(i, j);
        }

        if (current_pos.x >= min_x && current_pos.x <= max_x &&
            current_pos.y <= min_y && current_pos.y >= max_y) {
          count++;
          if (current_max > last_max) {
            last_max = current_max;
            last_max_p = current_max_y;
          }
          break;
        } else if (current_pos.x > max_x || current_pos.y < max_y) {
          break;
        }
      }
    }
  }

  std::cout << last_max_p.x << " " << last_max_p.y << " " << last_max << " "
            << count << std::endl;

  return 0;
}
