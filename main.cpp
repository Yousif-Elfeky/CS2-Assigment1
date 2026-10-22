#include <iostream>
#include <memory>
#include <print>
#include <string>

#include "game_engine.hpp"
#include "units.hpp"

void printGameIntroduction() {
  std::println("============================================================");
  std::println("                 TURN-BASED GAME SIMULATION");
  std::println("============================================================");
  std::println("Two teams take turns until one team has no living units.");
  std::println("Player units ask you to choose a valid target each turn.");
  std::println("Environment units choose their targets automatically.");
  std::println();
  std::println("Rules:");
  std::println("- Normal actions attack an enemy or heal an ally.");
  std::println("- Healers spend mana when they heal and regenerate mana every");
  std::println("  third round.");
  std::println(
      "- Every unit starts with 1 action point and can store up to 3.");
  std::println("- Units gain action points when attacking or taking damage.");
  std::println("- A killing blow grants an additional action point.");
  std::println("- A special action costs 3 action points.");
  std::println();
  std::println("Unit guide:");
  std::println("- Warrior: attacks enemies and can intimidate them, causing");
  std::println("  the target to skip its next turn.");
  std::println(
      "- Druid: heals an ally and also restores some of its own health.");
  std::println("  Its special action provides stronger healing.");
  std::println("- Cleric: provides strong direct healing. Its special action");
  std::println("  can fully restore an ally's health.");
  std::println("- Paladin: is durable, heals allies, and its special action");
  std::println("  provides additional self-healing.");
  std::println();
}

int readPresetChoice() {
  std::println("Choose a starting preset:");
  std::println("1. Balanced - reliable damage and healing");
  std::println("2. Offensive - several strong attackers");
  std::println("3. Defensive - durable units and multiple healers");

  std::string line;
  int choice = 0;
  while (std::print("Preset: "), std::getline(std::cin, line)) {
    try {
      choice = std::stoi(line);
    } catch (const std::exception&) {
      choice = 0;
    }
    if (choice >= 1 && choice <= 3) return choice;
    std::println("Choose 1, 2, or 3.");
  }
  return 1;
}

void addBalancedPreset(GameEngine& game) {
  game.addEntity(std::make_unique<warrior>("Player Warrior", 100.0,
                                           team::player, 20, 30, 1));
  game.addEntity(
      std::make_unique<cleric>("Player Cleric", 90.0, team::player, 25, 100));
  game.addEntity(std::make_unique<warrior>("Enemy Warrior", 200.0,
                                           team::environment, 30, 25, 1));
  game.addEntity(std::make_unique<druid>("Enemy Druid", 100.0,
                                         team::environment, 20, 100));
}

void addOffensivePreset(GameEngine& game) {
  game.addEntity(std::make_unique<warrior>("Player Warrior", 110.0,
                                           team::player, 25, 35, 1));
  game.addEntity(std::make_unique<warrior>("Player Warrior 2", 100.0,
                                           team::player, 30, 40, 1));
  game.addEntity(std::make_unique<warrior>("Enemy Warrior", 150.0,
                                           team::environment, 25, 30, 1));
  game.addEntity(
      std::make_unique<druid>("Enemy Druid", 80.0, team::environment, 18, 90));
}

void addDefensivePreset(GameEngine& game) {
  game.addEntity(
      std::make_unique<paladin>("Player Paladin", 140.0, team::player, 18, 90));
  game.addEntity(
      std::make_unique<druid>("Player Druid", 90.0, team::player, 18, 100));
  game.addEntity(std::make_unique<warrior>("Enemy Warrior", 220.0,
                                           team::environment, 28, 35, 1));
  game.addEntity(std::make_unique<cleric>("Enemy Cleric", 95.0,
                                          team::environment, 22, 100));
}

int main() {
  printGameIntroduction();

  GameEngine game;
  switch (readPresetChoice()) {
    case 2:
      addOffensivePreset(game);
      break;
    case 3:
      addDefensivePreset(game);
      break;
    default:
      addBalancedPreset(game);
      break;
  }

  return game.run();
}