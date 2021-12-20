#include <iostream>
#include <string>
#include <vector>

void print_image(std::vector<std::vector<bool>> image) {
  for (auto line : image) {
    for (auto pixel : line) {
      std::cout << ((pixel) ? "#" : ".");
    }

    std::cout << std::endl;
  }
}

std::vector<std::vector<bool>> apply_algorithm(
    std::vector<std::vector<bool>> image, std::string algorithm) {
  std::vector<std::vector<bool>> final = image;
  for (size_t center_y = 0; center_y < image.size(); center_y++) {
    for (size_t center_x = 0; center_x < image[0].size(); center_x++) {
      size_t num = 0;

      for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2; j++) {
          int y = center_y + i;
          int x = center_x + j;

          num = num << 1;

          if (x > 0 && y > 0 && y < image.size() && x < image[0].size() &&
              image[y][x]) {
            num++;
          }
        }
      }

      if (algorithm[num] == '#') {
        final[center_y][center_x] = true;
      } else {
        final[center_y][center_x] = false;
      }
    }
  }

  return final;
}

int main(int argc, char const *argv[]) {
  std::string algorithm;
  std::getline(std::cin, algorithm);

  std::vector<std::vector<bool>> image;
  std::string line;
  bool first = true;
  while (std::getline(std::cin, line)) {
    if (line != "") {
      if (first) {
        for (size_t i = 0; i < 11; i++) {
          image.push_back({});
          for (size_t j = 0; j < 22 + line.length(); j++) {
            image.back().push_back(false);
          }
        }

        first = false;
      }

      image.push_back({0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0});

      for (auto c : line) {
        image.back().push_back(c == '#');
      }

      for (size_t i = 0; i < 11; i++) {
        image.back().push_back(0);
      }
    }
  }
  size_t last_len = image.back().size();
  for (size_t i = 0; i < 11; i++) {
    image.push_back({});
    for (size_t j = 0; j < last_len; j++) {
      image.back().push_back(false);
    }
  }

  print_image(image);
  std::cout << std::endl;

  image = apply_algorithm(image, algorithm);
  print_image(image);
  std::cout << std::endl;

  image = apply_algorithm(image, algorithm);
  print_image(image);

  size_t count = 0;
  for (size_t i = 1; i < image.size() - 1; i++) {
    for (size_t j = 1; j < image[0].size() - 1; j++) {
      if (image[i][j]) {
        count++;
      }
    }
  }

  std::cout << count << std::endl;

  return 0;
}
