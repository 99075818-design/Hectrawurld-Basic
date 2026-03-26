#include <iostream>
#include <vector>
#include <conio.h>
#include "Player.hpp"
#include "Coin.hpp"
#include "Exit.hpp"
#include "Map.hpp"

//colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define GRAY "\033[90m"
#define LIGHT_GRAY "\033[37m"
#define ORANGE "\033[38;5;214m"

void render(Player& p, std::vector<Coin>& coins, Exit& e, Map& m) {
    std::cout << "\033[2J\033[1;1H"; 
    std::cout << CYAN << "HECTRAWURLD" << RESET << " | " << YELLOW << "COINS: " << p.coins << RESET << " | " << RED << "'p' to Quit\n" << RESET;

    for (int y = 0; y < Map::SIZE; y++) {
        for (int x = 0; x < Map::SIZE; x++) {
            if (x == p.x && y == p.y) {
                std::cout << "P "; // Player
            } else if (x == e.x && y == e.y) {
                std::cout << GREEN << "E " << RESET; // Exit
            } else {
                bool coinFound = false;
                for (auto& c : coins) {
                    if (!c.collected && c.x == x && c.y == y) {
                        std::cout << YELLOW << "o " << RESET; // Coin
                        coinFound = true;
                        break;
                    }
                }
                if (!coinFound) {
                    std::cout << GRAY << (m.grid[y][x] == 1 ? "X " : "  ") << RESET;
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
    
    std::vector<Coin> coins = { {5, 5}, {10, 2}, {15, 10}, {3, 17}, {12, 12}, {5, 18}, {17, 4}, {10, 7}};

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
        else if (key == 'p') break;

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
            
            std::cout << CYAN << "\n===================================" << std::endl;
            std::cout << "YOU ESCAPED! Final Score: " << RESET << YELLOW << player.coins << " coins." << RESET << std::endl;

            if (player.coins == 8) {
                std::cout << GREEN << "PERFECT SCORE!!!" << RESET << std::endl;
            }

            else if (player.coins < 8 && player.coins > 3) {
                std::cout << BLUE << "You Can Do Better!" << RESET << std::endl;
            }

            else if (player.coins < 4 && !player.coins == 0) {
                std::cout << ORANGE << "Try Harder!!!" << RESET << std::endl;
            }

            else if (player.coins == 0) {
                std::cout << RED << "YOU SUCK!!!!!" << RESET << std::endl;
            }
            
            std::cout << CYAN << "===================================" << std::endl;
            std::cout << "\nPress any key to close the game..." << RESET << std::endl;

            _getch();
            break;
        }
    }
    return 0;
}