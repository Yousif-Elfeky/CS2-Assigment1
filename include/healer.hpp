#pragma once

#include <string>

#include "entity.hpp"

// abstract base for all healing entities, which can heal allies and themselves.
class healer : public entity {
 protected:
  double m_healPower;
  double m_mana;
  double m_maxMana;

  bool spendMana(double);

  virtual double healManaCost() const = 0;
  virtual const char* healName() const = 0;
  virtual void applyHealing(entity* target) = 0;

 public:
  healer(const std::string&, double, team, double, double);

  // shared healing.
  void heal(entity* target);

  bool doNormalAction(entity* target) override;
  virtual bool doSpecialAction(entity* target) override = 0;

  void regenMana(double amount);

  double getMana() const;

  double getMaxMana() const;
};
