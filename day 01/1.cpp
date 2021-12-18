#include <iostream>

int main(int argc, char const *argv[]) {
  int current = 0, previous = 0;

  std::cin >> previous;

  while (std::cin >> current) {
    if (current > previous) {
      std::cout << "Increased" << std::endl;
    } else if (current < previous) {
      std::cout << "Decreased" << std::endl;
    } else {
      std::cout << "Same" << std::endl;
    }

    previous = current;
  }

  return 0;
}
