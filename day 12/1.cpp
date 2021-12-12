#include <array>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class Cavern {
 public:
  std::string name;
  bool is_big;
  bool has_been_visited = false;
  std::vector<Cavern *> linked;

  Cavern(std::string name_);
  Cavern();
  ~Cavern();
};

Cavern::Cavern(std::string name_) {
  if (isupper(name_[0])) {
    is_big = true;
  } else {
    is_big = false;
  }

  name = name_;
}

Cavern::Cavern() {}

Cavern::~Cavern() {}

long visit_cavern(std::string path, Cavern cavern,
                  std::set<std::string> visited, bool can_visit_twice) {
  visited.insert(cavern.name);
  if (cavern.name == "end") {
    std::cout << path << ",end" << std::endl;
    return 1;
  }

  long result = 0;
  for (auto cav : cavern.linked) {
    if (cav->name != "start" && (visited.find(cav->name) == visited.end() ||
                                 cav->is_big || cav->name == "end")) {
      result += visit_cavern(path + "," + cavern.name, *cav, visited,
                             can_visit_twice);
    } else if (visited.find(cav->name) != visited.end() && can_visit_twice &&
               cav->name != "start" && cav->name != "end") {
      result += visit_cavern(path + "," + cavern.name, *cav, visited, false);
    }
  }

  return result;
}

int main(int argc, char const *argv[]) {
  std::map<std::string, Cavern> caverns;
  std::string line;
  Cavern *start;

  while (std::cin >> line) {
    std::stringstream line_stream(line);
    std::string token1;
    std::string token2;

    std::getline(line_stream, token1, '-');
    std::getline(line_stream, token2, '-');

    caverns.try_emplace(token1, Cavern(token1));
    caverns.try_emplace(token2, Cavern(token2));

    caverns[token1].linked.push_back(&caverns[token2]);
    caverns[token2].linked.push_back(&caverns[token1]);

    if (token1 == "start") {
      start = &caverns[token1];
    }
  }

  std::set<std::string> visited;
  std::cout << visit_cavern("", *start, visited, true) << std::endl;

  return 0;
}
