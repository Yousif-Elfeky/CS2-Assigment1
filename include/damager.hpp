#pragma once
#include "entity.hpp"

// abstract base for all damage dealer entities, which can attack target and perform special attacks.
class damager : public entity {
 protected:
  int m_attackDamage;
  int m_specialDamage;

 public:
  damager(const std::string& name, double hp, team team, int attackDamage,
          int specialDamage);
  virtual ~damager();

  bool doNormalAction(entity* target) override;
  bool doSpecialAction(entity* target) override;

  virtual void doNormalAttack(entity* target);
  virtual void doSpecialAttack(entity*) = 0;
};