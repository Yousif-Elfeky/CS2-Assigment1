#include "game_engine.hpp"

#include <algorithm>
#include <iostream>
#include <print>
#include <sstream>
#include <string>

void GameEngine::addEntity(std::unique_ptr<entity> entity) {
  if (entity) {
    m_entities.push_back(std::move(entity));
  }
}
void GameEngine::removeEntity(size_t id) {
  auto it = std::find_if(
      m_entities.begin(), m_entities.end(),
      [id](const std::unique_ptr<entity>& e) { return e->getID() == id; });
  if (it != m_entities.end()) {
    m_entities.erase(it);
  }
}
entity* GameEngine::getEntity(size_t id) {
  for (auto& e : m_entities) {
    if (e && e->getID() == id) {
      return e.get();
    }
  }
  return nullptr;
}
const entity* GameEngine::getEntity(size_t id) const {
  for (const auto& e : m_entities) {
    if (e && e->getID() == id) {
      return e.get();
    }
  }
  return nullptr;
}
std::vector<const entity*> GameEngine::getValidTargets(
    const entity* currentEntity) const {
  std::vector<const entity*> validTargets;

  if (!currentEntity || !currentEntity->isAlive()) return validTargets;

  targetType preferredTarget = currentEntity->getTarget();

  for (const auto& e : m_entities) {
    if (!e || !e->isAlive()) continue;
    if (e.get() == currentEntity) continue;  // skip self?

    // check what team we are on
    bool isSameTeam = (e->getTeam() == currentEntity->getTeam());

    // if the currentEntity is an ally, we can only target allies
    if (isSameTeam && preferredTarget == targetType::ally) {
      validTargets.push_back(e.get());
    }
    // if the currentEntity is an enemy, we can only target enemies
    else if (!isSameTeam && preferredTarget == targetType::enemy) {
      validTargets.push_back(e.get());
    }
  }
  return validTargets;
}
void GameEngine::prepareRound() {
  for (const auto& e : m_entities) {
    if (e && e->isAlive()) {
      m_turnQueue.push(e->getID());
    }
  }
}
bool GameEngine::hasPlayer() const {
  for (const auto& e : m_entities) {
    if (e && e->isAlive() && e->getTeam() == team::player) {
      return true;
    }
  }
  return false;
}
bool GameEngine::hasEnvironment() const {
  for (const auto& e : m_entities) {
    if (e && e->isAlive() && e->getTeam() == team::environment) {
      return true;
    }
  }
  return false;
}
bool GameEngine::isGameOver() const {
  return !hasPlayer() || !hasEnvironment();
}
void GameEngine::printEntities() const {
  std::println();
  std::println("  ID   {:<24}{:<16}{:<14}Status", "Name", "Team", "Health");
  std::println(
      "  ---------------------------------------------------------------");

  for (const auto& e : m_entities) {
    if (!e) continue;

    const char* teamName =
        e->getTeam() == team::player ? "Player" : "Environment";
    const char* status = e->isAlive() ? "Active" : "Defeated";

    std::println("  {:>3}   {:<24}{:<16}{:>5.1f} / {:<5.1f}  {}", e->getID(),
                 e->getName(), teamName, e->getHP(), e->getMaxHP(), status);
  }

  std::println();
}
void GameEngine::displayGameResult() const {
  bool playerAlive = hasPlayer();
  bool environmentAlive = hasEnvironment();
  if (playerAlive && !environmentAlive) {
    std::println("Players win!");
  } else if (!playerAlive && environmentAlive) {
    std::println("Environment wins!");
  } else {
    std::println("It's a draw!");
  }
}
void GameEngine::doEndOfRound() {
  std::println();
  std::println("==================== End of Round {} ====================",
               m_round);
  printEntities();
}
int GameEngine::run() {
  std::println("\n==================== Game Start ====================");
  while (!isGameOver()) {
    std::println("\n==================== Round {} ====================",
                 m_round);
    prepareRound();

    while (!m_turnQueue.empty()) {
      size_t currentID = m_turnQueue.front();
      m_turnQueue.pop();

      entity* currentEntity = getEntity(currentID);
      if (!currentEntity || !currentEntity->isAlive()) continue;

      std::println("\n--- {}'s turn ---", currentEntity->getName());

      auto validTargets = getValidTargets(currentEntity);
      if (validTargets.empty()) {
        std::println("{} has no valid targets to act upon.",
                     currentEntity->getName());
        continue;
      }
      if (currentEntity->getTeam() == team::player) {
        std::println();
        if (!playerTurn(currentEntity)) {
          std::println("{}'s turn was skipped.", currentEntity->getName());
        }
      } else {
        std::println();
        environmentTurn(currentEntity);
      }
      std::println();
    }

    if (!isGameOver()) doEndOfRound();
    ++m_round;
  }

  displayGameResult();
  return isGameOver() ? 0 : 1;  // return 0 if game over, else 1
}

// helper for reading user input with validation
bool GameEngine::readChoice(const std::string& prompt, int min, int max,
                            int& choice) const {
  std::string line;
  while (std::print("{}", prompt), std::getline(std::cin, line)) {
    std::istringstream ss(line);

    if (!(ss >> choice)) {
      std::println("Invalid input. Enter a number.");
    } else if (choice < min || choice > max) {
      std::println("Choose a number between {} and {}.", min, max);
    } else {
      return true;
    }
  }
  return false;  // EOF reached
}
entity* GameEngine::selectTarget(const std::vector<const entity*>& candidates) {
  if (candidates.empty()) return nullptr;

  std::println("\nChoose a target:");

  for (std::size_t i = 0; i < candidates.size(); ++i) {
    const entity* e = candidates[i];

    std::println("{}. {} (ID: {}, HP: {}/{})", i + 1, e->getName(), e->getID(),
                 e->getHP(), e->getMaxHP());
  }

  int choice;
  if (!readChoice("Target: ", 1, static_cast<int>(candidates.size()), choice)) {
    return nullptr;
  }

  entity* selectedTarget = getEntity(candidates[choice - 1]->getID());
  if (!selectedTarget) {
    std::println("Failed to select a target.");
    return nullptr;
  }

  return selectedTarget;
}
bool GameEngine::playerTurn(entity* currentEntity) {
  auto candidates = getValidTargets(currentEntity);

  if (candidates.empty()) {
    std::println("{} has no valid targets.", currentEntity->getName());
    return true;
  }
  entity* target = selectTarget(candidates);
  if (!target) {
    std::println("No target selected. Skipping turn.");
    return true;
  }
  if (!currentEntity->doNormalAction(target)) {
    std::println("Action failed.");
  }
  return true;
}
void GameEngine::environmentTurn(entity* currentEntity) {
  auto candidates = getValidTargets(currentEntity);

  if (candidates.empty()) {
    std::println("{} has no valid targets.", currentEntity->getName());
    return;
  }
  // healer logic: heal the ally with the lowest HP
  if (currentEntity->getTarget() == targetType::ally) {
    const entity* lowestHPAlly = nullptr;
    auto lowestHPAllyIt =
        std::min_element(candidates.begin(), candidates.end(),
                         [](const entity* a, const entity* b) {
                           return a->getHP() < b->getHP();
                         });
    if (lowestHPAllyIt != candidates.end()) {
      lowestHPAlly = *lowestHPAllyIt;
    }
    if (lowestHPAlly) {
      currentEntity->doNormalAction(getEntity(lowestHPAlly->getID()));
    }
  } else if (currentEntity->getTarget() == targetType::enemy) {
    // damager logic: attack the enemy with the lowest HP
    const entity* lowestHPEnemy = nullptr;
    auto lowestHPEnemyIt =
        std::min_element(candidates.begin(), candidates.end(),
                         [](const entity* a, const entity* b) {
                           return a->getHP() < b->getHP();
                         });
    if (lowestHPEnemyIt != candidates.end()) {
      lowestHPEnemy = *lowestHPEnemyIt;
    }
    if (lowestHPEnemy) {
      currentEntity->doNormalAction(getEntity(lowestHPEnemy->getID()));
    }
  }
}