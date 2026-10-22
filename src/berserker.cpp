#include "berserker.hpp"
#include <cstdlib>
#include <iostream>

berserker::berserker(const std::string& name, double hp, team team, int attackDamage,int specialDamage, 
    int intimidate) : warrior(name, hp, team, attackDamage, specialDamage, intimidate), m_rageHp(hp) {}

void berserker::doSpecialAttack(entity* target) 
{
  std::cout << m_name << " enrages and lunges at " << target->getName()
            << " for " << m_specialDamage + ((m_rageHp - m_hp)*2) << " damage\n";
  
  target->takeDamage(m_specialDamage + ((m_rageHp - m_hp)*2));

  if (!target->isAlive()) {
    std::cout << target->getName() << " was consumed by "<< m_name <<"'s rage!\n";
  } else {
    std::cout << target->getName() << "'s health is now " << target->getHP() << "\n";
  }
}

void berserker::takeDamage(double d) {
  double bd = d*2;
  entity::takeDamage(bd);
}

bool berserker::doSpecialAction(entity* target) 
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

void berserker::print() const {
  std::cout << "[Berserker] ID: " << m_id << " | Name: " << m_name
            << " | HP: " << m_hp << "/" << m_maxHP 
            << " | Attack: " << m_attackDamage 
            << " | Special: May attack with Rage, dealing " << m_specialDamage << " + Missing HP)\n"
            << " | Aggressive, unarmored warrior whose rage attack becomes more powerful as it takes damage. Takes more damage by default\n";
}