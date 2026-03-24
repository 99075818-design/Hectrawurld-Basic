#ifndef PLAYER_HPP
#define PLAYER_HPP

struct Player {
    int x, y;
    int coins;

    Player(int startX, int startY) : x(startX), y(startY), coins(0) {}
};

#endif