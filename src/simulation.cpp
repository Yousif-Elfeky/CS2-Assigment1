#include "simulation.hpp"

#include <iostream>
#include <utility>

#include "controller.hpp"

void simulation::addEntity(std::unique_ptr<entity> entityPtr) {
  if (entityPtr) m_entities.push_back(std::move(entityPtr));
}

void simulation::printEntities() const {
  for (const auto& entityPtr : m_entities) {
    if (entityPtr->getFaction() == faction::player) {
      std::cout << "[player] ";
    } else {
      std::cout << "[environment] ";
    }
    entityPtr->print();
  }
}

// get the possible targets for a given entity and target side
// who is who is doing the action (horrable name, but I can't think of a better
// one)
std::vector<entity*> simulation::targetsFor(const entity& who,
                                            targetSide side) const {
  std::vector<entity*> targets;

  for (const auto& entityPtr : m_entities) {
    if (!entityPtr->isAlive()) continue;
    if (side == targetSide::ally && !who.isAlly(*entityPtr)) continue;
    if (side == targetSide::enemy && !who.isEnemy(*entityPtr)) continue;
    targets.push_back(entityPtr.get());
  }

  return targets;
}

entity* simulation::findTarget(const entity& who, targetSide side) const {
  entity* bestTarget = nullptr;
  double lowestRatio = 2.0;

  for (entity* target : targetsFor(who, side)) {
    // best target is the one with the lowest health ratio (current/max)
    const double ratio = target->getHP() / target->getMaxHP();
    if (bestTarget == nullptr || ratio < lowestRatio) {
      bestTarget = target;
      lowestRatio = ratio;
    }
  }

  return bestTarget;
}

void simulation::runRound(controller& playerController,
                          controller& environmentController) {
  if (m_state != gameState::ongoing) {
    std::cout << "the game is already over.\n";
    return;
  }

  ++m_round;
  std::cout << "--- Round " << m_round << " ---\n";

  runPhase(faction::player, playerController);
  removeDefeated();
  updateGameState();

  if (m_state == gameState::ongoing) {
    runPhase(faction::environment, environmentController);
    removeDefeated();
    updateGameState();
  }

  if (m_state == gameState::playerWon) {
    std::cout << "player wins.\n";
  } else if (m_state == gameState::environmentWon) {
    std::cout << "environment wins.\n";
  }
}

void simulation::runPhase(faction team, controller& unitController) {
  for (auto& entityPtr : m_entities) {
    if (m_state != gameState::ongoing) return;
    if (entityPtr->getFaction() != team || !entityPtr->isAlive()) continue;

    // restore action points for the entity at the start of its turn
    entityPtr->restoreActionPoints();
    while (entityPtr->isAlive() && entityPtr->getActionPoints() > 0 &&
           m_state == gameState::ongoing) {
      // ask the controller to take an action for this entity. if it returns
      // false or we run out of action points, the entity is done for this
      // round.
      if (!unitController.takeAction(*entityPtr, *this)) break;
      updateGameState();
    }
  }
}

void simulation::removeDefeated() {
  for (auto it = m_entities.begin(); it != m_entities.end();) {
    if (!(*it)->isAlive()) {
      it = m_entities.erase(
          it);  // erase returns the next iterator after the erased one
    } else {
      ++it;
    }
  }
}

bool simulation::hasLiving(faction team) const {
  for (const auto& entityPtr : m_entities) {
    if (entityPtr->isAlive() && entityPtr->getFaction() == team) return true;
  }
  return false;
}

void simulation::updateGameState() {
  bool playerAlive = hasLiving(faction::player);
  bool environmentAlive = hasLiving(faction::environment);

  if (!playerAlive && !environmentAlive) {
    m_state = gameState::ongoing;
  } else if (!playerAlive) {
    m_state = gameState::environmentWon;
  } else if (!environmentAlive) {
    m_state = gameState::playerWon;
  }
}

gameState simulation::getGameState() const { return m_state; }

size_t simulation::getRound() const { return m_round; }
