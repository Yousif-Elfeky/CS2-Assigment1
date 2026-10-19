#include "entity.hpp"

entity::entity(const std::string& name, size_t id, double hp)
    : m_name(name), m_id(id), m_hp(hp) {}

entity::~entity() {}

const std::string& entity::getName() const { return m_name; }

double entity::getHP() const { return m_hp; }

size_t entity::getID() const { return m_id; }

bool entity::isAlive() const {
  if (m_hp > 0) return true;
  return false;
}
void entity::takeDamage(double d) { m_hp -= d; }
