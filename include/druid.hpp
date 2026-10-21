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
  druid(const std::string& name, double hp = 80.0, team team = team::player,
        double healPower = 18.0, double mana = 90.0);

  void print() const override;
};
