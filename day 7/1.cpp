#include <array>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
  std::vector<int> submarines;
  int max;
  int min;

  bool first = true;
  std::string read;
  int num;
  while (std::getline(std::cin, read, ',')) {
    num = std::stoi(read);

    submarines.push_back(num);
    if (first) {
      max = num;
      min = num;
      first = false;
    } else {
      if (num > max) {
        max = num;
      } else if (num < min) {
        min = num;
      }
    }
  }

  first = true;
  int least_cost, least_pos;
  for (size_t i = min; i <= max; i++) {
    int cost = 0;
    for (auto pos : submarines) {
        int step = abs(i - pos);
        cost += step;
    }

    if (first || cost < least_cost) {
      least_cost = cost;
      least_pos = i;
      first = false;
    }
  }

  std::cout << least_pos << " " << least_cost << std::endl;

  return 0;
}
