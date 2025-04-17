#include "snake.h"
#include "map.h"
#include <stdlib.h>
#include <stdbool.h>

void InitSnake(Snake* snake, Vector2 start_pos) {
    
    // Créer le premier nœud (tête)
    snake->head = (SnakeNode*)malloc(sizeof(SnakeNode));
    
    // Position initiale
    snake->head->position = start_pos; // la position de la tête est celle de départ 
    snake->head->next = NULL; // Il n'y a pas de nœud suivant pour le moment
    snake->head->prev = NULL; // Il n'y a pas de nœud précédent pour le moment
    snake->tail = snake->head; // La queue est la même que la tête au début
    
    // Ajouter un second segment
    GrowSnake(snake);
    snake->direction = (Vector2){1, 0};  // Départ vers la droite
    snake->speed = 0.1;  // Vitesse par défaut
}

void ChangeSnakeDirection(Snake* snake, Vector2 new_dir) {
    // Vérifier que la direction n'est pas opposée à la direction actuelle (Le serpent ne peut pas faire demi-tour instantanément)
    if ((snake->direction.x == -new_dir.x && snake->direction.y == 0 && new_dir.y == 0) || (snake->direction.y == -new_dir.y && snake->direction.x == 0 && new_dir.x == 0)) return; //On ignore la di
    // Vérifier que la nouvelle direction n'est pas nulle
    if ((new_dir.x == 0 && new_dir.y == 0) || (new_dir.x != 0 && new_dir.y != 0)) return;  // Direction invalide (nulle ou diagonale)
    snake->direction = new_dir; // Mettre à jour la direction du serpent
}

void MoveSnake(Snake* snake) {
    if (snake->head == NULL) return;
    // Créer un nouveau nœud pour la tête
    SnakeNode* new_head = (SnakeNode*)malloc(sizeof(SnakeNode));
    // Calculer la nouvelle position
    new_head->position.x = snake->head->position.x + snake->direction.x;
    new_head->position.y = snake->head->position.y + snake->direction.y;
    new_head->next = snake->head; // Le nouveau nœud suivant est l'ancienne tête
    new_head->prev = NULL; // Pas d'un nœud précédent pour le nouveau nœud
    if (snake->head) snake->head->prev = new_head; // Mettre à jour l'ancienne tête pour qu'elle pointe vers le nouveau nœud
    snake->head = new_head; // Mettre à jour la tête du serpent
    if (snake->tail == NULL) snake->tail = snake->head; // Si un seul nœud existe, la queue du serpent est de même la tête 
    // Supprimer la queue si on ne grandit pas
    SnakeNode* current = snake->head;
    int count = 1; // Compter le nombre total des segments pour le serpent
    // Compter les nœuds et trouver l'avant-dernier
    while (current->next != NULL) {
        current = current->next;
        count++;
    }
    snake->length = count; // Mettre à jour la longueur du serpent
    // Dans le cas d'avoir plus d'un noeud dans le serpent, on supprime la queue pour assurer que la queue ne reste pas dans la même position de départ
    if (count > 1) {
        current = snake->head;
        while (current->next != NULL && current->next->next != NULL) {
            current = current->next; 
        }
        free(snake->tail);
        snake->tail = current;
        snake->tail->next = NULL;
    }
}

void GrowSnake(Snake* snake) {
    if (snake->head == NULL) return;
    // Créer un nouveau nœud à la position de la queue
    SnakeNode* new_node = (SnakeNode*)malloc(sizeof(SnakeNode));
    new_node->position = snake->tail->position; // Positionner le nouveau noeud à la queue
    new_node->next = NULL; // Le nouveau noeud d'après n'a pas de suivant
    snake->tail->next = new_node; // Mettre à jour le suivant de la queue
    snake->tail = new_node; // Mettre à jour la queue du serpent
}
bool CheckSelfCollision(Snake* snake) {
    if (snake->head == NULL || snake->head->next == NULL) return false; // Le serpent doit avoir au moins 2 segments pour se heurter à lui-même
    SnakeNode* current = snake->head->next->next; //Commence à vérifier les collisions à partir du troisième segment
    while (current != NULL) {
        //On vérifie si la tête du serpent est à la même position qu'un autre segment, alors une collision est détectée 
        if (Vector2Equals(snake->head->position, current->position)==1) {
            return true;
        }
        current = current->next; //On passe au segment suivant
    }
    return false; //Si on a pas retourner vrai à une collision, alors pas de collision détectée
}
void FreeSnake(Snake* snake) {
    SnakeNode* current = snake->head; // Commencer par la tête
    SnakeNode* next; // Mettre un pointeur pour le nœud suivant
    while (current != NULL) { // Tant qu'il y a des nœuds à libérer
        // Libérer le nœud actuel (la tête dans le cas pour la première itération) et passer au suivant
        next = current->next; 
        free(current);
        current = next;
    }
    snake->head = NULL; // Réinitialiser la tête 
    snake->tail = NULL; // Réinitialiser la queue
}
