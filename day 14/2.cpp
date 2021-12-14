#include <array>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

std::map<std::string, unsigned long long> result_polymer(std::map<std::string, unsigned long long> polymer,
                                          std::map<std::string, char> rules,
                                          std::map<char, unsigned long long> &count) {
  std::map<std::string, unsigned long long> result;

  for (auto pair : polymer) {
    if (rules.find(pair.first) != rules.end()) {
      std::string new_pair;
      std::string new_pair_2;

      new_pair += pair.first[0];
      new_pair += rules[pair.first];

      new_pair_2 += rules[pair.first];
      new_pair_2 += pair.first[1];

      result[new_pair] += pair.second;
      result[new_pair_2] += pair.second;

      count[rules[pair.first]] += pair.second;
    } else {
      result[pair.first] += pair.second;
    }
  }

  return result;
}

int main(int argc, char const *argv[]) {
  std::string templ;

  std::getline(std::cin, templ);

  std::map<std::string, char> rules;
  std::string token;
  while (std::getline(std::cin, token)) {
    std::stringstream token_stream(token);
    std::string pair;
    char result;

    std::getline(token_stream, pair, ' ');
    std::string discard;
    std::getline(token_stream, discard, ' ');
    token_stream >> result;

    rules[pair] = result;
  }

  std::map<char, unsigned long long> ocurrences;
  std::map<std::string, unsigned long long> first;
  for (size_t i = 0; i < templ.size() - 1; i++) {
    first[templ.substr(i, 2)] += 1;
    ocurrences[templ[i]] += 1;
  }
  ocurrences[templ[templ.size() - 1]] += 1;

  for (size_t i = 0; i < 40; i++) {
    first = result_polymer(first, rules, ocurrences);
    // std::cout << templ << " " << templ.length() << std::endl;
    std::cout << i << std::endl;
  }

  char most = templ[0];
  char least = templ[0];

  for (auto pair : ocurrences) {
    if (pair.second > ocurrences[most]) {
      most = pair.first;
    } else if (pair.second < ocurrences[least]) {
      least = pair.first;
    }
  }

  std::cout << ocurrences[most] - ocurrences[least] << std::endl;

  return 0;
}
