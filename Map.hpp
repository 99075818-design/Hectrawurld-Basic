#ifndef MAP_HPP
#define MAP_HPP

#include <cstdlib>

class Map {
public:
    static const int WIDTH = 40;
    static const int HEIGHT = 40;

    int layout[HEIGHT][WIDTH]; 
    bool explored[HEIGHT][WIDTH]; 

    Map() {
        for(int y = 0; y < HEIGHT; y++) {
            for(int x = 0; x < WIDTH; x++) {
                explored[y][x] = false;
                if(y == 0 || y == HEIGHT - 1 || x == 0 || x == WIDTH - 1) 
                    layout[y][x] = 1;
                else if(std::rand() % 100 < 5) 
                    layout[y][x] = 1;
                else if(std::rand() % 100 < 2) 
                    layout[y][x] = 2;
                else 
                    layout[y][x] = 0;
            }
        }
        layout[HEIGHT - 2][WIDTH - 2] = 3; 
    }

    bool isWalkable(int x, int y) const {
        if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return false;
        return layout[y][x] != 1;
    }

    void reveal(int px, int py) {
        for(int y = py - 3; y <= py + 3; y++) {
            for(int x = px - 3; x <= px + 3; x++) {
                if(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) 
                    explored[y][x] = true;
            }
        }
    }
};

#endif