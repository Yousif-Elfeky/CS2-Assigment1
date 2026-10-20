#pragma once

#include <string>
class entity {
 protected:
  std::string m_name;
  size_t m_id;
  int m_hp;
  int m_speed; //Determines Turn order (Higher speed entities go first, good idea?)

 public:
  entity(const std::string&, size_t, int, int);

  // vitual destructor
  virtual ~entity();

  // core methods to be overriden
  virtual void doNormalAttack(entity&) = 0;
  virtual void doSpecialAttack(entity&) = 0;
  virtual void print() const = 0;

  // core methods that are shared (don't need overrideding)
  const std::string& getName() const;
  int getHP() const;
  int getSpeed() const;
  size_t getID() const;
  bool isAlive() const;
  void takeDamage(int);
};