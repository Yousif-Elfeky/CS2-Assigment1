#pragma once

#include <string>
class entity {
 protected:
  std::string m_name;
  size_t m_id;
  int m_hp;
  int m_maxHP;

 public:
  entity(const std::string&, size_t, int);

  // vitual destructor
  virtual ~entity();

  virtual void print() const = 0;

  // core methods that are shared (don't need overrideding)
  const std::string& getName() const;
  int getHP() const;
  int getMaxHP() const;
  size_t getID() const;
  bool isAlive() const;
  void takeDamage(int);
  void receiveHealing(int);
};