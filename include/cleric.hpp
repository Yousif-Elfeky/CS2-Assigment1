#pragma once

#include <string>

#include "healer.hpp"

// a holy caster with the strongest direct healing.
class cleric : public healer {
 protected:
  double healManaCost() const override;
  const char* healName() const override;
  void applyHealing(entity&) override;

 public:
  cleric(const std::string& name, size_t id, double hp = 90.0,
         double healPower = 25.0, double mana = 100.0,
         faction team = faction::player, size_t maxActionPoints = 2);

  void print() const override;
};
