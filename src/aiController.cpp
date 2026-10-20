#include "aiController.hpp"

#include <iostream>

#include "entity.hpp"
#include "simulation.hpp"

bool aiController::takeAction(entity& actor, simulation& sim) {
  if (actor.getActionPoints() == 0) return false;

  entity* target = sim.findTarget(actor, actor.normalTargetSide());
  if (target == nullptr) {
    std::cout << actor.getName() << " has no valid targets.\n";
    return false;
  }

  if (!actor.doNormalAction(*target)) return false;
  actor.spendActionPoints(entity::normalActionCost);
  return true;
}
