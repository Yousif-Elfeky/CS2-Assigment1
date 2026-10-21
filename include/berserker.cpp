#pragma once
#include "warrior.hpp"

class berserker : public warrior {
 private:
   double m_rageHp;

 public:
  berserker(const std::string& name, double hp, team team, int attackDamage,
            int specialDamage, int intimidate);

  void doSpecialAttack(entity* target) override;
  void takeDamage(double d) override;
  void print() const override;
};