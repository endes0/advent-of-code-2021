#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
  int measurement = 0;
  std::vector<std::vector<int>> windows;
  std::vector<int> sums;

  //windows.push_back({0, 0, 0});

  int size = 0;
  while (std::cin >> measurement) {

    windows.push_back({});

    size = windows.size();

    for (int i = size-1; i >= 0 && i >= size-3; i--)
    {
      windows[i].push_back(measurement);
    }
    
  }

  for (size_t i = 0; i < windows.size(); i++)
  {
    sums.push_back(0);
    for (size_t j = 0; j < windows[i].size(); j++)
    {
      sums[i] += windows[i][j];
    }
    
    std::cout << sums[i];
    if (i > 0 && sums[i-1] < sums[i])
    {
      std::cout << " Increased" << std::endl;
    } else {
      std::cout << std::endl;
    }
    
  }
  

  return 0;
}
