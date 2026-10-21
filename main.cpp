#include <iostream>

#include "cleric.hpp"
#include "damager.hpp"
#include "druid.hpp"
#include "entity.hpp"
#include "healer.hpp"
#include "paladin.hpp"
#include "warrior.hpp"

int main() {
  warrior testWarrior("Test Warrior", 100, team::player, 20, 10, 5);
  testWarrior.print();
  return 0;
}
