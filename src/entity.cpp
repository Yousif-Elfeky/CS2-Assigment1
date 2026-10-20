#include "entity.hpp"

entity::entity(const std::string& name, size_t id, double hp, faction team,
               size_t maxActionPoints)
    : m_name(name),
      m_id(id),
      m_hp(hp),
      m_maxHP(hp),
      m_faction(team),
      m_maxActionPoints(maxActionPoints),
      m_actionPoints(maxActionPoints) {}

entity::~entity() {}

const std::string& entity::getName() const { return m_name; }

double entity::getHP() const { return m_hp; }

double entity::getMaxHP() const { return m_maxHP; }

size_t entity::getID() const { return m_id; }

faction entity::getFaction() const { return m_faction; }

bool entity::isAlly(const entity& other) const {
  return m_faction == other.m_faction;
}

bool entity::isEnemy(const entity& other) const {
  return m_faction != other.m_faction;
}

size_t entity::getActionPoints() const { return m_actionPoints; }

size_t entity::getMaxActionPoints() const { return m_maxActionPoints; }

void entity::restoreActionPoints() { m_actionPoints = m_maxActionPoints; }

bool entity::spendActionPoints(size_t amount) {
  if (amount > m_actionPoints) return false;
  m_actionPoints -= amount;
  return true;
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
