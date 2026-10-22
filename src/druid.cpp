#include "druid.hpp"

#include <print>

druid::druid(const std::string& name, double hp, team team, double healPower,
             double mana)
    : healer(name, hp, team, healPower, mana) {}

double druid::healManaCost() const { return 15.0; }

const char* druid::healName() const { return "Regrowth"; }

void druid::applyHealing(entity* target) {
  const double selfHeal = m_healPower * 0.5;
  const double targetBefore = target->getHP();
  const double selfBefore = getHP();

  target->receiveHealing(m_healPower);
  receiveHealing(selfHeal);

  const double targetHealed = target->getHP() - targetBefore;
  const double selfHealed = getHP() - selfBefore;

  std::println("{} uses {} on {} (+{} HP) and gains {} HP.", m_name,
               healName(), target->getName(), targetHealed, selfHealed);
}

void druid::print() const {
  std::println("[Druid] ID: {} | Name: {} | HP: {}/{} | Heal: {} | Mana: {}",
               m_id, m_name, m_hp, m_maxHP, m_healPower, m_mana);
}

bool druid::doSpecialAction(entity* target) {
  if (!isAlive() || !target || !target->isAlive() ||
      target->getTeam() != getTeam()) {
    return false;
  }
  if (!spendActionPoints(getMaxActionPoints())) {
    std::println("{} does not have enough action points.", m_name);
    return false;
  }

  const double targetBefore = target->getHP();
  const double selfBefore = getHP();
  target->receiveHealing(m_healPower * 2.0);
  receiveHealing(m_healPower);
  std::println("{} uses Nature's Renewal on {} (+{} HP, +{} self HP).", m_name,
               target->getName(), target->getHP() - targetBefore,
               getHP() - selfBefore);
  return true;
}
