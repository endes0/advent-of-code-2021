#include <array>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

std::string result_polymer(std::string polymer,
                           std::map<std::string, char> rules) {
  std::string result;

  for (unsigned long long i = 0; i < polymer.length(); i++) {
    if (rules.find(polymer.substr(i, 2)) != rules.end()) {
      result += polymer[i];
      result += rules[polymer.substr(i, 2)];

    } else {
      result += polymer[i];
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

  for (size_t i = 0; i < 40; i++) {
    templ = result_polymer(templ, rules);
    //std::cout << templ << " " << templ.length() << std::endl;
    std::cout << i << std::endl;
  }

  std::map<char, unsigned long long> ocurrences;
  char most = templ[0];
  char least = templ[0];
  for (char mander : templ) {
    ocurrences[mander]++;
    if (ocurrences[mander] > ocurrences[most]) {
      most = mander;
    } else if (ocurrences[mander] < ocurrences[least]) {
      least = mander;
    }
  }

  std::cout << ocurrences[most] - ocurrences[least] << std::endl;

  return 0;
}
