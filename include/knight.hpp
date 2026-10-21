#pragma once
#include "warrior.hpp"

class knight : public warrior {
 private:
  bool m_parry;

 public:
  knight(const std::string& name, double hp, team team, int attackDamage, int specialDamage, int intimidate);

  void doSpecialAttack(entity* target) override;
  void takeDamage(double d) override;
  void print() const override;
};