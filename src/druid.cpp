#include "druid.hpp"

#include <iostream>

druid::druid(const std::string& name, size_t id, double hp,
             double healPower, double mana)
    : healer(name, id, hp, healPower, mana) {}

double druid::healManaCost() const { return 15.0; }

const char* druid::healName() const { return "Regrowth"; }

void druid::applyHealing(entity& target) {
  const double selfHeal = m_healPower * 0.5;
  const double targetBefore = target.getHP();
  const double selfBefore = getHP();

  target.receiveHealing(m_healPower);
  receiveHealing(selfHeal);

  const double targetHealed = target.getHP() - targetBefore;
  const double selfHealed = getHP() - selfBefore;

  std::cout << m_name << " uses " << healName() << " on " << target.getName()
            << " (+" << targetHealed << " HP) and gains " << selfHealed
            << " HP.\n";
}

void druid::print() const {
  std::cout << "[Druid] ID: " << m_id << " | Name: " << m_name
            << " | HP: " << m_hp << "/" << m_maxHP
            << " | Heal: " << m_healPower << " | Mana: " << m_mana << "\n";
}
