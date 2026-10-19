#pragma once

#include <string>
class entity {
 protected:
  std::string m_name;
  size_t m_id;
  double m_hp;

 public:
  entity(const std::string&, size_t, double);

  // vitual destructor
  virtual ~entity();

  // core methods to be overriden
  virtual void doNormalAttack(entity&) = 0;
  virtual void doSpicialAttack(entity&) = 0;
  virtual void print() const = 0;

  // core methods that are shared (don't need overrideding)
  const std::string& getName() const;
  double getHP() const;
  size_t getID() const;
  bool isAlive() const;
  void takeDamage(double);
};