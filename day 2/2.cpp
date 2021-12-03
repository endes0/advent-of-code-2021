#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  std::string cmd = "";
  int x = 0;

  int depth = 0;
  int horizontal = 0;
  int aim = 0;

  while (std::cin >> cmd) {
    std::cin >> x;

    if (cmd == "forward") {
      horizontal += x;
      depth += x * aim;
    } else if (cmd == "up") {
      aim -= x;
    } else if (cmd == "down") {
      aim += x;
    }
  }

  std::cout << depth << std::endl;
  std::cout << horizontal << std::endl;
  std::cout << horizontal * depth << std::endl;


  return 0;
}
