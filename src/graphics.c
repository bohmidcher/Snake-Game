#include "graphics.h"
#include "config.h"
#include "game_logic.h"
#include "snake.h"
#include "map.h"
#include <math.h>
#include <stdio.h>

    // Définition des textures
    Texture2D apple;


    void LoadTextures(void) {
        // Utiliser des rectangles colorés par défaut
        Image default_image = GenImageColor(CELL_SIZE, CELL_SIZE, COLOR_BACKGROUND);
        Texture2D default_texture = LoadTextureFromImage(default_image);
        UnloadImage(default_image);
        Image snake_img = GenImageColor(CELL_SIZE, CELL_SIZE, COLOR_SNAKE); 
        Texture2D snake_texture = LoadTextureFromImage(snake_img);
        UnloadImage(snake_img);        
        // Charger la texture de la pomme
        Image apple_img = GenImageColor(CELL_SIZE, CELL_SIZE, COLOR_FRUIT);
        apple = LoadTextureFromImage(apple_img);
        UnloadImage(apple_img);
        
    }

    void DrawCenteredText(const char* text, int y, int fontSize, Color color) {
        int width = MeasureText(text, fontSize);
        DrawText(text, GetScreenWidth()/2 - width/2, y, fontSize, color);
    }

    void DrawMainMenu(GameData* game) {
        Color bgColor = (Color){173, 204, 96, 255};
        ClearBackground(bgColor);
        
        int centerX = GetScreenWidth()/2;
        int centerY = GetScreenHeight()/2;
        
        // Titre
        const char* title = "SNAKE GAME";
        int titleSize = 60;
        Color titleColor = DARKBROWN;
        DrawCenteredText(title, centerY - 100, titleSize, titleColor);
        //DrawText(title, centerX - MeasureText(title, titleSize)/2, centerY - 100, titleSize, titleColor);
        // Bouton JOUER
        Rectangle playBtn = {centerX - 100, centerY + 5, 200, 50};
        Color btnColor = COLOR_SNAKE;
        DrawRectangleRec(playBtn, btnColor);
        const char* playText = "PLAY";
        int btnTextSize = 30;
        DrawCenteredText(playText, centerY + 15, btnTextSize, WHITE);
        //DrawText(playText, centerX - MeasureText(playText, btnTextSize)/2, centerY + 15, btnTextSize, WHITE);
        // Vérifier le clic
        if (CheckCollisionPointRec(GetMousePosition(), playBtn) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Réinitialiser le jeu avant de passer à l'état PLAYING
            ResetGame(game);
            game->current_state = PLAYING;
        }
    }
    void DrawGameScreen(GameData* game) {
        // Supprimer BeginDrawing()/EndDrawing() de cette fonction
        // Fond vert clair
        Color bgColor = COLOR_BACKGROUND;
        ClearBackground(bgColor);
        // Quadrillage
        Color gridColor = COLOR_GRID;
        for (int x = 0; x < GetScreenWidth(); x += CELL_SIZE) {
            for (int y = 0; y < GetScreenHeight(); y += CELL_SIZE) {
                if ((x/CELL_SIZE + y/CELL_SIZE) % 2 == 0) {
                    DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, gridColor);
                }
            }
        }
        // Serpent
        Color snakeColor = COLOR_SNAKE;
        SnakeNode* current = game->snake.head;
        bool is_head = true;
        while (current != NULL) {
            float x = current->position.x * CELL_SIZE;
            float y = current->position.y * CELL_SIZE;
            // Dessiner le serpent segment par segment
            DrawRectangle(x, y, CELL_SIZE, CELL_SIZE, snakeColor);
            // Si c'est la tête, ajouter les yeux
            if (is_head) {
                Color eyeColor = WHITE;
                float eyeSize = CELL_SIZE/8;
                float eyeOffset = CELL_SIZE/5;
                // Position des yeux selon la direction
                if (game->snake.direction.x > 0) { // Droite
                    DrawCircle(x + 3*CELL_SIZE/4, y + CELL_SIZE/3, eyeSize, eyeColor);
                    DrawCircle(x + 3*CELL_SIZE/4, y + 2*CELL_SIZE/3, eyeSize, eyeColor);
                } else if (game->snake.direction.x < 0) { // Gauche
                    DrawCircle(x + CELL_SIZE/4, y + CELL_SIZE/3, eyeSize, eyeColor);
                    DrawCircle(x + CELL_SIZE/4, y + 2*CELL_SIZE/3, eyeSize, eyeColor);
                } else if (game->snake.direction.y < 0) { // Haut
                    DrawCircle(x + CELL_SIZE/3, y + CELL_SIZE/4, eyeSize, eyeColor);
                    DrawCircle(x + 2*CELL_SIZE/3, y + CELL_SIZE/4, eyeSize, eyeColor);
                } else { // Bas
                    DrawCircle(x + CELL_SIZE/3, y + 3*CELL_SIZE/4, eyeSize, eyeColor);
                    DrawCircle(x + 2*CELL_SIZE/3, y + 3*CELL_SIZE/4, eyeSize, eyeColor);
                }
                is_head = false;
            }
            current = current->next;
        }
        // Fruit
        if (game->map.fruit.active) {
            Color fruitColor = COLOR_FRUIT;
            float x = game->map.fruit.position.x * CELL_SIZE + CELL_SIZE/2;
            float y = game->map.fruit.position.y * CELL_SIZE + CELL_SIZE/2;
            DrawCircle(x, y, CELL_SIZE/3, fruitColor);
        }
        // Barre de score
        Color barColor = COLOR_UI_BAR;
        DrawRectangle(0, 0, GetScreenWidth(), 50, barColor);
        
        // Score (en haut à gauche)
        char scoreText[4];
        sprintf(scoreText, "Score: %d", game->score);
        int fontSize = 25;
        DrawText(scoreText, 20, 10, fontSize, WHITE);
        
        // Texte "Mute" (en haut à droite)
        const char* muteText;
        if (game->sound_enabled) {
            muteText = "Mute";
        } else {
            muteText = "Unmute";
        }
        DrawText(muteText, GetScreenWidth() - MeasureText(muteText, fontSize) - 20, 10, fontSize, WHITE);
        // Zone cliquable pour le bouton mute
        Rectangle muteBtn = {
            GetScreenWidth() - MeasureText(muteText, fontSize) - 20,
            10,
            MeasureText(muteText, fontSize),
            fontSize
        };
        
        // Vérifier le clic sur le bouton mute
        bool mute_clicked = CheckCollisionPointRec(GetMousePosition(), muteBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
        if (mute_clicked) {
            game->sound_enabled = !game->sound_enabled;
            // Ajuster le volume de la musique
            if (game->sound_enabled) {
                SetMusicVolume(game->background_music, 0.5f);
            } else {
                SetMusicVolume(game->background_music, 0.0f);
            }
        }
    }
    void DrawGameOverScreen(GameData* game) {
        // Fond noir
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 255});
        
        int centerX = GetScreenWidth()/2;
        int centerY = GetScreenHeight()/2;
        
        // Game Over
        const char* gameOverText = "GAME OVER";
        int gameOverSize = 60;
        DrawCenteredText(gameOverText, centerY - 100, gameOverSize, WHITE);
        // Score
        char scoreText[32];
        sprintf(scoreText, "Score: %d", game->score);
        int scoreSize = 30;
        DrawCenteredText(scoreText, centerY - 20, scoreSize, WHITE);
        // Bouton Rejouer
        Rectangle restartBtn = {centerX - 100, centerY + 50, 200, 50};
        Color btnColor = (Color){82, 121, 214, 255};
        DrawRectangleRec(restartBtn, btnColor);
        const char* restartText = "RESTART";
        int btnTextSize = 30;
        DrawCenteredText(restartText, centerY + 60, btnTextSize, WHITE);
        // Vérifier le clic sur le bouton rejouer
        if (CheckCollisionPointRec(GetMousePosition(), restartBtn) &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            // Réinitialiser le jeu et passer à l'état PLAYING
            ResetGame(game);
            game->current_state = PLAYING;
        }
    }