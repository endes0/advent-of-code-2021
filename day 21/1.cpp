#include <iostream>
#include <vector>

class Dice {
 private:
  unsigned int next = 1;

 public:
  unsigned int rolls = 0;

  Dice() {}

  unsigned int get_next() {
    unsigned int result = next;

    rolls++;
    next = next % 100 + 1;

    return result;
  }
};

struct Player {
  unsigned int pos;
  unsigned int score;

  explicit Player(unsigned int _pos) {
    pos = _pos;
    score = 0;
  }
};

bool play_game(std::vector<Player> &players, Dice &dice) {
  for (size_t i = 0; i < players.size(); i++) {
    unsigned int player_rolls =
        dice.get_next() + dice.get_next() + dice.get_next();
    players[i].pos += player_rolls;
    players[i].pos = (players[i].pos - 1) % 10 + 1;
    players[i].score += players[i].pos;

    if (players[i].score >= 1000) {
      return false;
    }
  }

  return true;
}

int main(int argc, char const *argv[]) {
  unsigned int player_1_pos;
  unsigned int player_2_pos;

  std::cin >> player_1_pos;
  std::cin >> player_2_pos;

  std::vector<Player> players;
  players.push_back(Player(player_1_pos));
  players.push_back(Player(player_2_pos));

  size_t i = 0;
  Dice dice;
  while (play_game(players, dice)) {
    i++;
    std::cout << "Turn " << i << std::endl;
  }

  std::cout << (dice.rolls * ((players[0].score > players[1].score)
                    ? players[1].score
                    : players[0].score))
            << std::endl;

  return 0;
}
