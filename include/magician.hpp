#pragma once
#include "damager.hpp"
#include <vector>
#include <memory>

// A damage dealer that can cast fireball,
// a single target move that deals (special damage) to one target
class magician : public damager {
 private:
  int m_specialDamage;

 public:
  magician(const std::string& name, double hp, team team, int attackDamage,int specialDamage);

  void doSpecialAttack(entity* target) override;

  void print() const override;
  bool doSpecialAction(entity* target) override;
};