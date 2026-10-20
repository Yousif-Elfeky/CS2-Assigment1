#pragma once

class entity;
class simulation;

class controller {
 public:
  virtual ~controller() = default;
  virtual bool takeAction(entity&, simulation&) = 0;
};
