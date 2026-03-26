#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <conio.h>
#include <iomanip>  
#include <string>
#include "Player.hpp"
#include "Coin.hpp"
#include "Exit.hpp"
#include "Map.hpp"

// Colors
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"
#define GRAY    "\033[90m"
#define ORANGE  "\033[38;5;214m"

void render(Player& p, std::vector<Coin>& coins, Exit& e, Map& m, double elapsedSeconds) {
    std::cout << "\033[2J\033[1;1H"; 

    std::cout << CYAN << "HECTRAWURLD" << RESET << " | " 
              << YELLOW << "COINS: " << p.coins << RESET << " | " 
              << ORANGE << "TIME: " << std::fixed << std::setprecision(2) << elapsedSeconds << "s" << RESET << " | " 
              << RED << "'P' TO QUIT" << RESET << std::endl;

    for (int y = 0; y < Map::SIZE; y++) {
        for (int x = 0; x < Map::SIZE; x++) {
            if (x == p.x && y == p.y) {
                std::cout << "P ";
            } else if (x == e.x && y == e.y) {
                std::cout << GREEN << "E " << RESET;
            } else {
                bool coinFound = false;
                for (auto& c : coins) {
                    if (!c.collected && c.x == x && c.y == y) {
                        std::cout << YELLOW << "o " << RESET;
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
    bool running = true;

    while (running) { // OUTER LOOP: Handles Game Restarts
        Map gameMap;
        Player player(1, 1);
        Exit gameExit(18, 18);
        std::vector<Coin> coins = { {5, 5}, {10, 2}, {15, 10}, {3, 17}, {12, 12}, {5, 18}, {17, 4}, {10, 7}};

        auto start_time = std::chrono::steady_clock::now();
        auto last_refresh_time = std::chrono::steady_clock::now();
        const double refresh_interval = 0.25; 

        bool levelActive = true;
        while (levelActive) { // INNER LOOP: The actual gameplay
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<double> total_elapsed = now - start_time;
            std::chrono::duration<double> time_since_refresh = now - last_refresh_time;

            if (time_since_refresh.count() >= refresh_interval) {
                render(player, coins, gameExit, gameMap, total_elapsed.count());
                last_refresh_time = now;
            }

            if (_kbhit()) {
                int input = _getch();
                int nextX = player.x;
                int nextY = player.y;

                if (input == 0 || input == 224) {
                    int arrow = _getch();
                    if (arrow == 72) nextY--;      
                    else if (arrow == 80) nextY++; 
                    else if (arrow == 75) nextX--; 
                    else if (arrow == 77) nextX++; 
                } else {
                    char key = std::tolower(input);
                    if (key == 'w') nextY--;
                    else if (key == 's') nextY++;
                    else if (key == 'a') nextX--;
                    else if (key == 'd') nextX++;
                    else if (key == 'p') {
                        std::cout << RED << "\nQuit to Desktop? (y/n): " << RESET;
                        if (std::tolower(_getch()) == 'y') return 0;
                    }
                }

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
                    render(player, coins, gameExit, gameMap, total_elapsed.count());
                    
                    std::cout << CYAN << "\n===================================" << std::endl;
                    std::cout << "YOU ESCAPED! Final Score: " << RESET << YELLOW << player.coins << " coins." << RESET << std::endl;

                    if (player.coins == 8) std::cout << GREEN << "PERFECT SCORE!!!" << RESET << std::endl;
                    else if (player.coins > 3) std::cout << BLUE << "You Can Do Better!" << RESET << std::endl;
                    else if (player.coins > 0) std::cout << ORANGE << "Try Harder!!!" << RESET << std::endl;
                    else std::cout << RED << "YOU SUCK!!!!!" << RESET << std::endl;
                    
                    std::cout << CYAN << "===================================" << std::endl;

                    // PLAY AGAIN LOGIC
                    std::cout << "\nPlay Again? (y/n): " << RESET;
                    char choice = std::tolower(_getch());
                    if (choice == 'y') {
                        levelActive = false; // Breaks inner loop, starts outer loop again
                    }
                    else if (choice = 'n') {
                        std::cout << "\nClosing HECTRAWURLD... Press any key." << std::endl;
                        _getch();
                        return 0; // Exits program entirely
                    }
                    else {
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
        }
    }
    return 0;
}