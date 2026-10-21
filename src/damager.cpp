#include "damager.hpp"

#include <iostream>

damager::damager(const std::string& name, double hp, team team,
                 int attackDamage, int specialDamage)
    : entity(name, hp, team),
      m_attackDamage(attackDamage),
      m_specialDamage(specialDamage) {
  m_target = targetType::enemy;
}

damager::~damager() {}

void damager::doNormalAttack(entity* target) {
  std::cout << m_name << " attacks " << target->getName() << " for "
            << m_attackDamage << " damage\n";
  target->takeDamage(m_attackDamage);
  std::cout << target->getName() << "'s health is now " << target->getHP()
            << "\n";

  if (!target->isAlive()) {
    std::cout << target->getName() << " has been slain!\n";
  }
}
bool damager::doNormalAction(entity* target) {
  if (!isAlive() || !target || !target->isAlive()) {
    return false;
  }

  if (target->getTeam() == getTeam()) {
    std::cout << "Cannot attack an ally!\n";
    return false;
  }
  doNormalAttack(target);
  return true;
}