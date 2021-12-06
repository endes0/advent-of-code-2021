#include <array>
#include <iostream>
#include <string>
#include <vector>

class Fish {
 private:
  unsigned int timer_;
  //bool first_cycle = true;

 public:
  Fish(unsigned int timer);
  Fish();
  ~Fish();

  void next_day();
  bool is_spawning();
};

Fish::Fish() { timer_ = 8; }

Fish::Fish(unsigned int timer) {
  timer_ = timer;
  //first_cycle = false;
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

int main(int argc, char const *argv[]) {
  std::vector<Fish> fishs;

  std::string num;
  while (std::getline(std::cin, num, ',')) {
    fishs.push_back(Fish(std::stoi(num)));
  }

  for (size_t i = 0; i < 80; i++) {
    size_t until = fishs.size();
    for (size_t j = 0; j < until; j++) {
      if (fishs[j].is_spawning()) {
        fishs.push_back(Fish());
      }

      fishs[j].next_day();
    }

    std::cout << "After " << i+1 << " days: " << fishs.size() << std::endl;
  }

  return 0;
}
