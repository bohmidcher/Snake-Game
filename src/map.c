#include "map.h"
#include "snake.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "raylib.h"
#include "raymath.h" 
#include "config.h"

// Initialisation de la carte
void InitMap(Map* map, bool with_walls) {
    // Initialiser le générateur aléatoire
    static bool rand_initialized = false;
    if (!rand_initialized) {
        srand((unsigned int)time(NULL));
        rand_initialized = true;
    }
    
    // Initialiser les murs
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            map->walls[x][y] = with_walls && (x == 0 || x == GRID_SIZE-1 || y == 0 || y == GRID_SIZE-1);
        }
    }

    // Initialiser le fruit
    map->fruit.active = false;
    map->fruit.type = FRUIT_NORMAL; // Initialiser le type de fruit
}

void SpawnFruit(Map* map, Snake* snake) {
    // Liste des positions libres
    Vector2 free_positions[GRID_SIZE * GRID_SIZE];
    int free_count = 0;
    // Récupérer toutes les positions libres
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            // Vérifier si la position est un mur
            if (map->walls[x][y]) continue;
            // Vérifier si le serpent occupe cette position
            bool occupied = false;
            SnakeNode* current = snake->head;
            while (current != NULL) {
                if (current->position.x == x && current->position.y == y) {
                    occupied = true;
                    break;
                }
                current = current->next;
            }
            if (!occupied) {
                free_positions[free_count++] = (Vector2){x, y};
            }
        }
    }
    // Si aucune position libre, ne pas générer de fruit
    if (free_count == 0) {
        map->fruit.active = false;
        return;
    }
    // Choisir une position aléatoire parmi les positions libres
    int random_index = rand() % free_count;
    map->fruit.position = free_positions[random_index];
    map->fruit.active = true;
}

bool CheckWallCollision(Map* map, Vector2 position) {
    const int x = position.x;
    const int y = position.y;
    // Vérifier les limites de la grille
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE) {
        return true;
    }
    // Vérifier si la position est un mur
    return map->walls[x][y];
}
