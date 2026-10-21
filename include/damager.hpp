#pragma once
#include "entity.hpp"

class damager : public entity {
 protected:
  int m_attackDamage;
  int m_specialDamage;

 public:
  damager(const std::string& name, double hp, team team, int attackDamage,
          int specialDamage);
  virtual ~damager();

  bool doNormalAction(entity& target) override;

  virtual void doNormalAttack(entity&);
  virtual void doSpecialAttack(entity&) = 0;
};