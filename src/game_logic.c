#include "game_logic.h"
#include "snake.h"
#include "map.h"
#include <stddef.h>
#include <stdio.h>
#include <math.h>

void InitGame(GameData* game) { // Initialiser le jeu
    InitAudioDevice(); // Initialiser le système audio
    // Charger les assets
    game->eat_sound = LoadSound("assets/audio/food.mp3"); // Charger le son de la nourriture
    game->crash_sound = LoadSound("assets/audio/gameover.mp3"); // Charger le son de la collision
    game->background_music = LoadMusicStream("assets/audio/music.mp3"); // Charger la musique de fond
    // Initialiser les valeurs
    game->current_state = MENU; // État du jeu initial est dans le menu 
    game->score = 0; // Le score initial est 0
    game->grid_enabled = true; // Activer la grille
    game->sound_enabled = true; // Le son est activé par défaut 
    game->move_timer = 0; // Initialiser le timer de mouvement à 0
    // Initialiser le serpent à NULL pour éviter des accès mémoire invalides
    game->snake.head = NULL; 
    game->snake.tail = NULL;    
    SetMusicVolume(game->background_music, 0.3); // Régler le volume de la musique de fond
    PlayMusicStream(game->background_music); // Jouer la musique de fond
}

void ResetGame(GameData* game) {
    // Libérer l'ancien serpent s'il existe
    if (game->snake.head != NULL) FreeSnake(&game->snake);
    // Initialiser le nouveau serpent pour la deuxième fois
    InitSnake(&game->snake, (Vector2){2, GRID_SIZE/2}); // Position initiale du serpent
    game->snake.speed = 0.1; // Initialiser la Vitesse par défaut
    InitMap(&game->map, false); // Initialiser la carte sans la grille
    if (game->snake.head != NULL) SpawnFruit(&game->map, &game->snake); // Générer un fruit seulement si le serpent est correctement initialisé
    game->score = 0; // Réinitialiser le score à 0
}

void UpdateGame(GameData* game ) {
    UpdateMusicStream(game->background_music); 
    if (game->current_state != PLAYING) return;
    //static float move_timer; // Timer variable pour le mouvement du serpent
    float frame_time = GetFrameTime(); // Temps écoulé depuis la dernière image
    game->move_timer += frame_time; // Incrémenter le timer de mouvement
    // Gérer les touches fléchées pour le mouvement
    if (IsKeyDown(KEY_UP) && game->snake.direction.y != 1) ChangeSnakeDirection(&game->snake, (Vector2){0, -1}); 
    else if (IsKeyDown(KEY_DOWN) && game->snake.direction.y != -1) ChangeSnakeDirection(&game->snake, (Vector2){0, 1});
    else if (IsKeyDown(KEY_LEFT) && game->snake.direction.x != 1) ChangeSnakeDirection(&game->snake, (Vector2){-1, 0});
    else if (IsKeyDown(KEY_RIGHT) && game->snake.direction.x != -1) ChangeSnakeDirection(&game->snake, (Vector2){1, 0});
    if (game->move_timer >= game->snake.speed) {// Vérifier si le serpent doit se déplacer
        game->move_timer = 0; // Réinitialiser le timer
        MoveSnake(&game->snake); // Déplacer le serpent d'abord
        if (CheckWallCollision(&game->map, game->snake.head->position) || CheckSelfCollision(&game->snake)) // Vérifier les collisions après le déplacement
        {
            if (game->sound_enabled) PlaySound(game->crash_sound);
            game->current_state = GAME_OVER;
        }
        // Vérifier la collision avec le fruit
        if (Vector2Equals(game->snake.head->position, game->map.fruit.position)) {
            if (game->sound_enabled) PlaySound(game->eat_sound); // Jouer le son de la nourriture
            GrowSnake(&game->snake); // Ajouter un segment au serpent
            // Augmenter le score en fonction du type de fruit
            if (game->map.fruit.type == FRUIT_NORMAL) {
                game->score += 10; // Augmenter le score de 10 points pour un fruit normal
                game->snake.speed = game->snake.speed * 0.95; // Augmenter la vitesse de 5%
            } 
            SpawnFruit(&game->map, &game->snake); //Générer un autre fruit dans une position aléatoire
        }
    }
}

void UnloadGame(GameData* game) // Libérer les ressources du jeu
{
    UnloadSound(game->eat_sound);
    UnloadSound(game->crash_sound);
    UnloadMusicStream(game->background_music);
    FreeSnake(&game->snake);
    CloseAudioDevice();
}