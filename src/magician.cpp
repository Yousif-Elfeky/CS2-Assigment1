#include "magician.hpp"

#include <cstdlib>
#include <iostream>

magician::magician(const std::string& name, double hp, team team, int attackDamage, int specialDamage)
    : damager(name, hp, team, attackDamage, 0),m_specialDamage(specialDamage) {}

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

//Magic Missiles
void magician::doMagicMissles(std::vector<std::unique_ptr<entity>>& allEnemies) 
{
  std::cout << m_name << " unleashes a barrage of magic missiles at all enemies\n";

  for (const auto& entityPtr : allEnemies) {
    if (entityPtr->isAlive() && entityPtr->getTeam() != m_team) {
      std::cout << " A magic missile blasts " << entityPtr->getName() << " for " << m_specialDamage << " damage\n";
      entityPtr->takeDamage(m_specialDamage);

      if (!entityPtr->isAlive()) {
        std::cout << "  - " << entityPtr->getName() << " was blasted by a magic missile\n";
      } else {
        std::cout << "  - " << entityPtr->getName() << "'s health is now " << entityPtr->getHP() << "\n";
      }
    }
  }
}

void magician::print() const {
  std::cout << "[Magician] ID: " << m_id << " | Name: " << m_name
            << " | HP: " << m_hp 
            << " | Attack Damage: " << (m_attackDamage)
            << " | Special Damage: " << m_specialDamage << "\n"
            << " | Special: Fireball(Single-Target) or Magic Missiles(Multi-hit)\n"
            << " | A wizard with basic attacks, a special Fireball that hits one \n"
            << "   target, and special Magic Missiles that hit all available targets.\n";
}