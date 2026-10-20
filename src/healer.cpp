#include "healer.hpp"

#include <iostream>

healer::healer(const std::string& name, size_t id, double hp,
               double healPower, double mana)
    : entity(name, id, hp), m_healPower(healPower), m_mana(mana) {}

bool healer::spendMana(double cost) {
  if (m_mana < cost) return false;
  m_mana -= cost;
  return true;
}

void healer::heal(entity& target) {
  if (!isAlive()) {
    std::cout << m_name << " is down and cannot heal.\n";
    return;
  }
  if (!target.isAlive()) {
    std::cout << target.getName() << " is already defeated.\n";
    return;
  }
  if (target.getHP() >= target.getMaxHP()) {
    std::cout << target.getName() << " is already at full health.\n";
    return;
  }

  const double cost = healManaCost();
  if (!spendMana(cost)) {
    std::cout << m_name << " does not have enough mana for " << healName()
              << ".\n";
    return;
  }

  applyHealing(target);
}

double healer::getMana() const { return m_mana; }
