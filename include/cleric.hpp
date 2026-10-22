#pragma once

#include <string>

#include "healer.hpp"

// a holy caster with the strongest direct healing.
class cleric : public healer {
 protected:
  double healManaCost() const override;
  const char* healName() const override;
  void applyHealing(entity* target) override;

 public:
  cleric(const std::string& name, double hp = 90.0, team team = team::player,
         double healPower = 25.0, double mana = 100.0);

  void print() const override;
  bool doSpecialAction(entity* target) override;
};
