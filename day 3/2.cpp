#include <array>
#include <iostream>
#include <string>
#include <vector>

std::string getTheCommon(std::vector<std::string> list, bool is_major) {
  std::vector<int> count;
  std::string result;
  for (int i = 0; i < list.size(); i++) {
    int pos = 0;
    for (auto character : list[i]) {
      if ((character == '1' || character == '0') && count.size() < pos + 1) {
        count.push_back(0);
      }

      if (character == '1') {
        count[pos]++;
      }

      pos++;
    }
  }

  for (auto col : count) {
    if (list.size() - col < col) {
      result += (is_major) ? '1' : '0';
    } else if (list.size() - col == col) {
      result += "x";
    } else {
      result += (is_major) ? '0' : '1';
    }
  }

  return result;
}

std::string getTheNumber(std::vector<std::string> list, bool is_major) {
  size_t pos = 0;
  while (list.size() > 1) {
    std::string comm = getTheCommon(list, true);
    std::vector<std::string> result;

    for (auto num : list) {
      if (num[pos] == comm[pos]) {
        result.push_back(num);
      }
    }

    list = result;

    pos++;
  }

  return list[0];
}

int main(int argc, char const *argv[]) {
  std::string in;
  std::string major;
  std::string minor;
  std::vector<std::string> list;

  while (std::cin >> in) {
    list.push_back(in);
  }

  major = getTheNumber(list, true);
  minor = getTheNumber(list, false);

  std::cout << major << std::endl;
  std::cout << minor << std::endl;
  std::cout << std::stoi(major, nullptr, 2) << std::endl;
  std::cout << std::stoi(minor, nullptr, 2) << std::endl;
  std::cout << std::stoi(major, nullptr, 2) * std::stoi(minor, nullptr, 2)
            << std::endl;

  return 0;
}
