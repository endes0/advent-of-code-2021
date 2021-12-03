#include <iostream>
#include <string>

int main(int argc, char const *argv[]) {
  std::string cmd = "";
  int x = 0;

  int depth = 0;
  int horizontal = 0;

  while (std::cin >> cmd) {
    std::cin >> x;

    if (cmd == "forward") {
      horizontal += x;
    } else if (cmd == "backward") {
      horizontal -= x;
    } else if (cmd == "up") {
      depth -= x;
    } else if (cmd == "down") {
      depth += x;
    }
  }

  std::cout << depth << std::endl;
  std::cout << horizontal << std::endl;
  std::cout << horizontal * depth << std::endl;


  return 0;
}
