#include "healer.hpp"

#include <print>

healer::healer(const std::string& name, double hp, team team, double healPower,
               double mana)
    : entity(name, hp, team), m_healPower(healPower), m_mana(mana) {
  m_target = targetType::ally;
}

bool healer::spendMana(double cost) {
  if (m_mana < cost) return false;
  m_mana -= cost;
  return true;
}

void healer::heal(entity* target) {
  if (!isAlive()) {
    std::println("{} is down and cannot heal.", m_name);
    return;
  }
  if (!target || !target->isAlive()) {
    std::println("{} is already defeated.", target->getName());
    return;
  }
  if (target->getHP() >= target->getMaxHP()) {
    std::println("{} is already at full health.", target->getName());
    return;
  }

  const double cost = healManaCost();
  if (!spendMana(cost)) {
    std::println("{} does not have enough mana for {}.", m_name, healName());
    return;
  }

  applyHealing(target);
}

double healer::getMana() const { return m_mana; }

bool healer::doNormalAction(entity* target) {
  if (!isAlive() || !target || !target->isAlive()) {
    return false;
  }

  if (target->getTeam() != getTeam()) {
    std::println("Cannot heal an enemy!");
    return false;
  }

  heal(target);
  return true;
}