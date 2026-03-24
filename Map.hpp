#ifndef MAP_HPP
#define MAP_HPP

class Map {
public:
    static const int SIZE = 20;
    int grid[SIZE][SIZE];

    Map() {
        for (int y = 0; y < SIZE; y++) {
            for (int x = 0; x < SIZE; x++) {
                if (y == 0 || y == SIZE - 1 || x == 0 || x == SIZE - 1) 
                    grid[y][x] = 1; 
                else 
                    grid[y][x] = 0; 
            }
        }
    }

    bool isWalkable(int x, int y) {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return false;
        return grid[y][x] == 0;
    }
};

#endif