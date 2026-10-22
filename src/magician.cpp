#include "magician.hpp"

#include <cstdlib>
#include <iostream>

magician::magician(const std::string& name, double hp, team team, int attackDamage, int specialDamage)
    : damager(name, hp, team, attackDamage, specialDamage) {}

void magician::doSpecialAttack(entity* target) {
  // Fireball
  std::cout << m_name << " casts Fireball at " << target->getName() << " for "
  << m_specialDamage << " damage\n";
  target->takeDamage(m_specialDamage);

  if (!target->isAlive()) 
  {
    std::cout << target->getName() << " has been burned alive by fireball!\n";
  } else {
    std::cout << target->getName() << "'s health is now " << target->getHP() << "\n";
  }
}

bool magician::doSpecialAction(entity* target) 
{
  if (!isAlive() || !target || !target->isAlive() || target->getTeam() == getTeam()) {
    return false;
  }

  if (!spendActionPoints(getMaxActionPoints())) {
    std::cout << m_name << " does not have enough action points.\n";
    return false;
  }

  doSpecialAttack(target);
  return true;
}


void magician::print() const {
  std::cout << "[Magician] ID: " << m_id << " | Name: " << m_name
            << " | HP: " << m_hp 
            << " | Attack Damage: " << (m_attackDamage)
            << " | Special Damage: " << m_specialDamage << "\n"
            << " | Special: Fireball(Single-Target)\n"
            << " | A wizard with basic attacks, a special Fireball that hits one \n"
            << "   target.\n";
}