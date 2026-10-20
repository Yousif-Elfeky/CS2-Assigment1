#include "healer.hpp"

#include <iostream>

healer::healer(const std::string& name, size_t id, double hp,
               double healPower, double mana, faction team,
               size_t maxActionPoints)
    : entity(name, id, hp, team, maxActionPoints),
      m_healPower(healPower),
      m_mana(mana) {}

bool healer::doNormalAction(entity& target) { return heal(target); }

targetSide healer::normalTargetSide() const { return targetSide::ally; }

bool healer::spendMana(double cost) {
  if (m_mana < cost) return false;
  m_mana -= cost;
  return true;
}

bool healer::heal(entity& target) {
  if (!isAlive()) {
    std::cout << m_name << " is down and cannot heal.\n";
    return false;
  }
  if (!target.isAlive()) {
    std::cout << target.getName() << " is already defeated.\n";
    return false;
  }
  if (!isAlly(target)) {
    std::cout << target.getName() << " is not an ally.\n";
    return false;
  }
  if (target.getHP() >= target.getMaxHP()) {
    std::cout << target.getName() << " is already at full health.\n";
    return false;
  }

  const double cost = healManaCost();
  if (!spendMana(cost)) {
    std::cout << m_name << " does not have enough mana for " << healName()
              << ".\n";
    return false;
  }

  applyHealing(target);
  return true;
}

double healer::getMana() const { return m_mana; }
