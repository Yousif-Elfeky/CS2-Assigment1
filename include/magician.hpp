#pragma once
#include "damager.hpp"
#include <vector>
#include <memory>

class magician : public damager {
 private:
  int m_specialDamage;

 public:
  magician(const std::string& name, double hp, team team, int attackDamage,int specialDamage);

  void doSpecialAttack(entity* target) override;
  void doMagicMissles(std::vector<std::unique_ptr<entity>>& allEnemies);
  
  void print() const override;
};