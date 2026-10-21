#include "game_engine.hpp"

#include <algorithm>
#include <iostream>
#include <limits>
#include <random>
#include <sstream>
#include <string>

std::mt19937 GameEngine::rng(std::random_device{}());

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
  std::cout << "\n--- Entities ---\n";

  for (const auto& e : m_entities) {
    if (!e) continue;

    e->print();
    std::cout << '\n';
  }
}
void GameEngine::displayGameResult() const {
  bool playerAlive = hasPlayer();
  bool environmentAlive = hasEnvironment();
  if (playerAlive && !environmentAlive) {
    std::cout << "Players win!\n";
  } else if (!playerAlive && environmentAlive) {
    std::cout << "Environment wins!\n";
  } else {
    std::cout << "It's a draw!\n";
  }
}
void GameEngine::doEndOfRound() {
  std::cout << "\n--- End of Round " << m_round << " ---\n";
  printEntities();
}
void GameEngine::run() {
  std::cout << "Starting the game...\n";
  while (!isGameOver()) {
    std::cout << "\n--- Round " << m_round << " ---\n";
    prepareRound();

    while (!m_turnQueue.empty()) {
      size_t currentID = m_turnQueue.front();
      m_turnQueue.pop();

      entity* currentEntity = getEntity(currentID);
      if (!currentEntity || !currentEntity->isAlive()) continue;

      std::cout << "\nIt's " << currentEntity->getName() << "'s turn.\n";

      auto validTargets = getValidTargets(currentEntity);
      if (validTargets.empty()) {
        std::cout << currentEntity->getName()
                  << " has no valid targets to act upon.\n";
        continue;
      }
      if (currentEntity->getTeam() == team::player) {
        if (!playerTurn(currentEntity)) {
          std::cout << currentEntity->getName() << "'s turn was skipped.\n";
        }
      } else {
        environmentTurn(currentEntity);
      }
    }

    if (!isGameOver()) doEndOfRound();
    ++m_round;
  }

  displayGameResult();
}

// helper for reading user input with validation
bool GameEngine::readChoice(const std::string& prompt, int min, int max,
                            int& choice) const {
  std::string line;
  while (std::cout << prompt && std::getline(std::cin, line)) {
    std::istringstream ss(line);

    if (!(ss >> choice)) {
      std::cout << "Invalid input. Enter a number.\n";
    } else if (choice < min || choice > max) {
      std::cout << "Choose a number between " << min << " and " << max << ".\n";
    } else {
      return true;
    }
  }
  return false;  // EOF reached
}
entity* GameEngine::selectTarget(const std::vector<const entity*>& candidates) {
  if (candidates.empty()) return nullptr;

  std::cout << "\nChoose a target:\n";

  for (std::size_t i = 0; i < candidates.size(); ++i) {
    const entity* e = candidates[i];

    std::cout << i + 1 << ". " << e->getName() << " (ID: " << e->getID()
              << ", HP: " << e->getHP() << "/" << e->getMaxHP() << ")\n";
  }

  int choice;
  if (!readChoice("Target: ", 1, static_cast<int>(candidates.size()), choice)) {
    return nullptr;
  }

  entity* selectedTarget = getEntity(candidates[choice - 1]->getID());
  if (!selectedTarget) {
    std::cout << "Failed to select a target.\n";
    return nullptr;
  }

  return selectedTarget;
}
bool GameEngine::playerTurn(entity* currentEntity) {
  auto candidates = getValidTargets(currentEntity);

  if (candidates.empty()) {
    std::cout << currentEntity->getName() << " has no valid targets.\n";
    return true;
  }
  entity* target = selectTarget(candidates);
  if (!target) {
    std::cout << "No target selected. Skipping turn.\n";
    return true;
  }
  if (!currentEntity->doNormalAction(target)) {
    std::cout << "Action failed.\n";
  }
  return true;
}
void GameEngine::environmentTurn(entity* currentEntity) {
  auto candidates = getValidTargets(currentEntity);

  if (candidates.empty()) {
    std::cout << currentEntity->getName() << " has no valid targets.\n";
    return;
  }
  // healer logic: heal the ally with the lowest HP
  if (currentEntity->getTarget() == targetType::ally) {
    const entity* lowestHPAlly = nullptr;
    for (const auto& ally : candidates) {
      if (!lowestHPAlly || ally->getHP() < lowestHPAlly->getHP()) {
        lowestHPAlly = ally;
      }
    }
    if (lowestHPAlly) {
      currentEntity->doNormalAction(getEntity(lowestHPAlly->getID()));
    }
  } else if (currentEntity->getTarget() == targetType::enemy) {
    // damager logic: attack the enemy with the lowest HP
    const entity* lowestHPEnemy = nullptr;
    for (const auto& enemy : candidates) {
      if (!lowestHPEnemy || enemy->getHP() < lowestHPEnemy->getHP()) {
        lowestHPEnemy = enemy;
      }
    }
    if (lowestHPEnemy) {
      currentEntity->doNormalAction(getEntity(lowestHPEnemy->getID()));
    }
  }
}