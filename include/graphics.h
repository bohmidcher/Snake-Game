#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "raylib.h"
#include "game_logic.h"
#include "map.h"


// Interface
void DrawMainMenu(GameData* game);
void DrawGameScreen(GameData* game);
void DrawGameOverScreen(GameData* game);
// Utilitaires
void DrawCenteredText(const char* text, int y, int fontSize, Color color);
void LoadTextures(void);

#endif