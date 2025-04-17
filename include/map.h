#ifndef MAP_H
#define MAP_H

#include "snake.h"
#include "raylib.h"
#include "raymath.h" 
#include "config.h"
#include <stdbool.h>

typedef struct Snake Snake;
typedef enum {
    FRUIT_NORMAL,
} FruitType;
    
typedef struct {
    Vector2 position;
    bool active;
    FruitType type;
} Fruit;

typedef struct {
    bool walls[GRID_SIZE][GRID_SIZE];
    Fruit fruit;
} Map;

void InitMap(Map* map, bool with_walls);
void SpawnFruit(Map* map, Snake* snake);
bool CheckWallCollision(Map* map, Vector2 position);
bool CheckPositionValid(Map* map, Snake* snake, Vector2 position);


#endif