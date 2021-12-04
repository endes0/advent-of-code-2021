
#include <array>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

class Board {
 private:
  std::vector<std::set<unsigned int>> board_rows;
  std::vector<std::set<unsigned int>> board_columns;

  unsigned int total_sum;
  bool checked = false;

  bool search_remove(std::set<unsigned int>* set, unsigned int num);

 public:
  Board(std::array<std::array<unsigned int, 5>, 5> board);
  ~Board();

  void bingo(unsigned int number);
  bool has_win();
  bool has_alreay_checked();
  unsigned int get_total();

  void print();
};

bool Board::search_remove(std::set<unsigned int>* set, unsigned int num) {
  auto it = set->find(num);
  if (it != set->end()) {
    set->erase(it);
    return true;
  }
  return false;
}

Board::Board(std::array<std::array<unsigned int, 5>, 5> board) {
  total_sum = 0;

  for (size_t i = 0; i < 5; i++) {
    std::set<unsigned int> blank;
    board_columns.push_back(blank);
  }

  for (auto row : board) {
    std::set<unsigned int> result_row;
    size_t i = 0;
    for (auto col : row) {
      result_row.insert(col);
      board_columns[i].insert(col);
      total_sum += col;
      i++;
    }
    board_rows.push_back(result_row);
  }
}

Board::~Board() {}

void Board::bingo(unsigned int number) {
  bool found = false;
  for (size_t i = 0; i < board_rows.size(); i++) {
    auto it = board_rows[i].find(number);
    if (it != board_rows[i].end()) {
      board_rows[i].erase(it);

      // if (search_remove(&board_rows[i], number)) {
      found = true;
    }
  }
  for (size_t i = 0; i < board_columns.size(); i++) {
    auto it = board_columns[i].find(number);
    if (it != board_columns[i].end()) {
      board_columns[i].erase(it);
      // if (search_remove(&board_columns[i], number)) {
      found = true;
    }
  }

  if (found) {
    total_sum -= number;
  }
}

bool Board::has_win() {
  for (auto row : board_rows) {
    if (row.empty()) {
      checked = true;
      return true;
    }
  }

  for (auto col : board_columns) {
    if (col.empty()) {
      checked = true;
      return true;
    }
  }

  return false;
}

unsigned int Board::get_total() { return total_sum; }
bool Board::has_alreay_checked() { return checked; }

void Board::print() {
  for (auto row : board_rows) {
    for (auto col : row) {
      std::cout << col << ' ';
    }
    std::cout << std::endl;
  }
}

int main(int argc, char const* argv[]) {
  std::vector<int> nums;
  std::vector<Board> boards;
  std::string first_line;

  std::getline(std::cin, first_line);
  std::stringstream first_line_stream(first_line);
  std::string token;

  while (getline(first_line_stream, token, ',')) {
    nums.push_back(std::stoi(token));
  }

  while (std::cin) {
    std::array<std::array<unsigned int, 5>, 5> board;
    for (size_t i = 0; i < 5; i++) {
      for (size_t j = 0; j < 5; j++) {
        std::cin >> board[i][j];
      }
    }

    Board new_board(board);
    boards.push_back(new_board);
  }

  for (auto num : nums) {
    std::cout << num << std::endl;

    for (size_t i = 0; i < boards.size(); i++) {
      if (boards[i].has_alreay_checked()) {
        continue;
      }
      
      boards[i].bingo(num);
      if (boards[i].has_win()) {
        std::cout << " = " << i << " = " << std::endl;
        std::cout << boards[i].get_total() << std::endl;
        std::cout << num << std::endl;
        std::cout << boards[i].get_total() * num << std::endl;
        std::cout << " ==" << std::endl;
      }
    }
  }

  return 0;
}
