#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

const std::set<char> num0{'a', 'b', 'c', 'e', 'f', 'g'};       //
const std::set<char> num1{'c', 'f'};                           //
const std::set<char> num2{'a', 'c', 'd', 'e', 'g'};            //
const std::set<char> num3{'a', 'c', 'd', 'f', 'g'};            //
const std::set<char> num4{'b', 'c', 'd', 'f'};                 //
const std::set<char> num5{'a', 'b', 'd', 'f', 'g'};            //
const std::set<char> num6{'a', 'b', 'd', 'e', 'f', 'g'};       //
const std::set<char> num7{'a', 'c', 'f'};                      //
const std::set<char> num8{'a', 'b', 'c', 'd', 'e', 'f', 'g'};  //
const std::set<char> num9{'a', 'b', 'c', 'd', 'f', 'g'};       //

const std::vector<std::set<char>> nums5{num2, num3, num5};
const std::vector<std::set<char>> nums6{num0, num6, num9};

// trim from start (in place)
static inline void ltrim(std::string &s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
  s.erase(std::find_if(s.rbegin(), s.rend(),
                       [](unsigned char ch) { return !std::isspace(ch); })
              .base(),
          s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
  ltrim(s);
  rtrim(s);
}

std::set<char> intersect_with(std::set<char> first, std::set<char> second) {
  if (first.size() == 0) {
    return second;
  }
  std::set<char> result;
  std::vector<char> v_intersection;

  std::set_intersection(first.begin(), first.end(), second.begin(),
                        second.end(), std::back_inserter(v_intersection));

  for (auto elem : v_intersection) {
    result.insert(elem);
  }

  return result;
}

int main(int argc, char const *argv[]) {
  int total = 0;
  std::string read;
  while (std::getline(std::cin, read, '|')) {
    std::stringstream next_line_stream(read);
    std::string token;
    std::map<char, std::set<char>> inputs;
    std::vector<std::string> to_analize;
    std::map<int, std::set<char>> to_analize_info;

    while (getline(next_line_stream, token, ' ')) {
      trim(token);
      if (token.length() == 2) {
        inputs[token[0]] = intersect_with(inputs[token[0]], num1);
        inputs[token[1]] = intersect_with(inputs[token[1]], num1);
        to_analize_info[1].insert(token[0]);
        to_analize_info[1].insert(token[1]);
      } else if (token.length() == 4) {
        for (auto t : token) {
          inputs[t] = intersect_with(inputs[t], num4);
          to_analize_info[4].insert(t);
        }
      } else if (token.length() == 3) {
        for (auto t : token) {
          inputs[t] = intersect_with(inputs[t], num7);
          to_analize_info[7].insert(t);
        }
      } else if (token.length() == 7) {
        for (auto t : token) {
          inputs[t] = intersect_with(inputs[t], num8);
          to_analize_info[8].insert(t);
        }
      } else {
        to_analize.push_back(token);
      }
    }

    for (auto elem : to_analize) {
      std::set<char> input;
      for (auto e : elem) {
        input.insert(e);
      }

      if (elem.length() == 5) {
        if (to_analize_info[1].size() > 0 &&
                intersect_with(input, to_analize_info[1]).size() == 2 ||
            (to_analize_info[4].size() > 0 &&
             intersect_with(input, to_analize_info[4]).size() == 3 &&
             to_analize_info[7].size() > 0 &&
             intersect_with(input, to_analize_info[7]).size() == 3)) {
          // Its 3
          for (auto t : elem) {
            inputs[t] = intersect_with(inputs[t], num3);
            to_analize_info[3].insert(t);
          }
        } else if (to_analize_info[4].size() > 0 &&
                   intersect_with(input, to_analize_info[4]).size() == 2) {
          // its 2
          for (auto t : elem) {
            inputs[t] = intersect_with(inputs[t], num2);
            to_analize_info[2].insert(t);
          }
        } else if (to_analize_info[4].size() > 0 &&
                   intersect_with(input, to_analize_info[4]).size() == 3) {
          // its 5
          for (auto t : elem) {
            inputs[t] = intersect_with(inputs[t], num5);
            to_analize_info[5].insert(t);
          }
        } else {
          throw "ups";
        }

      } else if (elem.length() == 6) {
        if ((intersect_with(input, to_analize_info[7]).size() == 2)) {
          // its 6
          for (auto t : elem) {
            inputs[t] = intersect_with(inputs[t], num6);
            to_analize_info[6].insert(t);
          }
        } else if (  //(intersect_with(input, to_analize_info[2]).size() == 4)
            (intersect_with(input, to_analize_info[3]).size() == 4) ||
            (intersect_with(input, to_analize_info[4]).size() == 3) ||
            (intersect_with(input, to_analize_info[5]).size() == 4)
            //(intersect_with(input, to_analize_info[7]).size() == 3) ||
            //(intersect_with(input, to_analize_info[8]).size() == 6)
        ) {
          // its 0
          for (auto t : elem) {
            inputs[t] = intersect_with(inputs[t], num0);
            to_analize_info[0].insert(t);
          }
        } else {
          // its 9
          for (auto t : elem) {
            inputs[t] = intersect_with(inputs[t], num9);
            to_analize_info[9].insert(t);
          }
        }

      } else {
        std::cout << elem << std::endl;
        throw "ups";
      }
    }

    for (auto elem : to_analize_info) {
      std::cout << elem.first << ": ";
      for (auto comb : elem.second) {
        std::cout << comb;
      }
      std::cout << std::endl;
    }

    std::getline(std::cin, read);
    std::stringstream second_line_stream(read);
    std::string final = "0";
    while (getline(second_line_stream, token, ' ')) {
      trim(token);
      std::set<char> number;
      for (auto c : token) {
        number.insert(c);
      }

      for (auto comb : to_analize_info) {
        if (comb.second == number) {
          final += std::to_string(comb.first);
          break;
        }
      }

      std::cout << final << std::endl;
    }
    total += std::stoi(final);
    std::cout << std::endl;
  }

  std::cout << total << std::endl;

  return 0;
}
