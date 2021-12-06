#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

class Fish {
 private:
  unsigned int timer_;
  unsigned long long multiplier_;
  // bool first_cycle = true;

 public:
  Fish(unsigned int timer, unsigned long multiplier);
  Fish();
  ~Fish();

  void next_day();
  bool is_spawning();
  unsigned long long how_many();
};

Fish::Fish() { timer_ = 8; }

Fish::Fish(unsigned int timer, unsigned long multiplier) {
  timer_ = timer;
  multiplier_ = multiplier;
  // first_cycle = false;
}

Fish::~Fish() {}

void Fish::next_day() {
  /*if (first_cycle) {
    first_cycle = false;
    return;
  }*/
  if (timer_ == 0) {
    timer_ = 6;
    return;
  }

  timer_--;
}

bool Fish::is_spawning() { return timer_ == 0; }
unsigned long long Fish::how_many() { return multiplier_; }

int main(int argc, char const *argv[]) {
  std::vector<Fish> fishs;
  unsigned long long total_fish = 0;

  std::string num;
  std::multiset<unsigned int> same;
  while (std::getline(std::cin, num, ',')) {
    same.insert(std::stoi(num));
    total_fish++;
  }

  unsigned int old = 0;
  int mult = 1;
  bool first_cycle = true;
  for (auto fish : same) {
    if (first_cycle) {
      old = fish;
      first_cycle = false;
    } else if (old != fish) {
      fishs.push_back(Fish(old, mult));
      mult = 1;
      old = fish;
    } else {
      mult++;
    }
  }
  fishs.push_back(Fish(old, mult));

  for (size_t i = 0; i < 257; i++) {
    size_t until = fishs.size();
    unsigned long long mult = 0;
    for (size_t j = 0; j < until; j++) {
      if (fishs[j].is_spawning()) {
        mult += fishs[j].how_many();
      }

      fishs[j].next_day();
    }
    if (mult > 0) {
      fishs.push_back(Fish(8, mult));
      total_fish += mult;
    }

    std::cout << "After " << i + 1 << " days: " << total_fish << " "
              << fishs.size() << std::endl;
  }

  return 0;
}
