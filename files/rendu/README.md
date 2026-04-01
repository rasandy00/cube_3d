# Cub3D - Documentation Complète

*This project has been created as part of the 42 curriculum by Nyrakoto.*

---

## Table des matières

1. [Description du projet](#description-du-projet)
2. [Architecture du projet](#architecture-du-projet)
3. [Étapes de développement](#étapes-de-développement)
4. [Installation et compilation](#installation-et-compilation)
5. [Utilisation](#utilisation)
6. [Format du fichier .cub](#format-du-fichier-cub)
7. [Structure du code](#structure-du-code)
8. [Algorithme de raycasting](#algorithme-de-raycasting)
9. [Gestion des erreurs](#gestion-des-erreurs)
10. [Gestion mémoire](#gestion-mémoire)
11. [Tests](#tests)
12. [Ressources](#ressources)

---

## Description du projet

Cub3D est un projet graphique de l'école 42 qui consiste à créer un moteur de rendu 3D basé sur la technique du **raycasting**, inspiré du jeu Wolfenstein 3D (1992).

### Objectifs

- Implémenter un moteur de raycasting en C
- Parser un fichier de configuration `.cub`
- Afficher une vue 3D à la première personne
- Gérer les déplacements du joueur
- Respecter la norme 42

### Contraintes techniques

| Contrainte | Description |
|------------|-------------|
| Langage | C uniquement |
| Norme | Norme 42 (fonctions ≤ 25 lignes, 5 variables max) |
| Compilation | `cc` avec `-Wall -Wextra -Werror` |
| Bibliothèques | MiniLibX, libft, math (`-lm`) |
| Mémoire | Zéro leak toléré |

---

## Architecture du projet

### Structure des dossiers

```
files/rendu/
├── cub3D                    # Exécutable
├── Makefile                 # Script de compilation
├── README.md                # Cette documentation
├── main.c                   # Point d'entrée
├── includes/
│   └── cub3d.h              # Header principal (structures, prototypes)
├── src/
│   ├── parsing/             # Module de parsing
│   │   ├── parse_file.c     # Point d'entrée du parsing
│   │   ├── parse_textures.c # Parsing textures + couleurs
│   │   ├── load_textures.c  # Chargement XPM via MLX
│   │   ├── parse_map.c      # Lecture de la map
│   │   ├── validate_map.c   # Validation (flood fill)
│   │   └── free_map.c       # Libération mémoire
│   ├── raycasting/          # Moteur de rendu
│   │   ├── raycast.c        # Boucle principale + DDA
│   │   └── texture.c        # Application des textures
│   ├── player/              # Gestion joueur
│   │   ├── move.c           # Déplacements W/A/S/D
│   │   ├── rotate.c         # Rotations gauche/droite
│   │   └── collision.c      # Détection de collisions
│   ├── render/              # Rendu et événements
│   │   ├── draw.c           # Rendu d'une frame
│   │   ├── hooks.c          # Gestion événements clavier
│   │   └── game_loop.c      # Boucle principale du jeu
│   └── utils/               # Utilitaires
│       ├── errors.c         # Messages d'erreur
│       ├── pixel.c          # Écriture pixels
│       ├── colors.c         # Conversion RGB
│       ├── split_utils.c    # Libération split
│       └── free_game.c      # Libération globale
├── libft/                   # Librairie 42 + get_next_line
├── minilibx-linux/          # Bibliothèque graphique
├── textures/                # Textures XPM (64x64)
│   ├── wall_north.xpm
│   ├── wall_south.xpm
│   ├── wall_west.xpm
│   └── wall_east.xpm
└── maps/                    # Fichiers de test .cub
    ├── simple.cub
    ├── valid.cub
    └── example.cub
```

### Structures de données principales

```c
// Texture (image MLX)
typedef struct s_texture {
    void    *img;       // Pointeur image MLX
    char    *addr;      // Adresse des données pixels
    int     bpp;        // Bits par pixel
    int     line_len;   // Longueur d'une ligne
    int     endian;     // Endianness
    int     width;      // Largeur
    int     height;     // Hauteur
} t_texture;

// Position et direction du joueur
typedef struct s_player {
    double  x;          // Position X
    double  y;          // Position Y
    double  dir_x;      // Direction X (vecteur)
    double  dir_y;      // Direction Y (vecteur)
    double  plane_x;    // Plan caméra X
    double  plane_y;    // Plan caméra Y
} t_player;

// Carte du jeu
typedef struct s_map {
    char    **grid;     // Grille 2D de la map
    int     height;     // Nombre de lignes
    int     width;      // Largeur max
    int     player_x;   // Position X du joueur
    int     player_y;   // Position Y du joueur
    char    player_dir; // Orientation (N/S/E/W)
} t_map;

// Rayon pour le raycasting
typedef struct s_ray {
    double  camera_x;       // Position caméra (-1 à 1)
    double  dir_x, dir_y;   // Direction du rayon
    int     map_x, map_y;   // Position dans la grille
    double  side_dist_x, side_dist_y;  // Distance au prochain côté
    double  delta_dist_x, delta_dist_y; // Distance entre intersections
    double  perp_wall_dist; // Distance perpendiculaire au mur
    int     step_x, step_y; // Direction du pas
    int     side;           // Côté touché (0=X, 1=Y)
    int     hit;            // Mur touché ?
} t_ray;

// Contexte global du jeu
typedef struct t_game {
    void        *mlx;           // Connexion MLX
    void        *win;           // Fenêtre
    void        *img;           // Image principale
    char        *img_addr;      // Adresse image
    t_texture   tex[4];         // 4 textures (N/S/E/W)
    char        *tex_paths[4];  // Chemins des textures
    int         floor_color;    // Couleur du sol
    int         ceiling_color;  // Couleur du plafond
    t_player    player;         // Joueur
    t_map       map;            // Carte
    int         keys[65536];    // État des touches
} t_game;
```

---

## Étapes de développement

### Étape 1 : Analyse du sujet

**Objectif :** Extraire toutes les règles et contraintes du sujet.

**Livrable :** `files/rendu/analyse-sujet.md`

**Règles identifiées :**

| Élément | Format | Contraintes |
|---------|--------|-------------|
| Textures | `NO/SO/WE/EA ./path` | Chemin valide, fichier XPM |
| Couleurs | `F/C R,G,B` | Valeurs 0-255, format strict |
| Map | `0` (vide), `1` (mur), `N/S/E/W` (joueur) | Fermée, 1 joueur |

**Cas d'erreur identifiés (18 total) :**
- Fichier inexistant, mauvaise extension
- Textures manquantes/doublons/invalides
- Couleurs manquantes/doublons/format invalide
- Map non fermée, 0 ou plusieurs joueurs
- Caractères interdits

---

### Étape 2 : Architecture

**Objectif :** Concevoir une architecture modulaire conforme à la norme 42.

**Décisions d'architecture :**

1. **Séparation des modules :**
   - `parsing/` : Lecture et validation du fichier .cub
   - `raycasting/` : Algorithme DDA et rendu
   - `player/` : Déplacements et collisions
   - `render/` : Boucle de jeu et événements
   - `utils/` : Fonctions utilitaires

2. **Makefile :**
   - Règles : `all`, `clean`, `fclean`, `re`
   - Compilation séparée : libft → minilibx → cub3D

3. **Gestion des textures :**
   - Chargement différé après `mlx_init()`
   - Stockage des chemins pendant le parsing
   - Chargement effectif dans `load_textures.c`

---

### Étape 3 : Parsing du fichier .cub

**Objectif :** Implémenter un parser robuste gérant tous les cas d'erreur.

**Ordre de parsing :**

```
1. Vérification extension (.cub)
2. Parsing configuration (6 éléments, ordre flexible)
   ├── NO ./path_to_north_texture
   ├── SO ./path_to_south_texture
   ├── WE ./path_to_west_texture
   ├── EA ./path_to_east_texture
   ├── F R,G,B (couleur sol)
   └── C R,G,B (couleur plafond)
3. Parsing de la map (toujours en dernier)
4. Validation (flood fill)
```

**Fonctions clés :**

| Fonction | Fichier | Rôle |
|----------|---------|------|
| `parse_file()` | parse_file.c | Point d'entrée, orchestration |
| `parse_config()` | parse_textures.c | Parsing des 6 éléments |
| `parse_texture_path()` | parse_textures.c | Extraction chemin texture |
| `parse_color_value()` | parse_textures.c | Parsing couleur RGB |
| `parse_map()` | parse_map.c | Lecture et stockage map |
| `validate_map()` | validate_map.c | Flood fill + validation |
| `load_textures()` | load_textures.c | Chargement XPM après mlx_init |

**Algorithme flood fill :**

```c
static int flood_fill(t_map *map, char **visited, int i, int j)
{
    // Si hors limites → map non fermée
    if (i < 0 || j < 0 || i >= map->height || j >= strlen(map->grid[i]))
        return (1);
    // Si mur ou déjà visité → OK
    if (visited[i][j] == '1' || map->grid[i][j] == '1')
        return (0);
    // Si espace → map non fermée
    if (map->grid[i][j] == ' ')
        return (1);
    visited[i][j] = '1';
    // Récursion dans les 4 directions
    if (flood_fill(map, visited, i + 1, j) != 0) return (1);
    if (flood_fill(map, visited, i - 1, j) != 0) return (1);
    if (flood_fill(map, visited, i, j + 1) != 0) return (1);
    if (flood_fill(map, visited, i, j - 1) != 0) return (1);
    return (0);
}
```

---

### Étape 4 : Moteur de Raycasting

**Objectif :** Implémenter l'algorithme DDA pour le rendu 3D.

**Principe du raycasting :**

Pour chaque colonne de pixels de l'écran (0 à 1920), on lance un rayon depuis le joueur jusqu'à ce qu'il touche un mur. La distance détermine la hauteur de la ligne à dessiner.

**Algorithme DDA (Digital Differential Analysis) :**

```
Pour chaque colonne x:
    1. Calculer la direction du rayon
       ray_dir_x = player.dir_x + player.plane_x * camera_x
       ray_dir_y = player.dir_y + player.plane_y * camera_x
       
    2. Calculer delta_dist (distance entre intersections)
       delta_dist_x = |1 / ray_dir_x|
       delta_dist_y = |1 / ray_dir_y|
       
    3. Initialiser side_dist (distance au premier côté)
       
    4. Boucle DDA jusqu'à toucher un mur:
       - Avancer sur l'axe X ou Y (le plus proche)
       - Mettre à jour side_dist
       - Vérifier si mur touché
       
    5. Calculer la distance perpendiculaire (corrige fish-eye)
       perp_wall_dist = side_dist - delta_dist
       
    6. Calculer la hauteur de ligne:
       line_height = SCREEN_HEIGHT / perp_wall_dist
       
    7. Dessiner la colonne avec texture
```

**Correction du fish-eye :**

Le fish-eye effect se produit quand on utilise la distance euclidienne directe. On utilise la distance perpendiculaire pour corriger :

```c
if (ray->side == 0)
    ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
else
    ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
```

**Application des textures :**

1. Calculer `wall_x` (position exacte sur le mur)
2. Déterminer la texture selon l'orientation :
   - `side == 0 && step_x > 0` → EST
   - `side == 0 && step_x < 0` → OUEST
   - `side == 1 && step_y > 0` → SUD
   - `side == 1 && step_y < 0` → NORD
3. Calculer `tex_x` (coordonnée X dans la texture)
4. Dessiner la colonne pixel par pixel

---

### Étape 5 : Player & Inputs

**Objectif :** Implémenter les déplacements et rotations du joueur.

**Contrôles :**

| Touche | Action | Code |
|--------|--------|------|
| W | Avancer | 119 |
| S | Reculer | 115 |
| A | Strafe gauche | 97 |
| D | Strafe droite | 100 |
| ← | Rotation gauche | 65361 |
| → | Rotation droite | 65363 |
| ESC | Quitter | 65307 |

**Système d'événements :**

```c
// Tableau d'état des touches
int keys[65536];

// Appui d'une touche
int key_press(int keycode, t_game *game)
{
    if (keycode == KEY_ESC)
        close_window(game);
    game->keys[keycode] = 1;
    return (0);
}

// Relâchement d'une touche
int key_release(int keycode, t_game *game)
{
    game->keys[keycode] = 0;
    return (0);
}
```

**Mouvements :**

```c
// Avancer
new_x = player.x + player.dir_x * MOVE_SPEED;
new_y = player.y + player.dir_y * MOVE_SPEED;

// Strafe (perpendiculaire à la direction)
new_x = player.x + player.plane_x * MOVE_SPEED;
new_y = player.y + player.plane_y * MOVE_SPEED;

// Rotation (rotation du vecteur direction ET du plan)
old_dir_x = dir_x;
dir_x = dir_x * cos(rot_speed) - dir_y * sin(rot_speed);
dir_y = old_dir_x * sin(rot_speed) + dir_y * cos(rot_speed);
```

**Gestion des collisions :**

Vérification avec une marge de sécurité (0.1) pour éviter de traverser les murs :

```c
int check_collision(t_game *game, double x, double y)
{
    // Vérifier les 4 coins autour de la position
    if (game->map.grid[(int)(y + 0.1)][(int)(x + 0.1)] == '1') return (1);
    if (game->map.grid[(int)(y - 0.1)][(int)(x - 0.1)] == '1') return (1);
    if (game->map.grid[(int)(y + 0.1)][(int)(x - 0.1)] == '1') return (1);
    if (game->map.grid[(int)(y - 0.1)][(int)(x + 0.1)] == '1') return (1);
    return (0);
}
```

---

### Étape 6 : Nettoyage & Tests

**Objectif :** Finaliser le projet, vérifier les leaks, valider.

**Libération mémoire :**

```c
void free_game(t_game *game)
{
    int i;
    
    // Libérer les 4 textures
    i = 0;
    while (i < 4)
    {
        if (game->tex[i].img)
            mlx_destroy_image(game->mlx, game->tex[i].img);
        if (game->tex_paths[i])
            free(game->tex_paths[i]);
        i++;
    }
    // Libérer l'image principale
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    // Détruire la fenêtre
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    // Libérer la map
    free_map(&game->map);
    // Détruire le display MLX (important pour les leaks)
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
}
```

**Note sur les "still reachable" :**

Les `still reachable` restants dans valgrind proviennent des bibliothèques X11/XCB (non libérées par MiniLibX). Ce n'est pas un leak de notre code.

---

## Installation et compilation

### Prérequis

- GCC/Clang
- Make
- X11 (Linux)
- Valgrind (pour les tests)

### Compilation

```bash
cd files/rendu

# Compiler tout
make

# Nettoyer les objets
make clean

# Nettoyer tout (objets + exécutable)
make fclean

# Recompiler from scratch
make re
```

### Exécution

```bash
./cub3D maps/simple.cub
```

---

## Utilisation

### Contrôles en jeu

| Touche | Action |
|--------|--------|
| `W` | Avancer |
| `S` | Reculer |
| `A` | Strafe (déplacement latéral) gauche |
| `D` | Strafe droite |
| `←` (flèche gauche) | Rotation gauche |
| `→` (flèche droite) | Rotation droite |
| `ESC` | Quitter le programme |
| Croix rouge | Quitter le programme |

### Résolution

- Largeur : 1920 pixels
- Hauteur : 1080 pixels

Modifiable dans `includes/cub3d.h` :
```c
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
```

---

## Format du fichier .cub

### Structure

```
[Textures]     # Ordre flexible
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm

[Couleurs]     # Ordre flexible
F 220,100,0    # Sol (R,G,B)
C 225,30,0     # Plafond (R,G,B)

[Lignes vides autorisées]

[Map]          # Toujours en dernier
1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
1000000000110000011101111
1111011111111101110000001
1100000011010101110000001
1000000000000000110000001
110000011101010111110111N1
1111111111111111111111111
```

### Caractères de la map

| Caractère | Signification |
|-----------|---------------|
| `0` | Sol (espace vide) |
| `1` | Mur |
| `N` | Joueur orienté Nord |
| `S` | Joueur orienté Sud |
| `E` | Joueur orienté Est |
| `W` | Joueur orienté Ouest |
| ` ` (espace) | Partie valide de la map |

### Règles

1. **Textures** : 4 obligatoires (NO, SO, WE, EA)
2. **Couleurs** : 2 obligatoires (F, C), format `R,G,B` (0-255)
3. **Map** : Doit être fermée (entourée de murs `1`)
4. **Joueur** : Exactement 1 (N, S, E ou W)
5. **Lignes vides** : Interdites dans la map, autorisées ailleurs

---

## Structure du code

### Point d'entrée (main.c)

```c
int main(int argc, char **argv)
{
    t_game game;
    
    // 1. Vérifier les arguments
    if (argc != 2)
        return (print_error("Usage: ./cub3D <map.cub>"), 1);
    
    // 2. Initialiser et parser
    ft_memset(&game, 0, sizeof(t_game));
    game.floor_color = -1;
    game.ceiling_color = -1;
    if (parse_file(argv[1], &game) != 0)
        return (free_game(&game), 1);
    
    // 3. Initialiser MLX
    game.mlx = mlx_init();
    if (!game.mlx)
        return (print_error("MLX init failed"), free_game(&game), 1);
    
    // 4. Charger les textures
    if (load_textures(&game) != 0)
        return (free_game(&game), 1);
    
    // 5. Créer la fenêtre
    game.win = mlx_new_window(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3D");
    game.img = mlx_new_image(game.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game.img_addr = mlx_get_data_addr(game.img, ...);
    
    // 6. Initialiser le joueur
    init_game(&game);
    
    // 7. Enregistrer les hooks
    mlx_hook(game.win, 2, 1L << 0, key_press, &game);
    mlx_hook(game.win, 3, 1L << 1, key_release, &game);
    mlx_hook(game.win, 17, 0, close_window, &game);
    mlx_loop_hook(game.mlx, game_loop, &game);
    
    // 8. Lancer la boucle principale
    mlx_loop(game.mlx);
    
    return (0);
}
```

### Boucle de jeu (game_loop)

```c
int game_loop(t_game *game)
{
    // 1. Rotation si touches pressées
    if (game->keys[KEY_LEFT])
        rotate_player(game, -ROT_SPEED);
    if (game->keys[KEY_RIGHT])
        rotate_player(game, ROT_SPEED);
    
    // 2. Déplacements
    move_player(game);
    
    // 3. Rendu
    render_frame(game);
    
    return (0);
}
```

### Rendu d'une frame (render_frame)

```c
void render_frame(t_game *game)
{
    // Lancer le raycasting pour toutes les colonnes
    raycast(game);
    
    // Afficher l'image dans la fenêtre
    mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
}
```

---

## Algorithme de raycasting

### Vue d'ensemble

```
         Écran
    +--------------+
    |   |    |     |
    |   |    |     |  ← Lignes verticales (colonnes)
    |   |    |     |    Hauteur = f(distance)
    +--------------+
         ↓
      Joueur
         ↓
       Rayons
         ↓
    +--------------+
    |  Map 2D      |
    |  1111111111  |
    |  1000000001  |
    |  1000N00001  |  ← N = joueur
    |  1000000001  |
    |  1111111111  |
    +--------------+
```

### Formules clés

**Position caméra sur l'écran :**
```c
camera_x = 2 * x / SCREEN_WIDTH - 1;  // -1 (gauche) à +1 (droite)
```

**Direction du rayon :**
```c
ray_dir_x = player.dir_x + player.plane_x * camera_x;
ray_dir_y = player.dir_y + player.plane_y * camera_x;
```

**Delta distance :**
```c
delta_dist_x = fabs(1 / ray_dir_x);  // Distance entre 2 lignes verticales
delta_dist_y = fabs(1 / ray_dir_y);  // Distance entre 2 lignes horizontales
```

**Distance perpendiculaire :**
```c
if (side == 0)
    perp_wall_dist = (map_x - player.x + (1 - step_x) / 2) / ray_dir_x;
else
    perp_wall_dist = (map_y - player.y + (1 - step_y) / 2) / ray_dir_y;
```

**Hauteur de ligne :**
```c
line_height = (int)(SCREEN_HEIGHT / perp_wall_dist);
draw_start = -line_height / 2 + SCREEN_HEIGHT / 2;
draw_end = line_height / 2 + SCREEN_HEIGHT / 2;
```

---

## Gestion des erreurs

### Format de sortie

```
Error
<message explicite>
```

### Erreurs gérées

| Erreur | Message |
|--------|---------|
| Mauvais arguments | `Usage: ./cub3D <map.cub>` |
| Extension invalide | `Invalid file extension` |
| Fichier introuvable | `Cannot open file` |
| Configuration incomplète | `Missing configuration` |
| Texture dupliquée | `Duplicate texture` |
| Texture invalide | `Invalid texture` ou `Failed to load texture` |
| Couleur invalide | `Invalid color format` |
| Couleur hors plage | `Color out of range` |
| Couleur dupliquée | `Duplicate floor/ceiling color` |
| Map vide | `Empty map` |
| Pas de joueur | `No player` |
| Plusieurs joueurs | `Multiple players` |
| Caractère interdit | `Invalid character` |
| Map non fermée | `Map not closed` |

### Code de sortie

- Succès : `0`
- Erreur : `1`

---

## Gestion mémoire

### Fonctions de libération

```c
// Libérer la map
void free_map(t_map *map)
{
    int i;
    
    if (!map->grid) return;
    i = 0;
    while (map->grid[i])
    {
        free(map->grid[i]);
        i++;
    }
    free(map->grid);
    map->grid = NULL;
}

// Libérer tout le jeu
void free_game(t_game *game)
{
    int i;
    
    // Textures
    i = 0;
    while (i < 4)
    {
        if (game->tex[i].img)
            mlx_destroy_image(game->mlx, game->tex[i].img);
        if (game->tex_paths[i])
            free(game->tex_paths[i]);
        i++;
    }
    // Image principale
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    // Fenêtre
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    // Map
    free_map(&game->map);
    // Display MLX
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
}
```

### Test valgrind

```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/simple.cub
```

**Résultat attendu :**
- `definitely lost: 0 bytes`
- `indirectly lost: 0 bytes`
- `possibly lost: 0 bytes`
- `still reachable`: Proviennent de X11/XCB (normal)

---

## Tests

### Maps de test incluses

| Fichier | Description |
|---------|-------------|
| `maps/simple.cub` | Map 10x10, 1 joueur |
| `maps/valid.cub` | Map 16x9, plus grande |
| `maps/example.cub` | Map complexe du sujet |

### Commandes de test

```bash
# Test basique
./cub3D maps/simple.cub

# Test avec valgrind
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/simple.cub

# Test avec map invalide (pour tester les erreurs)
./cub3D maps/invalid.cub
```

### Créer des maps de test d'erreur

```bash
# Map sans joueur
echo "NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 0,0,0
C 255,255,255
111111
100001
111111" > maps/error_no_player.cub

# Map non fermée
echo "NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 0,0,0
C 255,255,255
11111
10001
100N1
11111" > maps/error_open_map.cub
```

---

## Ressources

### Tutoriels Raycasting

- [Lodev Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - Référence principale
- [Permadi's Raycasting](https://www.permadi.com/tutorial/raycast/rayc1.html) - Théorie détaillée
- [Wolfenstein 3D Wikipedia](https://en.wikipedia.org/wiki/Wolfenstein_3D)

### Documentation 42

- [Norme 42](https://github.com/42School/norminette)
- [Sujet Cub3D](./files/en.subject.pdf)

### MiniLibX

- [Documentation MLX](https://hsmarket.net/lib/mlx_manual.pdf)
- [GitHub MLX Linux](https://github.com/42Paris/minilibx-linux)

### Outils de développement

- [Norminette](https://github.com/42School/norminette) - Vérification norme
- [Valgrind](https://valgrind.org/) - Détection de leaks

---

## Auteur

**Nyrakoto** - Étudiant 42 Antananarivo

Projet réalisé dans le cadre du Common Core 42, Milestone 4.

---

## Historique des versions

| Version | Date | Description |
|---------|------|-------------|
| 1.0 | 2026-03-31 | Version initiale complète |

---

*Ce projet a été généré avec l'aide de la compétence bmad-42-cub3d.*
