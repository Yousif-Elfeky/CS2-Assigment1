#pragma once

#include <string>

#include "healer.hpp"

// a durable healer: weaker healing than the others, but the highest health.
class paladin : public healer {
 protected:
  double healManaCost() const override;
  const char* healName() const override;
  void applyHealing(entity&) override;

 public:
  paladin(const std::string& name, size_t id, double hp = 120.0,
          double healPower = 15.0, double mana = 80.0,
          faction team = faction::player, size_t maxActionPoints = 2);

  void print() const override;
};
