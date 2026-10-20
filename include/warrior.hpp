#pragma once
#include "entity.hpp"

class warrior : public entity {
private:
    int m_attackDamage;
    int m_intimidate;  //Special: Chance to make enemies lose their turn. assignment says that each
                     //entity must interact with other entities or the simworld in a unique way
public:
    warrior(const std::string& name, size_t id, int hp, int speed, int attackDamage);

    void doNormalAttack(entity& target) override;
    void doSpecialAttack(entity& target) override;
    void print() const override;

    //int dealDamage() const;
    //int useIntimidate() const;
};