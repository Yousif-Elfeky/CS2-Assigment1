#include "cleric.hpp"

#include <print>

cleric::cleric(const std::string& name, double hp, team team, double healPower,
               double mana)
    : healer(name, hp, team, healPower, mana) {}

double cleric::healManaCost() const { return 20.0; }

const char* cleric::healName() const { return "Divine Light"; }

void cleric::applyHealing(entity* target) {
  const double before = target->getHP();
  target->receiveHealing(m_healPower);
  const double restored = target->getHP() - before;

  std::println("{} uses {} on {}, restoring {} HP ({} HP total).", m_name,
               healName(), target->getName(), restored, target->getHP());
}

void cleric::print() const {
  std::println("[Cleric] ID: {} | Name: {} | HP: {}/{} | Heal: {} | Mana: {}",
               m_id, m_name, m_hp, m_maxHP, m_healPower, m_mana);
}

bool cleric::doSpecialAction(entity* target) {
  if (!isAlive() || !target || !target->isAlive() ||
      target->getTeam() != getTeam()) {
    return false;
  }
  if (!spendActionPoints(getMaxActionPoints())) {
    std::println("{} does not have enough action points.", m_name);
    return false;
  }

  const double targetBefore = target->getHP();
  target->receiveHealing(target->getMaxHP());
  std::println("{} uses Divine Restoration on {} (+{} HP, full recovery).",
               m_name, target->getName(), target->getHP() - targetBefore);
  return true;
}
