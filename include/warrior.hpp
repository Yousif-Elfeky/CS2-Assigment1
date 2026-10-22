#pragma once
#include "damager.hpp"

//Standard damage dealer that can intimidate enemies, causing them to skip their next turn. 
//Knight and Berserker are improved versions of this unit
class warrior : public damager {
 protected:
  int m_intimidate; //Rolls 0 or 1. Failure and success respectively.

 public:
  warrior(const std::string& name, double hp, team team, int attackDamage,
          int specialDamage, int intimidate);

  void doSpecialAttack(entity* target) override;
  void print() const override;
  bool doSpecialAction(entity* target) override;
};