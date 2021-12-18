#include <iostream>
#include <string>
#include <vector>

size_t num_len(std::string line) {
  for (size_t j = 0; j < line.length(); j++) {
    if (line[j] == ',' || line[j] == '[' || line[j] == ']') {
      return j;
    }
  }
  return line.length();
}

bool explode(std::string& line) {
  size_t last_left_i_number = 0;
  bool last_was_num = false;
  size_t open_brackets = 0;
  for (size_t i = 0; i < line.length(); i++) {
    if (line[i] == '[') {
      open_brackets++;
      last_was_num = false;

      if (open_brackets == 5) {
        size_t how_many_left = num_len(line.substr(i + 1));
        size_t how_many_right = num_len(line.substr(i + 2 + how_many_left));

        int left = std::stoi(line.substr(i + 1, how_many_left));
        int right =
            std::stoi(line.substr(i + how_many_left + 2, how_many_right));

        if (last_left_i_number > 0) {
          size_t last_left_len = num_len(line.substr(last_left_i_number));
          std::string new_num = std::to_string(
              left + std::stoi(line.substr(last_left_i_number, last_left_len)));
          line.replace(last_left_i_number, last_left_len, new_num);

          if (new_num.length() > last_left_len) {
            i += new_num.length() - last_left_len;
          }
        }

        size_t pair_end = i + how_many_left + how_many_right + 2;

        for (size_t j = pair_end; j < line.length(); j++) {
          if (!(line[j] == ',' || line[j] == '[' || line[j] == ']')) {
            size_t last_right_len = num_len(line.substr(j));
            line.replace(j, last_right_len,
                         std::to_string(right + std::stoi(line.substr(
                                                    j, last_right_len))));
            break;
          }
        }

        line.replace(i, pair_end + 1 - i, "0");
        return true;
      }

    } else if (line[i] == ']') {
      open_brackets--;
      last_was_num = false;
    } else if (line[i] != ',') {
      if (!last_was_num) {
        last_left_i_number = i;
      }
      last_was_num = true;
    } else {
      last_was_num = false;
    }
  }
  return false;
}

bool split(std::string& line) {
  bool last_was_num = false;
  size_t num_start = 0;
  for (size_t i = 0; i < line.length(); i++) {
    if (!(line[i] == ',' || line[i] == '[' || line[i] == ']')) {
      if (!last_was_num) {
        last_was_num = true;
        num_start = i;
      }
    } else {
      if (last_was_num && num_start != i - 1) {
        int num = std::stoi(line.substr(num_start, i - num_start));
        std::string pair = "[";
        pair += std::to_string(num / 2);
        pair += ",";
        pair += std::to_string((num + 1) / 2);
        pair += "]";

        line.replace(num_start, i - num_start, pair);
        return true;
      }

      last_was_num = false;
    }
  }

  return false;
}

int magnitude(std::string pair) {
  int result = 0;
  size_t last;

  if (pair[1] == '[') {
    size_t open_brackets = 0;
    for (size_t i = 1; i < pair.length(); i++) {
      if (pair[i] == '[') {
        open_brackets++;
      } else if (pair[i] == ']') {
        open_brackets--;

        if (open_brackets == 0) {
          result += 3 * magnitude(pair.substr(1, i));
          last = i;
          break;
        }
      }
    }
  } else {
    result += 3 * (pair[1] - '0');
    last = 1;
  }

  last += 2;
  if (pair[last] == '[') {
    size_t open_brackets = 0;
    for (size_t i = last; i < pair.length(); i++) {
      if (pair[i] == '[') {
        open_brackets++;
      } else if (pair[i] == ']') {
        open_brackets--;

        if (open_brackets == 0) {
          result += 2 * magnitude(pair.substr(last, i - last));
          break;
        }
      }
    }
  } else {
    result += 2 * (pair[last] - '0');
  }

  return result;
}

std::string sum(std::string first, std::string second) {
  std::string sum = "[";
  sum += first;
  sum += ",";
  sum += second;
  sum += "]";

  bool something_done;
  do {
    something_done = false;
    something_done = explode(sum) || split(sum);
  } while (something_done);

  return sum;
}

int main(int argc, char const* argv[]) {
  std::string input;
  std::vector<std::string> inputs;

  while (std::cin >> input) {
    inputs.push_back(input);
  }

  int max_mag = -1;
  for (size_t i = 0; i < inputs.size(); i++) {
    for (size_t j = 0; j < inputs.size(); j++) {
      if (i != j) {
        std::string result = sum(inputs[i], inputs[j]);
        int mag = magnitude(result);
        if (mag > max_mag) {
          max_mag = mag;
        }
      }
    }
  }

  std::cout << max_mag << std::endl;

  return 0;
}
