#pragma once

#include <string>

enum class faction { player, environment };
enum class targetSide { ally, enemy };

class entity {
 protected:
  std::string m_name;
  size_t m_id;
  double m_hp;
  double m_maxHP;
  faction m_faction;
  size_t m_maxActionPoints;
  size_t m_actionPoints;

 public:
  entity(const std::string&, size_t, double, faction team = faction::player,
         size_t maxActionPoints = 2);

  // vitual destructor
  virtual ~entity();

  virtual void print() const = 0;
  virtual bool doNormalAction(entity&) = 0;
  virtual targetSide normalTargetSide() const = 0;

  // core methods that are shared (don't need overrideding)
  static constexpr size_t normalActionCost = 1;

  const std::string& getName() const;
  double getHP() const;
  double getMaxHP() const;
  size_t getID() const;
  faction getFaction() const;
  bool isAlly(const entity&) const;
  bool isEnemy(const entity&) const;
  size_t getActionPoints() const;
  size_t getMaxActionPoints() const;
  void restoreActionPoints();
  bool spendActionPoints(size_t);
  bool isAlive() const;
  void takeDamage(double);
  void receiveHealing(double);
};
