#include "cleric.hpp"

#include <iostream>

cleric::cleric(const std::string& name, size_t id, double hp,
               double healPower, double mana, faction team,
               size_t maxActionPoints)
    : healer(name, id, hp, healPower, mana, team, maxActionPoints) {}

double cleric::healManaCost() const { return 20.0; }

const char* cleric::healName() const { return "Divine Light"; }

void cleric::applyHealing(entity& target) {
  const double before = target.getHP();
  target.receiveHealing(m_healPower);
  const double restored = target.getHP() - before;

  std::cout << m_name << " uses " << healName() << " on " << target.getName()
            << ", restoring " << restored << " HP (" << target.getHP()
            << " HP total).\n";
}

void cleric::print() const {
  std::cout << "[Cleric] ID: " << m_id << " | Name: " << m_name
            << " | HP: " << m_hp << "/" << m_maxHP
            << " | Heal: " << m_healPower << " | Mana: " << m_mana << "\n";
}
