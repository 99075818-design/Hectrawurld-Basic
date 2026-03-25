#include <iostream>
#include <vector>
#include <conio.h>
#include "Player.hpp"
#include "Coin.hpp"
#include "Exit.hpp"
#include "Map.hpp"

void render(Player& p, std::vector<Coin>& coins, Exit& e, Map& m) {
    std::cout << "\033[2J\033[1;1H"; 
    std::cout << "HECTRAWURLD | COINS: " << p.coins << " | 'q' to Quit\n";

    for (int y = 0; y < Map::SIZE; y++) {
        for (int x = 0; x < Map::SIZE; x++) {
            if (x == p.x && y == p.y) {
                std::cout << "P "; // Player
            } else if (x == e.x && y == e.y) {
                std::cout << "E "; // Exit
            } else {
                bool coinFound = false;
                for (auto& c : coins) {
                    if (!c.collected && c.x == x && c.y == y) {
                        std::cout << "o "; // Coin
                        coinFound = true;
                        break;
                    }
                }
                if (!coinFound) {
                    std::cout << (m.grid[y][x] == 1 ? "# " : ". ");
                }
            }
        }
        std::cout << "\n";
    }
}

int main() {
    Map gameMap;
    Player player(1, 1);
    Exit gameExit(18, 18);
    
    std::vector<Coin> coins = { {5, 5}, {10, 2}, {15, 10}, {3, 17}, {12, 12} };

    while (true) {
        render(player, coins, gameExit, gameMap);

        char input = _getch();
        char key = std::tolower(input);
        int nextX = player.x;
        int nextY = player.y;

        if (key == 'w') nextY--;
        else if (key == 's') nextY++;
        else if (key == 'a') nextX--;
        else if (key == 'd') nextX++;
        else if (key == 'q') break;

        if (gameMap.isWalkable(nextX, nextY)) {
            player.x = nextX;
            player.y = nextY;
        }

        for (auto& c : coins) {
            if (!c.collected && player.x == c.x && player.y == c.y) {
                c.collected = true;
                player.coins++;
            }
        }

        if (player.x == gameExit.x && player.y == gameExit.y) {
            render(player, coins, gameExit, gameMap);
            
            std::cout << "\n===================================" << std::endl;
            std::cout << "YOU ESCAPED! Final Score: " << player.coins << " coins." << std::endl;

            if (player.coins == 5) {
                std::cout << "PERFECT SCORE!!!" << std::endl;
            }

            else if (player.coins < 5) {
                std::cout << "You Can Do Better!" << std::endl;
            }
            
            std::cout << "===================================" << std::endl;
            std::cout << "\nPress any key to close the game..." << std::endl;

            _getch();
            break;
        }
    }
    return 0;
}