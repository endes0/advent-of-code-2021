#include <array>
#include <iostream>
#include <string>
#include <vector>

int main(int argc, char const *argv[]) {
  int total = 0;
  unsigned int alpha = 0, gamma = 0;
  std::string in;
  std::array<int, 12> common{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  while (std::cin >> in) {
    for (size_t i = 0; i < common.size(); ++i) {
      if (in[i] == '1') {
        common[i]++;
      }
    }
    total++;
  }

  for (int i = 0; i < common.size(); i++) {
    std::cout << common[i] << " ";

    alpha = alpha << 1;
    gamma = gamma << 1;
    if (total - common[i] < common[i]) {
      std::cout << 1;
      alpha++;
    } else {
      std::cout << 0;
      gamma++;
    }

    std::cout << std::endl;
  }

  std::cout << alpha << std::endl;
  std::cout << gamma << std::endl;
  std::cout << alpha * gamma << std::endl;

  return 0;
}
