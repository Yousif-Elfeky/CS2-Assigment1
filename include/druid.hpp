#pragma once

#include <string>

#include "healer.hpp"

// a nature healer that shares its healing with itself.
class druid : public healer {
 protected:
  double healManaCost() const override;
  const char* healName() const override;
  void applyHealing(entity&) override;

 public:
  druid(const std::string& name, size_t id, double hp = 80.0,
        double healPower = 18.0, double mana = 90.0,
        faction team = faction::player, size_t maxActionPoints = 2);

  void print() const override;
};
