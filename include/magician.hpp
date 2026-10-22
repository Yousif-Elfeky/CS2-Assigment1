#pragma once
#include "damager.hpp"
#include <vector>
#include <memory>

// A damage dealer that can cast magic missiles, dealing damage to multiple enemies.
// Also casts fireball, a single target move that deals special damage to one target
class magician : public damager {
 private:
  int m_specialDamage;

 public:
  magician(const std::string& name, double hp, team team, int attackDamage,int specialDamage);

  void doSpecialAttack(entity* target) override;
  void doMagicMissles(std::vector<std::unique_ptr<entity>>& allEnemies);
  
  void print() const override;
  bool doSpecialAction(entity* target) override;
  bool doMultiTargetSpecialAction(std::vector<std::unique_ptr<entity>>& allEntities);
};