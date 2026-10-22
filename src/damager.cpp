#include "damager.hpp"

#include <print>

damager::damager(const std::string& name, double hp, team team,
                 int attackDamage, int specialDamage)
    : entity(name, hp, team),
      m_attackDamage(attackDamage),
      m_specialDamage(specialDamage) {
  m_target = targetType::enemy;
}

damager::~damager() {}

void damager::doNormalAttack(entity* target) {
  const bool wasAlive = target->isAlive();
  std::println("{} attacks {} for {} damage", m_name, target->getName(),
               m_attackDamage);
  target->takeDamage(m_attackDamage);
  restoreActionPoints();
  std::println("{}'s health is now {}", target->getName(), target->getHP());

  if (wasAlive && !target->isAlive()) {
    restoreActionPoints();
    std::println("{} has been slain!", target->getName());
  }
}
bool damager::doNormalAction(entity* target) {
  if (!isAlive() || !target || !target->isAlive()) {
    return false;
  }

  if (target->getTeam() == getTeam()) {
    std::println("Cannot attack an ally!");
    return false;
  }
  doNormalAttack(target);
  return true;
}

bool damager::doSpecialAction(entity* target) {
  if (!isAlive() || !target || !target->isAlive() ||
      target->getTeam() == getTeam()) {
    return false;
  }
  if (!spendActionPoints(getMaxActionPoints())) {
    std::println("{} does not have enough action points.", m_name);
    return false;
  }

  doSpecialAttack(target);
  return true;
}