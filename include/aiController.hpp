#pragma once

#include "controller.hpp"

// simple ai controller that always attacks the target with the lowest health
// ratio.
class aiController : public controller {
 public:
  bool takeAction(entity&, simulation&) override;
};
