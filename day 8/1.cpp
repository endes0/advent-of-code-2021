#include <array>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

int main(int argc, char const *argv[]) {
  int total = 0;
  std::string read;
  while (std::getline(std::cin, read, '|')) {
    std::stringstream next_line_stream(read);
    std::string token;
    std::set<std::string> inputs;

    while (getline(next_line_stream, token, ' ')) {

    }

    std::getline(std::cin, read);
    std::stringstream second_line_stream(read);
    while (getline(second_line_stream, token, ' ')) {
      if (token.length() == 2 || token.length() == 7 || token.length() == 4 ||
          token.length() == 3) {
        total++;
      }
    }
  }

  std::cout << total << std::endl;

  return 0;
}
