#pragma once

#include <string>

#include "entity.hpp"

// abstract base for all healing entities, where the mana is not per entity but
// rather shared between them. This class contorols that flow of mana.
class healer : public entity {
 protected:
  double m_healPower;
  double m_mana;

  bool spendMana(double);

  virtual double healManaCost() const = 0;
  virtual const char* healName() const = 0;
  virtual void applyHealing(entity&) = 0;

 public:
  healer(const std::string&, size_t, double, team, double, double);

  // shared healing.
  void heal(entity&);

  bool doNormalAction(entity& target) override;

  double getMana() const;
};
