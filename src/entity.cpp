#include "entity.hpp"

entity::entity(const std::string& name, size_t id, int hp, int speed)
    : m_name(name), m_id(id), m_hp(hp) {}

entity::~entity() {}

const std::string& entity::getName() const { return m_name; }

int entity::getHP() const { return m_hp; }

size_t entity::getID() const { return m_id; }

size_t entity::getSpeed() const { return m_speed; }

bool entity::isAlive() const {
  if (m_hp > 0) return true;
  return false;
}
void entity::takeDamage(int d) { m_hp -= d; }
