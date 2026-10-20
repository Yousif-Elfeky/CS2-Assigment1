#pragma once

#include <string>
class entity {
 protected:
  std::string m_name;
  size_t m_id;
  double m_hp;
  double m_maxHP;

 public:
  entity(const std::string&, size_t, int, int);

  // vitual destructor
  virtual ~entity();

  virtual void print() const = 0;

  // core methods that are shared (don't need overrideding)
  const std::string& getName() const;
  double getHP() const;
  double getMaxHP() const;
  size_t getID() const;
  bool isAlive() const;
  void takeDamage(double);
  void receiveHealing(double);
};