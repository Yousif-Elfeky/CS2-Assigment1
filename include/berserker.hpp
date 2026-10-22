#pragma once
#include "warrior.hpp"

// An agressive warrior that gains rage when taking damage, increasing its special move's damage
class berserker : public warrior {
 private:
   double m_rageHp;

 public:
  berserker(const std::string& name, double hp, team team, int attackDamage,
            int specialDamage, int intimidate);

  void doSpecialAttack(entity* target) override;
  void takeDamage(double d) override;  //Takes more damage than normal
  void print() const override;
  bool doSpecialAction(entity* target) override;
};