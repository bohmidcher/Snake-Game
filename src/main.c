#include "config.h"
#include "game_logic.h"
#include "graphics.h"
#include <stdio.h>

int main() {
    // Définir une taille de fenêtre fixe
    const int screenWidth = WINDOW_WIDTH;
    const int screenHeight = WINDOW_HEIGHT;    
    // Initialisation de la fenêtre
    InitWindow(screenWidth, screenHeight, "Snake Game");   
    // Configuration
    SetTargetFPS(60);
    SetConfigFlags(FLAG_MSAA_4X_HINT);  // Anti-aliasing    
    // Chargement des textures
    LoadTextures();
    // Initialisation du jeu
    GameData game;
    InitGame(&game);    
    while (!WindowShouldClose()) {
        // Mise à jour
        UpdateGame(&game);
        // Affichage
        BeginDrawing();
        ClearBackground(BLACK);  // Un seul ClearBackground
        switch (game.current_state) {
            case MENU: 
                DrawMainMenu(&game); 
                break;
            case PLAYING: 
                DrawGameScreen(&game); 
                break;
            case GAME_OVER: 
                DrawGameOverScreen(&game); 
                break;
        }
        EndDrawing();
    }
    UnloadGame(&game);
    CloseWindow();
    return 0;
}