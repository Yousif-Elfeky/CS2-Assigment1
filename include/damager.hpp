#pragma once
#include "entity.hpp"

class damager : public entity {
protected:
    int m_attackDamage;
    int m_specialDamage;

public:
    damager(const std::string& name, size_t id, int hp, int speed, int attackDamage,int specialDamage);
    virtual ~damager();

    virtual void doNormalAttack(entity&) = 0;
    virtual void doSpecialAttack(entity&) = 0;
};