#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <string>

struct Entity {
    int x, y;
    int hp, maxHp, dmg, gold;
    char symbol;
    std::string name;

    Entity(int startX, int startY, int health, int damage, char sym, std::string n)
        : x(startX), y(startY), hp(health), maxHp(health), dmg(damage), gold(0), symbol(sym), name(n) {}

    bool isAlive() const { return hp > 0; }
    void takeDamage(int amount) { hp = (hp - amount < 0) ? 0 : hp - amount; }
};

#endif