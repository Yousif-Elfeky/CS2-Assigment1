#include "paladin.hpp"

#include <iostream>

paladin::paladin(const std::string& name, size_t id, double hp,
                 double healPower, double mana, faction team,
                 size_t maxActionPoints)
    : healer(name, id, hp, healPower, mana, team, maxActionPoints) {}

double paladin::healManaCost() const { return 25.0; }

const char* paladin::healName() const { return "Lay on Hands"; }

void paladin::applyHealing(entity& target) {
  const double selfHeal = m_healPower * 0.25;
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

void paladin::print() const {
  std::cout << "[Paladin] ID: " << m_id << " | Name: " << m_name
            << " | HP: " << m_hp << "/" << m_maxHP
            << " | Heal: " << m_healPower << " | Mana: " << m_mana << "\n";
}
