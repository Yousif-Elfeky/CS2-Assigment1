#include "humanController.hpp"

#include <iostream>
#include <limits>
#include <vector>

#include "entity.hpp"
#include "simulation.hpp"

bool humanController::takeAction(entity& actor, simulation& sim) {
  if (actor.getActionPoints() == 0) return false;

  const std::vector<entity*> targets =
      sim.targetsFor(actor, actor.normalTargetSide());
  if (targets.empty()) {
    std::cout << actor.getName() << " has no valid targets.\n";
    return false;
  }

  std::cout << "\n"
            << actor.getName() << " | AP: " << actor.getActionPoints() << "/"
            << actor.getMaxActionPoints() << "\n";

  // list the targets
  for (size_t i = 0; i < targets.size(); ++i) {
    std::cout << i + 1 << ") " << targets[i]->getName() << " ("
              << targets[i]->getHP() << "/" << targets[i]->getMaxHP()
              << " HP)\n";
  }
  std::cout << "0) end turn\n";

  int choice = 0;

  while (true) {
    std::cout << "choice: ";
    if (std::cin >> choice && choice >= 0 &&
        choice <= static_cast<int>(targets.size()))
      break;

    // clear cin and ignore the rest of the line to avoid infinite loop on
    // invalid input
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "invalid choice.\n";
  }

  if (choice == 0) return false;

  entity& target = *targets[static_cast<size_t>(choice - 1)];
  if (actor.doNormalAction(target)) {
    actor.spendActionPoints(entity::normalActionCost);
  }

  return true;
}
