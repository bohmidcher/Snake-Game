# Projet Snake Game - Guide d'Utilisation

## Introduction
Bienvenue dans Snake Game, un jeu classique où vous contrôlez un serpent qui doit manger des fruits pour grandir tout en évitant les collisions avec les murs et lui-même.

## Configuration Requise
- Système d'exploitation: Windows
- Bibliothèque: Raylib (incluse dans le projet)

## Installation
1. Clonez ou téléchargez ce dépôt sur votre ordinateur
2. Assurez-vous que tous les fichiers sont dans la structure de dossiers appropriée

## Compilation
Utilisez la commande suivante pour compiler le jeu:
 gcc -o bin/snake_game.exe src/main.c src/graphics.c src/game_logic.c src/map.c src/snake.c -Iinclude -Iraylib -Llib -lraylib -lopengl32 -lgdi32 -lwinmm

## Exécution
Pour lancer le jeu après compilation:
./bin/snake_game.exe


## Contrôles du Jeu
- **Flèches directionnelles**: Contrôler la direction du serpent
  - Flèche Haut: Déplacer vers le haut
  - Flèche Bas: Déplacer vers le bas
  - Flèche Gauche: Déplacer vers la gauche
  - Flèche Droite: Déplacer vers la droite
  - Échap: Quitter le jeu

## Fonctionnalités
- Système de score: Gagnez 10 points pour chaque fruit mangé
- Augmentation de la vitesse: Le serpent accélère progressivement à mesure que vous mangez des fruits
- Effets sonores: Sons pour manger des fruits et collision
- Musique de fond

## Structure du Projet
- assets/: Contient les fichiers audio et autres ressources
- include/: Fichiers d'en-tête (.h)
- src/: Fichiers source (.c)
- lib/: Bibliothèques raylib nécessaires
- bin/: Fichiers binaires compilés

## Dépannage
Si vous rencontrez des problèmes lors de la compilation ou de l'exécution:
    1. Vérifiez que tous les fichiers sont présents dans la structure de dossiers
    2. Assurez-vous que les bibliothèques Raylib sont correctement installées
    3. Vérifiez les chemins d'accès dans les commandes de compilation

## Amusez-vous bien !
Profitez du jeu et essayez d'obtenir le meilleur score possible !