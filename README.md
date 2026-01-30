# 42Cube3D (cub3D)

Projet "cub3D" — rendu 3D simple (raycasting) réalisé dans le cadre du cursus 42.

## Description

Ce projet implémente un moteur de rendu 3D minimaliste utilisant la technique du raycasting (à la manière de Wolfenstein 3D). Il charge des fichiers de carte `.cub`, parse la configuration (textures, couleurs, résolution) et affiche une vue 3D avec gestion des déplacements et collisions.

## Fonctionnalités

- Lecture et validation de fichiers `.cub` (configuration + carte)
- Moteur de raycasting pour rendu 3D en temps réel
- Déplacements et rotations du joueur
- Gestion basique des textures et couleurs
- Plusieurs cartes d'exemple et tests fournis

## Prérequis

- macOS avec outils de développement (Xcode Command Line Tools)
- Make
- Bibliothèque MiniLibX (incluse dans `lib/minilibx` et `lib/minilibx-macos`)

## Installation

1. Ouvrir un terminal dans la racine du projet.
2. S'assurer d'avoir les outils de compilation : `xcode-select --install` si nécessaire.
3. Lancer la compilation :

```sh
make
```

Le Makefile génère l'exécutable principal (typiquement `cub3d`).

## Exécution

Lancer le programme en fournissant une carte `.cub` :

```sh
./cub3d maps/valid/map1.cub
```

Remplacez le chemin par n'importe quel fichier `.cub` des dossiers `maps/valid` ou `maps/error` pour tester la validation.

## Commandes / Contrôles

- Déplacement avant/arrière : `W` / `S`
- Déplacement latéral : `A` / `D`
- Rotation : flèches gauche / droite
- Quitter : `ESC`

(Ces contrôles peuvent varier légèrement selon la configuration ; vérifier `mlx_hook.c` et `src/` si nécessaire.)

## Structure du dépôt (aperçu)

- `src/` : sources principales (boucle, gestion d'image, math, utilitaires)
- `parsing/` : parseurs et validateurs de carte
- `raycasting/` : code de rendu raycasting
- `lib/minilibx` et `lib/minilibx-macos` : MiniLibX (X11 / macOS)
- `maps/valid` : exemples de cartes valides
- `maps/error` : cartes conçues pour tester les erreurs de parsing
- `include/` : en-têtes (notamment `cub3d.h`)
- `Makefile` : règle de compilation

## Format du fichier `.cub`

Le fichier `.cub` contient :
- la résolution
- chemins vers les textures
- couleurs du plafond et du sol
- la carte (grille) où `1` = mur, `0` = espace, et `N/S/E/W` indique la position/orientation du joueur.

Utilisez les fichiers dans `maps/valid` comme exemples.

## Dépannage

- Erreur lors de la compilation : vérifier que les headers et la MiniLibX sont disponibles et compatibles avec macOS.
- Problèmes d'affichage / textures : s'assurer que les chemins des textures dans le `.cub` sont corrects et que les fichiers existent.
- Crash au lancement : lancer avec une carte valide (voir `maps/valid`) pour isoler un problème de parsing.

## Tests fournis

Des cartes de tests sont fournies dans `maps/error` pour vérifier la robustesse du parser et `maps/valid` pour des cas fonctionnels. Utilisez-les pour diagnostiquer et reproduire des comportements.

## Contributions

Ce dépôt est destiné à un usage pédagogique (projet 42). Si vous souhaitez proposer des améliorations :
- Ouvrez une branche et créez une pull request détaillant les changements.
- Documentez toute modification de l'API ou des formats de fichier.

## Auteurs & Licence

- Auteur principal : Maxandre Severin et Adam Flandin
- Licence : voir les fichiers de licence inclus dans `lib/minilibx` si vous réutilisez la MiniLibX.
