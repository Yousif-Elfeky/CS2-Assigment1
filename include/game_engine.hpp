#pragma once

#include <memory>
#include <vector>

#include "entity.hpp"
#include "queue.hpp"

class GameEngine {
 private:
  // we own the entities, so we use unique_ptr to manage their lifetime
  // we could also use shared_ptr + weak_ptr, but we have a unique id for each
  // entity, so we can use unique_ptr for simplicity
  std::vector<std::unique_ptr<entity>> m_entities;
  // queue of actions to be performed in the game engine
  // the queue does not own the entities, it just holds pointers to them

  queue<size_t> m_turnQueue;
  // current round
  int m_round = 1;

 private:
  bool readChoice(const std::string& prompt, int min, int max,
                  int& choice) const;

  entity* selectTarget(const std::vector<const entity*>& candidates);

  bool playerTurn(entity* currentEntity);
  void environmentTurn(entity* currentEntity);

  bool hasPlayer() const;
  bool hasEnvironment() const;
  void regenerateHealers();
  void prepareRound();
  void doEndOfRound();

 public:
  int run();

  void addEntity(std::unique_ptr<entity> entity);
  void removeEntity(size_t id);

  entity* getEntity(size_t id);
  const entity* getEntity(size_t id) const;
  std::vector<const entity*> getValidTargets(const entity* currentEntity) const;

  bool isGameOver() const;
  void displayGameResult() const;

  void printEntities() const;
};