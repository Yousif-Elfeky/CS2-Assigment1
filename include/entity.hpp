#pragma once

#include <string>

enum class team { player, environment };
enum class targetType { ally, enemy };
class entity {
 protected:
  std::string m_name;
  size_t m_id;
  double m_hp;
  double m_maxHP;
  team m_team;
  targetType m_target;

 public:
  entity(const std::string&, size_t, double, team);

  // vitual destructor
  virtual ~entity();

  virtual void print() const = 0;

  // core methods that are shared (don't need overrideding)
  const std::string& getName() const;
  double getHP() const;
  double getMaxHP() const;
  size_t getID() const;
  bool isAlive() const;
  bool isAlly() const;
  bool isEnemy() const;
  team getTeam() const;
  targetType getTarget() const;
  void takeDamage(double);
  void receiveHealing(double);
};