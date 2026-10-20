#pragma once

#include <memory>
#include <vector>

#include "entity.hpp"

class controller;

enum class gameState { ongoing, playerWon, environmentWon };

// main simulator of the world. owns entities and advances the world one turn at
// a time.
class simulation {
 public:
  // automatic memory management of entities, so we don't have to worry about
  // deleting them.
  void addEntity(std::unique_ptr<entity>);

  // get the possible targets for a given entity and target side
  std::vector<entity*> targetsFor(const entity&, targetSide) const;
  // find the target with the lowest health ratio (current/max) for a given
  // entity and target side
  entity* findTarget(const entity&, targetSide) const;
  // run a round of the simulation, where each entity gets to act once.
  void runRound(controller&, controller&);
  void printEntities() const;

  bool hasLiving(faction) const;
  gameState getGameState() const;
  size_t getRound() const;

 private:
  void runPhase(faction, controller&);
  void removeDefeated();
  void updateGameState();

  std::vector<std::unique_ptr<entity>> m_entities;
  size_t m_round = 0;
  gameState m_state = gameState::ongoing;
};
