#ifndef GAMEENGINE_HPP
#define GAMEENGINE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <conio.h>
#include "Entity.hpp"
#include "Map.hpp" // Make sure this is here

class GameEngine {
public:
    std::vector<std::string> log;

    void addLog(std::string msg) {
        log.push_back(msg);
        if(log.size() > 5) log.erase(log.begin());
    }

    // --- ADD THIS FUNCTION BACK IN ---
    void handleTile(Entity& player, Map& map) {
        int tile = map.layout[player.y][player.x];
        
        // If tile is 2 (Medkit '+')
        if (tile == 2) {
            player.hp = player.maxHp; 
            map.layout[player.y][player.x] = 0; // Remove medkit from map
            addLog("(!) Found a Medkit! HP Restored.");
        } 
        // If tile is 3 (Exit 'E')
        else if (tile == 3) {
            addLog("The exit is right here! Step on it to escape.");
        }
    }

    void startCombat(Entity& player, Entity& enemy) {
        bool inCombat = true;
        while(inCombat && enemy.isAlive() && player.isAlive()) {
            std::cout << "\033[2J\033[1;1H"; 
            std::cout << "--- BATTLE: " << enemy.name << " ---\n";
            std::cout << "Player HP: " << player.hp << " | " << enemy.name << " HP: " << enemy.hp << "\n";
            std::cout << "1. Attack  2. Block (Half Damage)  3. Flee\n";
            
            char choice = _getch();
            if(choice == '1') {
                enemy.takeDamage(player.dmg);
                addLog("You slashed " + enemy.name + "!");
                if(enemy.isAlive()) {
                    player.takeDamage(enemy.dmg);
                    addLog(enemy.name + " counter-attacked!");
                }
            } 
            else if(choice == '2') {
                addLog("You braced for impact!");
                player.takeDamage(enemy.dmg / 2);
                addLog(enemy.name + " hit your shield!");
            }
            else if(choice == '3') {
                addLog("You scrambled away safely!");
                inCombat = false;
            }

            if(!enemy.isAlive()) {
                int loot = rand() % 20 + 10;
                player.gold += loot;
                addLog("Killed " + enemy.name + "! Found " + std::to_string(loot) + " coins.");
                inCombat = false;
            }
        }
    }
};

#endif