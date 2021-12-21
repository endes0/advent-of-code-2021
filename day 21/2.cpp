#include <iostream>
#include <queue>
#include <vector>

struct Player {
  unsigned int pos;
  unsigned int score;

  explicit Player(unsigned int _pos) {
    pos = _pos;
    score = 0;
  }
};

struct Game {
  std::vector<Player> players;
  unsigned int dice_comb;
  size_t round = 0;
  long total_universes = 1;
};

bool play_game(Game &game) {
  unsigned int player_rolls = game.dice_comb;

  size_t comb;
  switch (player_rolls) {
    case 3:
      comb = 1;
      break;
    case 4:
      comb = 3;
      break;
    case 5:
      comb = 6;
      break;
    case 6:
      comb = 7;
      break;
    case 7:
      comb = 6;
      break;
    case 8:
      comb = 3;
      break;
    case 9:
      comb = 1;
      break;
    default:
      std::cout << "Big ups" << std::endl;
      break;
  }

  game.total_universes = game.total_universes * comb;

  /*  for (size_t j = 3; j < 10; j++) {
      if (j != player_rolls) {
        Game new_game = game;
        new_game.dice_comb = j;

        universes.push(new_game);
      }
    }*/

  game.players[game.round].pos += player_rolls;
  game.players[game.round].pos = (game.players[game.round].pos - 1) % 10 + 1;
  game.players[game.round].score += game.players[game.round].pos;

  if (game.players[game.round].score >= 21) {
    return false;
  }

  game.round = (game.round + 1) % 2;

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

  std::vector<Game> universes;
  universes.push_back(Game{players, 3});
  universes.push_back(Game{players, 4});
  universes.push_back(Game{players, 5});
  universes.push_back(Game{players, 6});
  universes.push_back(Game{players, 7});
  universes.push_back(Game{players, 8});
  universes.push_back(Game{players, 9});

  long player_1_wins = 0;
  long player_2_wins = 0;

  while (!universes.empty()) {
    std::vector<Game> new_universes;

    for (auto game : universes) {
      if (!play_game(game)) {
        if (game.players[0].score > game.players[1].score) {
          player_1_wins += game.total_universes;
        } else {
          player_2_wins += game.total_universes;
        }
      } else {
        for (size_t j = 3; j < 10; j++) {
          Game new_game = game;
          new_game.dice_comb = j;

          new_universes.push_back(new_game);
        }
      }
    }

    universes = new_universes;
  }

  std::cout << player_1_wins << " " << player_2_wins << std::endl;

  return 0;
}
