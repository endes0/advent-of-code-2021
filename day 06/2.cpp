#include <math.h>

#include <array>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#define LOADBMP_IMPLEMENTATION
#include "../day 05/LoadBMP/loadbmp.h"

class Fish {
 private:
  unsigned int timer_;
  unsigned long long multiplier_;

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
}

Fish::~Fish() {}

void Fish::next_day() {
  if (timer_ == 0) {
    timer_ = 6;
    return;
  }

  timer_--;
}

bool Fish::is_spawning() { return timer_ == 0; }
unsigned long long Fish::how_many() { return multiplier_; }

int main(int argc, char const *argv[]) {
  // 1 pixel = 1000 m³ aprox
  unsigned char pixels[1161 * 1161 * 3];

  for (size_t i = 0; i < 300 * 300 * 3; i++) {
    pixels[i] = 0;
  }

  std::vector<Fish> fishs;
  unsigned long long total_fish = 0;
  unsigned long long last_filled = 0;

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

  for (size_t i = 0; i < 298; i++) {
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

    // 1 fish (aprox 15 x 5 x 1 cms) is 0.000075 m³
    // So there will be aprox 13 333 333 fishes for pixel

    for (unsigned long long j = last_filled;
         j < total_fish / 13333333 && j < 1161 * 1161; j++) {
      size_t pix_pos = j * 3;

      // Lets make colors with the day
      float h = (i-120)/180.0 * 360;
      float s = ((100-i*0.15)) / 100.0;
      float v = ((i % 2 == 1) * 60.0 + (i % 2 == 0) * 40.0) / 100.0;
      float C = s * v;
      float X = C * (1 - fabs(fmod(h / 60.0, 2.0) - 1));
      float m = v - C;
      float r, g, b;
      if (h >= 0 && h < 60) {
        r = C, g = X, b = 0;
      } else if (h >= 60 && h < 120) {
        r = X, g = C, b = 0;
      } else if (h >= 120 && h < 180) {
        r = 0, g = C, b = X;
      } else if (h >= 180 && h < 240) {
        r = 0, g = X, b = C;
      } else if (h >= 240 && h < 300) {
        r = X, g = 0, b = C;
      } else {
        r = C, g = 0, b = X;
      }
      pixels[pix_pos] = (r + m) * 255;
      pixels[pix_pos + 1] = (g + m) * 255;
      pixels[pix_pos + 2] = (b + m) * 255;
    }
    last_filled = total_fish / 13333333;

    std::cout << "After " << i + 1 << " days: " << total_fish << " "
              << fishs.size() << std::endl;
  }

  unsigned int err =
      loadbmp_encode_file("image.bmp", pixels, 1161, 1161, LOADBMP_RGB);

  if (err) printf("LoadBMP Load Error: %u\n", err);

  return 0;
}
