#ifndef SNAKE_H
#define SNAKE_H

#include "raylib.h"
#include "map.h"

// Structure pour un nœud du serpent
typedef struct SnakeNode {
    Vector2 position;
    struct SnakeNode* next;
    struct SnakeNode* prev;
} SnakeNode;

// Structure principale du serpent
typedef struct Snake {
    SnakeNode* head;
    SnakeNode* tail;
    Vector2 direction;
    float speed;
    Color color;
    int length;
} Snake;

// Fonctions de gestion du serpent
void InitSnake(Snake* snake, Vector2 start_pos);
void MoveSnake(Snake* snake);
void GrowSnake(Snake* snake);
void FreeSnake(Snake* snake);
bool CheckSelfCollision(Snake* snake);
void ChangeSnakeDirection(Snake* snake, Vector2 new_dir);

#endif