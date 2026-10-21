#pragma once
#include "damager.hpp"

class warrior : public damager {
 protected:
  int m_intimidate;

 public:
  warrior(const std::string& name, double hp, team team, int attackDamage,
          int specialDamage, int intimidate);

  void doSpecialAttack(entity* target) override;
  void print() const override;
};