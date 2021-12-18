#include <math.h>

#include <array>
#include <iostream>
#include <string>
#include <vector>

#define LOADBMP_IMPLEMENTATION
#include "../day 05/LoadBMP/loadbmp.h"

int main(int argc, char const *argv[]) {
  unsigned char pixels[1500 * 1000 * 3];
  std::vector<int> submarines;
  int max;
  int min;

  for (size_t i = 0; i < 1500 * 1000 * 3; i++) {
    pixels[i] = 0;
  }

  bool first = true;
  std::string read;
  int num;
  while (std::getline(std::cin, read, ',')) {
    num = std::stoi(read);

    submarines.push_back(num);
    if (first) {
      max = num;
      min = num;
      first = false;
    } else {
      if (num > max) {
        max = num;
      } else if (num < min) {
        min = num;
      }
    }
  }

  first = true;
  int least_cost, least_pos;
  for (size_t i = min; i <= max; i++) {
    int cost = 0;
    for (auto pos : submarines) {
      int step = abs(static_cast<int>(i) - pos);
      cost += ((step * (step + 1)) / 2);
    }

    if (first || cost < least_cost) {
      least_cost = cost;
      least_pos = i;
      first = false;
    }
  }

  std::cout << least_pos << " " << least_cost << std::endl;

  for (size_t i = 0; i < submarines.size(); i++) {
    int min, max;
    bool reverse = false;
    if (submarines[i] > least_pos) {
      max = submarines[i];
      min = least_pos;
      reverse = true;
    } else {
      min = submarines[i];
      max = least_pos;
    }

    for (size_t j = min; j <= max; j++) {
      size_t pix_pos = i * 1500 * 3 + j * 3;

      float h = static_cast<float>(i) / submarines.size() * 360;
      float s = 50.0 / 100.0;
      float v = (reverse) ? static_cast<float>(max - j) / (max-min)
                          : static_cast<float>(j) / max;
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
  }

  unsigned int err =
      loadbmp_encode_file("image.bmp", pixels, 1500, 1000, LOADBMP_RGB);

  if (err) printf("LoadBMP Load Error: %u\n", err);

  return 0;
}
