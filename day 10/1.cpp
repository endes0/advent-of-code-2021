#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
  std::string line;
  int total = 0;
  while (std::cin >> line) {
    std::map<char, int> tokens;
    std::vector<char> stack;
    for (auto c : line) {
      if (c == '{' || c == '(' || c == '<' || c == '[') {
        tokens[c] += 1;
        stack.push_back(c);
      } else {
        char mander;
        switch (c) {
          case ')':
            mander = '(';
            break;
          case ']':
            mander = '[';
            break;
          case '}':
            mander = '{';
            break;
          case '>':
            mander = '<';
            break;
          default:
            break;
        }
        if (stack[stack.size() - 1] != mander) {
          std::cout << line << " " << c << std::endl;
          switch (c) {
            case ')':
              total += 3;
              break;
            case ']':
              total += 57;
              break;
            case '}':
              total += 1197;
              break;
            case '>':
              total += 25137;
              break;
            default:
              break;
          }
          break;
        } else {
            stack.pop_back();
        }
      }
    }
  }

  std::cout << total << std::endl;

  return 0;
}
