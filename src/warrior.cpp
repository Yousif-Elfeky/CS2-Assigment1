#include "warrior.hpp"

#include <cstdlib>
#include <print>

warrior::warrior(const std::string& name, double hp, team team,
                 int attackDamage, int specialDamage, int intimidate)
    : damager(name, hp, team, attackDamage, specialDamage),
      m_intimidate(intimidate) {}

void warrior::doSpecialAttack(entity* target) {
  std::print("{} attempts to intimidate {}...", m_name, target->getName());

  int roll = std::rand() % 2;

  if (roll == 1 && m_intimidate > 0) {
    std::println("{} is successfully intimidated and skips their turn!",
                 target->getName());
    // Make enemy skip turn (Set their damage=0 for one turn turn only?)
    // target->attackDamage = 0;
  } else {
    std::println("{} ignores {}'s intimidation attempt", target->getName(),
                 m_name);
  }
}

void warrior::print() const {
  std::println("[Warrior] ID: {} | Name: {} | HP: {} | Attack Damage: {}",
               m_id, m_name, m_hp, m_attackDamage);
  std::println("Special: Intimidate (Medium Success Rate)");
  std::println("Basic front line attacker. Can attempt to intimidate foes to "
               "stun them for one turn.");
}
