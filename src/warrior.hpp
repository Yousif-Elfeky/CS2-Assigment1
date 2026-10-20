#include "warrior.hpp"
#include <iostream>

warrior::warrior(const std::string& name, size_t id, int hp, int speed, int attackDamage, 
    int intimidate): entity(name, id, hp, speed), m_attackDamage(attackDamage), 
    m_intimidate(intimidate) {}

void warrior::doNormalAttack(entity& target) 
{
    std::cout << m_name << " slashes " << target.getName() << " for " << m_attackDamage << " damage\n";
    target.takeDamage(m_attackDamage);
    std::cout << target.getName() << "'s health is now " << target.getHP() << "\n";
    if (!target.isAlive())
    {
        std::cout << target.getName() << " has been slain!\n";
    }
}

void warrior::doSpecialAttack(entity& target) 
{
    std::cout << m_name << " attempts to intimidate " << target.getName() << "...";
    
    int roll = std::rand() % 2;

    if (roll == 1) {
        std::cout << target.getName() << " is successfully intimidated and skips their turn!\n";
        // Make enemy skip turn (Set their damage=0 for one turn turn only?)
        //target.attackDamage = 0;
    } else {
        std::cout << target.getName() << " ignores " << m_name << "'s intimidation attempt\n";
    }
}

void warrior::print() const {
    std::cout << "[Warrior] ID: " << m_id 
              << " | Name: " << m_name 
              << " | HP: " << m_hp 
              << " | Speed: " << m_speed 
              << " | Attack Damage: " << m_attackDamage 
              << " | Intimidate: " << m_intimidate << "\n";
}