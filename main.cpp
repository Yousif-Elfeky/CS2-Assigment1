#include <memory>

#include "druid.hpp"
#include "game_engine.hpp"
#include "warrior.hpp"

int main() {
  GameEngine game;

  // Player-controlled
  game.addEntity(std::make_unique<warrior>("Player Warrior", 100.0,
                                           team::player, 20, 30, 1));
  game.addEntity(std::make_unique<warrior>("Player Warrior 2", 100.0,
                                           team::player, 30, 30, 1));

  // AI-controlled
  game.addEntity(std::make_unique<druid>("Enemy Druid", 100.0,
                                         team::environment, 20, 100));
  game.addEntity(std::make_unique<warrior>("Enemy Warrior", 200.0,
                                           team::environment, 30, 25, 1));

  if (!game.run()) {
    return 1;
  }

  return 0;
}