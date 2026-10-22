#include "warrior.hpp"

#include <cstdlib>
#include <print>

warrior::warrior(const std::string& name, double hp, team team,
                 int attackDamage, int specialDamage, int intimidate)
    : damager(name, hp, team, attackDamage, specialDamage),
      m_intimidate(intimidate) {}

void warrior::doSpecialAttack(entity* target) {
  std::print("{} attempts to intimidate {}...", m_name, target->getName());

  const bool successful = m_intimidate > 0 && std::rand() % 2 == 1;
  if (successful) {
    target->skipNextTurn();
    std::println("{} is successfully intimidated and skips their next turn!",
                 target->getName());
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
