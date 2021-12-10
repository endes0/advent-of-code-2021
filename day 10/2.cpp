#include <algorithm>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
  std::string line;
  std::set<long> totals;

  while (std::cin >> line) {
    std::vector<char> stack;
    bool corrupted = false;
    long total = 0;

    for (auto c : line) {
      if (c == '{' || c == '(' || c == '<' || c == '[') {
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
          corrupted = true;
          break;
        } else {
          stack.pop_back();
        }
      }
    }

    if (!corrupted) {
      std::for_each(stack.rbegin(), stack.rend(),
                    [&total](char i) { /*code*/
                                       int sum = 0;
                                       switch (i) {
                                         case '(':
                                           sum = 1;
                                           break;
                                         case '[':
                                           sum = 2;
                                           break;
                                         case '{':
                                           sum = 3;
                                           break;
                                         case '<':
                                           sum = 4;
                                           break;
                                         default:
                                           break;
                                       }
                                       total *= 5;
                                       total += sum;
                    });
      totals.insert(total);
    }
  }

  for (auto total : totals) {
    std::cout << total << std::endl;
  }

  // size_t pos = totals.size() / 2;
  auto it = totals.begin();
  for (size_t i = 0; i < totals.size() / 2; i++) {
    it++;
  }

  std::cout << std::endl;
  std::cout << *it << std::endl;

  return 0;
}
