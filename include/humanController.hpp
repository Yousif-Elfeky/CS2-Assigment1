#pragma once

#include "controller.hpp"

// custom human controller that allows the user to choose which action to take
// for a given entity.
class humanController : public controller {
 public:
  bool takeAction(entity&, simulation&) override;
};
