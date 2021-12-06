#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define LOADBMP_IMPLEMENTATION
#include "../day 5/LoadBMP/loadbmp.h"

class Fish {
 private:
  unsigned int timer_;
  unsigned long long multiplier_;
  // bool first_cycle = true;

 public:
  Fish(unsigned int timer, unsigned long multiplier, unsigned char r,
       unsigned char g, unsigned char b);
  Fish();
  ~Fish();

  void next_day();
  bool is_spawning();
  unsigned long long how_many();

  unsigned char r_;
  unsigned char g_;
  unsigned char b_;
};

Fish::Fish() { timer_ = 8; }

Fish::Fish(unsigned int timer, unsigned long multiplier, unsigned char r,
           unsigned char g, unsigned char b) {
  timer_ = timer;
  multiplier_ = multiplier;
  // first_cycle = false;

  r_ = r;
  g_ = g;
  b_ = b;
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
  unsigned char pixels[300 * 300 * 3];

  for (size_t i = 0; i < 300 * 300 * 3; i++) {
    pixels[i] = 0;
  }

  std::vector<Fish> fishs;
  unsigned long long total_fish = 0;

  std::string num;
  std::multiset<unsigned int> same;
  while (std::getline(std::cin, num, ',')) {
    same.insert(std::stoi(num));
    total_fish++;
  }

  std::array<std::array<unsigned char, 3>, 5> colors{{{0xFF, 0x00, 0x00},
                                                      {0x00, 0xFF, 0x00},
                                                      {0x00, 0x00, 0xFF},
                                                      {0x7F, 0x7F, 0x00},
                                                      {0x00, 0x7F, 0x7F}}};
  size_t color_i = 0;

  unsigned int old = 0;
  int mult = 1;
  bool first_cycle = true;
  for (auto fish : same) {
    if (first_cycle) {
      old = fish;
      first_cycle = false;
    } else if (old != fish) {
      fishs.push_back(Fish(old, mult, colors[color_i][0], colors[color_i][1],
                           colors[color_i][2]));
      mult = 1;
      old = fish;

      color_i++;
    } else {
      mult++;
    }
  }
  fishs.push_back(Fish(old, mult, colors[color_i][0], colors[color_i][1],
                       colors[color_i][2]));

  for (size_t i = 0; i < 298; i++) {
    size_t until = fishs.size();
    unsigned long long mult = 0;

    unsigned char new_r = 0, new_g = 0, new_b = 0;
    for (size_t j = 0; j < until; j++) {
      float atenuator =
          static_cast<float>(fishs[j].how_many()) /
          static_cast<float>(total_fish /
                             ((static_cast<float>(i) * (10.0 / 300.0)) + 1));
      if (atenuator < 0.05) {
        atenuator = 0.05;
      }

      if (fishs[j].is_spawning()) {
        mult += fishs[j].how_many();

        new_r += fishs[j].r_;  //* atenuator;
        new_g += fishs[j].g_;  //* atenuator;
        new_b += fishs[j].b_;  //* atenuator;
      }

      size_t pix_pos = j * 3;
      size_t colum_pos = i * 300 * 3;

      pixels[colum_pos + pix_pos] = fishs[j].r_ * atenuator;
      pixels[colum_pos + pix_pos + 1] = fishs[j].g_ * atenuator;
      pixels[colum_pos + pix_pos + 2] = fishs[j].b_ * atenuator;

      fishs[j].next_day();
    }
    if (mult > 0) {
      fishs.push_back(Fish(8, mult, new_r, new_g, new_b));
      total_fish += mult;

      new_r = 0;
      new_g = 0;
      new_b = 0;
    }

    std::cout << "After " << i + 1 << " days: " << total_fish << " "
              << fishs.size() << std::endl;
  }

  unsigned int err =
      loadbmp_encode_file("image.bmp", pixels, 300, 300, LOADBMP_RGB);

  if (err) printf("LoadBMP Load Error: %u\n", err);

  return 0;
}
