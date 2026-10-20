#include "entity.hpp"

entity::entity(const std::string& name, size_t id, int hp)
    : m_name(name), m_id(id), m_hp(hp), m_maxHP(hp) {}

entity::~entity() {}

const std::string& entity::getName() const { return m_name; }

int entity::getHP() const { return m_hp; }

int entity::getMaxHP() const { return m_maxHP; }

size_t entity::getID() const { return m_id; }

bool entity::isAlive() const {
  if (m_hp > 0) return true;
  return false;
}
void entity::takeDamage(int d) {
  if (d <= 0) return;
  m_hp -= d;
  if (m_hp < 0) m_hp = 0;
}

void entity::receiveHealing(int amount) {
  if (amount <= 0) return;
  m_hp += amount;
  if (m_hp > m_maxHP) m_hp = m_maxHP;
}
