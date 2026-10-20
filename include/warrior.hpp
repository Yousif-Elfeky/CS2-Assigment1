#pragma once
#include "damager.hpp"

class warrior : public damager {
private:
    int m_intimidate;

public:
    warrior(const std::string& name, size_t id, int hp, int attackDamage, int specialDamage, int intimidate);

    void doSpecialAttack(entity& target) override;
    void print() const override;
};