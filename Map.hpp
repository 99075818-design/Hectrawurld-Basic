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
    
        //i split by walls (the lines)

        grid[10][4] = 1;
        grid[10][5] = 1;
        grid[10][6] = 1;
        grid[10][7] = 1;
        grid[10][8] = 1;

        grid[1][3] = 1;
        grid[2][3] = 1;
        grid[3][3] = 1;
        grid[4][3] = 1;
        grid[5][3] = 1;
        grid[6][3] = 1;

        grid[6][4] = 1;
        grid[6][5] = 1;
        grid[6][6] = 1;

        grid[5][6] = 1;
        grid[4][6] = 1;

        grid[8][14] = 1;
        grid[9][14] = 1;
        grid[10][14] = 1;
        grid[11][14] = 1;
        grid[12][14] = 1;
        grid[13][14] = 1;

        grid[11][13] = 1;
        grid[11][12] = 1;
        grid[11][11] = 1;

        grid[12][11] = 1;
        grid[13][11] = 1;

        grid[13][12] = 1;
        
        grid[8][3] = 1;
        grid[9][3] = 1;
        grid[10][3] = 1;
        grid[11][3] = 1;
        grid[12][3] = 1;
        grid[13][3] = 1;
        grid[14][3] = 1;
        grid[15][3] = 1;

        grid[16][2] = 1;
        grid[16][3] = 1;
        grid[16][4] = 1;

        grid[12][2] = 1;
        grid[14][1] = 1;
        grid[5][2] = 1;
        grid[2][1] = 1;
        grid[7][1] = 1;
        grid[10][1] = 1;
        grid[2][6] = 1;
        grid[3][6] = 1;
        grid[2][6] = 1;
        grid[4][5] = 1;

        grid[17][2] = 1;
        grid[17][4] = 1;
        grid[18][4] = 1;

        grid[12][5] = 1;
        grid[12][6] = 1;
        grid[13][5] = 1;
        grid[13][6] = 1;

        grid[12][7] = 1;
        grid[12][8] = 1;
        grid[12][9] = 1;
        grid[12][10] = 1;

        grid[16][5] = 1;
        grid[16][6] = 1;
        grid[16][7] = 1;
        grid[15][7] = 1;

        grid[2][6] = 1;
        grid[2][4] = 1;

        grid[8][6] = 1;
        grid[8][7] = 1;
        grid[8][8] = 1;
        grid[8][9] = 1;
        grid[8][9] = 1;
        grid[8][10] = 1;
        grid[8][11] = 1;
        grid[8][12] = 1;

        grid[7][9] = 1;
        grid[6][9] = 1;
        grid[5][9] = 1;
        grid[4][9] = 1;
        grid[3][9] = 1;
        grid[2][9] = 1;

        grid[8][9] = 1;

    }

    bool isWalkable(int x, int y) {
        if (x < 0 || x >= SIZE || y < 0 || y >= SIZE) return false;
        return grid[y][x] == 0;
    }
};

#endif