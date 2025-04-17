#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "raylib.h"
#include "snake.h"
#include "map.h"

// États simplifiés du jeu
typedef enum {
    MENU,
    PLAYING,
    GAME_OVER
} GameState;

// Structure de données du jeu simplifiée
typedef struct {
    GameState current_state;
    Snake snake;
    Map map;
    Sound eat_sound;
    Sound crash_sound;
    Music background_music;
    int score;
    bool grid_enabled;
    bool sound_enabled;
    float move_timer;
} GameData;

// Fonctions du jeu
void InitGame(GameData* game);
void ResetGame(GameData* game);
void UpdateGame(GameData* game);
void UnloadGame(GameData* game);
#endif // GAME_LOGIC_H