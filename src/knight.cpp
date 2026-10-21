#include "knight.hpp"
#include <cstdlib>
#include <iostream>

knight::knight(const std::string& name, double hp, team team, int attackDamage, int specialDamage, 
    int intimidate) : warrior(name, hp, team, attackDamage, specialDamage, intimidate),m_parry(false) {}

void knight::doSpecialAttack(entity* target) {
  int choice = std::rand() % 2;

  if (choice == 0) {
    std::cout << m_name << " attempts to intimidate " << target->getName()
              << "...";

    int roll = std::rand() % 2;

    if (roll == 1 && m_intimidate > 0) {
      std::cout << target->getName()
                << " is successfully intimidated and skips their turn!\n";
    } else {
      std::cout << target->getName() << " ignores " << m_name
                << "'s intimidation attempt\n";
    }
  } else {
    doNormalAttack(target);

    m_parry = true;
    std::cout << m_name << " The knight is ready to parry the next attack, negating all damage\n";
  }
}

void knight::takeDamage(double d) {
  if (m_parry) {
    std::cout << m_name << " Attack parried. 0 damage taken.\n";
    m_parry = false;
    return;
  }
  entity::takeDamage(d);
}

void knight::print() const {
  std::cout << "[Knight] ID: " << m_id << " | Name: " << m_name
            << " | HP: " << m_hp << " | Attack Damage: " << m_attackDamage
            << " | Special: Either Intimidates or Parries the next incoming attack\n"
            << " | A more defensive warrior capable of intimidating foes or parrying, which\n" 
            << "   initiates a normal attack followed by blocking the next incoming attack\n";
}