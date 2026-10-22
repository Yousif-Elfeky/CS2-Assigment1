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
  int m_actionPoints = 1;
  bool m_skipNextTurn = false;
  team m_team;
  targetType m_target;
  static size_t s_nextID;

 public:
  entity(const std::string&, double, team);

  // vitual destructor
  virtual ~entity();

  // main methods that need to be overrided by child classes
  virtual void print() const = 0;
  //// returns true if the action was successful, false otherwise
  virtual bool doNormalAction(entity* target) = 0;
  virtual bool doSpecialAction(entity* target) = 0;

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
  int getActionPoints() const;
  static constexpr int getMaxActionPoints() { return 3; }
  bool spendActionPoints(int amount);
  void restoreActionPoints(int amount = 1);
  void skipNextTurn();
  bool shouldSkipTurn();
};