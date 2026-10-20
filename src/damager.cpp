#include "damager.hpp"

#include <iostream>

damager::damager(const std::string& name, size_t id, double hp,
                 int attackDamage, int specialDamage)
    : entity(name, id, hp),
      m_attackDamage(attackDamage),
      m_specialDamage(specialDamage) {}

damager::~damager() {}

void damager::doNormalAttack(entity& target) {
  std::cout << m_name << " attacks " << target.getName() << " for "
            << m_attackDamage << " damage\n";
  target.takeDamage(m_attackDamage);
  std::cout << target.getName() << "'s health is now " << target.getHP()
            << "\n";

  if (!target.isAlive()) {
    std::cout << target.getName() << " has been slain!\n";
  }
}
