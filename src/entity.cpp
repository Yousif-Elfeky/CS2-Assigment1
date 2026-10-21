#include "entity.hpp"

entity::entity(const std::string& name, size_t id, double hp, team team)
    : m_name(name), m_id(id), m_hp(hp), m_maxHP(hp), m_team(team) {}

entity::~entity() {}

const std::string& entity::getName() const { return m_name; }

double entity::getHP() const { return m_hp; }

double entity::getMaxHP() const { return m_maxHP; }

size_t entity::getID() const { return m_id; }

team entity::getTeam() const { return m_team; }

targetType entity::getTarget() const { return m_target; }

bool entity::isAlly() const {
  if (m_team == team::player) {
    return true;
  }
  return false;
}

bool entity::isEnemy() const {
  if (m_team == team::environment) {
    return true;
  }
  return false;
}

bool entity::isAlive() const {
  if (m_hp > 0) return true;
  return false;
}
void entity::takeDamage(double d) {
  if (d <= 0) return;
  m_hp -= d;
  if (m_hp < 0) m_hp = 0;
}

void entity::receiveHealing(double amount) {
  if (amount <= 0) return;
  m_hp += amount;
  if (m_hp > m_maxHP) m_hp = m_maxHP;
}
