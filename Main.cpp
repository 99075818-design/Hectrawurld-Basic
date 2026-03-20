#include <iostream>
#include <conio.h>
#include <vector>
#include <ctime>
#include "Entity.hpp"
#include "Map.hpp"
#include "GameEngine.hpp"

void render(const Entity& p, const std::vector<Entity>& enemies, Map& m, GameEngine& eng) {
    std::cout << "\033[2J\033[1;1H"; 
    std::cout << "=== HECTRAWURLD === HP: " << p.hp << "/" << p.maxHp << "\n";

    m.reveal(p.x, p.y); // Update Fog of War

    for (int y = 0; y < Map::HEIGHT; y++) {
        for (int x = 0; x < Map::WIDTH; x++) {
            if (!m.explored[y][x]) {
                std::cout << "  "; // Hidden by Fog
                continue;
            }

            bool enemyHere = false;
            if (x == p.x && y == p.y) std::cout << "P ";
            else {
                for(const auto& e : enemies) {
                    if(e.isAlive() && e.x == x && e.y == y) {
                        std::cout << "G ";
                        enemyHere = true;
                        break;
                    }
                }
                if(!enemyHere) {
                    if (m.layout[y][x] == 1) std::cout << "# ";
                    else if (m.layout[y][x] == 2) std::cout << "+ ";
                    else if (m.layout[y][x] == 3) std::cout << "E ";
                    else std::cout << ". ";
                }
            }
        }
        std::cout << "\n";
    }

    std::cout << "\n--- LOG ---\n";
    for(const auto& line : eng.log) std::cout << line << "\n";
}

int main() {
    srand(time(0)); // Seed random
    Map gameMap;
    Entity player(1, 1, 100, 20, 'H', "Hero");
    GameEngine engine;

    std::vector<Entity> goblins;
    for(int i=0; i<3; i++) {
        goblins.push_back(Entity(rand()%30+5, rand()%15+2, 40, 8, 'G', "Goblin " + std::to_string(i+1)));
    }

    while (player.isAlive()) {
        render(player, goblins, gameMap, engine);

        char move = _getch();
        int nX = player.x, nY = player.y;
        if (move == 'w') nY--; else if (move == 's') nY++;
        else if (move == 'a') nX--; else if (move == 'd') nX++;
        else if (move == 'q') break;

        if (gameMap.isWalkable(nX, nY)) {
            player.x = nX; player.y = nY;
            engine.handleTile(player, gameMap);
        }

        for(auto& g : goblins) {
            if (player.x == g.x && player.y == g.y && g.isAlive()) {
                engine.startCombat(player, g);
            }
        }
    }

    return 0;
}