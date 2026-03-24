#ifndef COIN_HPP
#define COIN_HPP

struct Coin {
    int x, y;
    bool collected;

    Coin(int startX, int startY) : x(startX), y(startY), collected(false) {}
};

#endif