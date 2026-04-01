# Analyse du Sujet Cub3D

## 1. Règles du fichier .cub

### 1.1 Éléments obligatoires

| Élément | Identifiant | Format | Contraintes |
|---------|-------------|--------|-------------|
| Texture Nord | `NO` | `NO ./path_to_texture` | Chemin valide, fichier XPM/PNG lisible |
| Texture Sud | `SO` | `SO ./path_to_texture` | Chemin valide, fichier XPM/PNG lisible |
| Texture Ouest | `WE` | `WE ./path_to_texture` | Chemin valide, fichier XPM/PNG lisible |
| Texture Est | `EA` | `EA ./path_to_texture` | Chemin valide, fichier XPM/PNG lisible |
| Couleur sol | `F` | `F R,G,B` | R,G,B ∈ [0,255], format strict |
| Couleur plafond | `C` | `C R,G,B` | R,G,B ∈ [0,255], format strict |

### 1.2 Règles de positionnement

- **Ordre flexible** : Les éléments (textures, couleurs) peuvent apparaître dans n'importe quel ordre
- **Map en dernier** : La map DOIT être le dernier élément du fichier
- **Séparation** : Les éléments peuvent être séparés par une ou plusieurs lignes vides (sauf dans la map)
- **Espaces** : Chaque type d'information peut être séparé par un ou plusieurs espaces (sauf dans la map)

### 1.3 Règles de la map

| Caractère | Signification |
|-----------|---------------|
| `0` | Espace vide (sol) |
| `1` | Mur |
| `N` | Joueur orienté Nord |
| `S` | Joueur orienté Sud |
| `E` | Joueur orienté Est |
| `W` | Joueur orienté Ouest |
| ` ` (espace) | Partie valide de la map (à gérer) |

**Contraintes de la map :**
- Doit être **fermée/entourée de murs** (`1`)
- **1 seul joueur** maximum
- **Aucune ligne vide** dans la map
- Espaces sont valides mais doivent être gérés
- La map est parsée telle qu'elle apparaît dans le fichier

---

## 2. Règles du programme

### 2.1 Contrôles joueur

| Touche | Action |
|--------|--------|
| `W` | Avancer |
| `A` | Strafe gauche |
| `S` | Reculer |
| `D` | Strafe droite |
| `←` (flèche gauche) | Rotation gauche |
| `→` (flèche droite) | Rotation droite |
| `ESC` | Fermer le programme |

### 2.2 Événements système

- **Croix rouge** : Fermeture propre du programme
- **Fenêtre** : Gestion fluide (changement de fenêtre, minimisation)

### 2.3 Affichage

- Affichage dans une fenêtre via MiniLibX
- **Textures de murs différentes** selon l'orientation (N/S/E/W)
- Couleurs distinctes pour sol et plafond
- Utilisation d'images MiniLibX recommandée

---

## 3. Cas d'erreur à détecter

### 3.1 Erreurs de fichier

| Erreur | Description |
|--------|-------------|
| Fichier inexistant | Le chemin donné n'existe pas |
| Fichier illisible | Permissions insuffisantes |
| Mauvaise extension | Le fichier ne termine pas par `.cub` |

### 3.2 Erreurs de configuration

| Erreur | Description |
|--------|-------------|
| Texture manquante | Une des textures NO/SO/WE/EA absente |
| Texture dupliquée | Même identifiant utilisé plusieurs fois |
| Texture invalide | Fichier texture inexistant ou illisible |
| Couleur manquante | F ou C absent |
| Couleur dupliquée | Même identifiant utilisé plusieurs fois |
| Format couleur invalide | Pas au format `R,G,B` |
| Valeur couleur hors plage | R, G ou B ∉ [0,255] |

### 3.3 Erreurs de map

| Erreur | Description |
|--------|-------------|
| Map absente | Aucune map dans le fichier |
| Map non fermée | Map non entourée de murs |
| Aucun joueur | Pas de N/S/E/W dans la map |
| Plusieurs joueurs | Plus d'un N/S/E/W dans la map |
| Caractère interdit | Caractère autre que 0,1,N,S,E,W,espace |
| Map avant éléments | Map apparaît avant textures/couleurs |
| Ligne vide dans map | Ligne vide au milieu de la map |

### 3.4 Erreurs mémoire/système

| Erreur | Description |
|--------|-------------|
| Malloc échoué | Allocation mémoire impossible |
| Image non chargée | mlx_xpm_file_to_image échoue |

### 3.5 Format de sortie d'erreur

```
Error
<message explicite>
```

Le programme doit quitter proprement (exit), pas crasher.

---

## 4. Contraintes techniques 42

### 4.1 Compilation

- Compilateur : `cc`
- Flags : `-Wall -Wextra -Werror`
- Bibliothèques : math (`-lm`), MiniLibX, libft (autorisée)

### 4.2 Makefile

Règles obligatoires :
- `all` : Compile le programme
- `clean` : Supprime les .o
- `fclean` : Supprime les .o et l'exécutable
- `re` : fclean + all
- `bonus` : Compile avec les bonus (non requis pour nous)

### 4.3 Norme 42

- Fonctions ≤ 25 lignes
- Maximum 5 variables par fonction
- Pas de `for`, `do-while`, `switch`
- Pas de déclaration dans le corps des fonctions
- Lignes ≤ 80 caractères (recommandé)

### 4.4 Mémoire

- **Zéro leak** : Toute mémoire allouée doit être libérée
- Pas de crash (segfault, bus error, double free)
- `valgrind` doit passer sans erreur

---

## 5. Fonctions autorisées

### 5.1 Standard C

| Fonction | Usage |
|----------|-------|
| `open`, `close`, `read`, `write` | I/O fichiers |
| `printf` | Affichage |
| `malloc`, `free` | Mémoire |
| `perror`, `strerror` | Messages d'erreur |
| `exit` | Terminaison |
| `gettimeofday` | Timing |

### 5.2 Math library (`-lm`)

Toutes les fonctions mathématiques :
- `sin`, `cos`, `tan`
- `sqrt`, `pow`
- etc.

### 5.3 MiniLibX

- `mlx_init`
- `mlx_new_window`
- `mlx_new_image`
- `mlx_get_data_addr`
- `mlx_xpm_file_to_image` / `mlx_png_file_to_image`
- `mlx_put_image_to_window`
- `mlx_hook`
- `mlx_loop`
- `mlx_destroy_image`
- `mlx_destroy_window`
- etc.

---

## 6. Edge cases identifiés

### 6.1 Parsing

- Fichier vide
- Fichier avec uniquement des espaces/lignes vides
- Éléments mélangés (textures après map)
- Map avec espaces internes
- Map avec largeur variable (rectangulaire non requis)
- Chemins de texture avec espaces
- Couleurs avec espaces supplémentaires

### 6.2 Map

- Map 1x1
- Map rectangulaire parfaite
- Map irrégulière (largeur variable)
- Map avec "trous" (espaces entourés de murs)
- Map en spirale
- Map très grande

### 6.3 Rendu

- Joueur contre un mur
- Joueur dans un couloir étroit
- Vue directement face à un mur
- Vue dans un angle

---

## 7. Exemple de fichier .cub valide

```
NO ./textures/wall_north.xpm
SO ./textures/wall_south.xpm
WE ./textures/wall_west.xpm
EA ./textures/wall_east.xpm
F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

---

## Checklist de validation

- [ ] Toutes les règles extraites
- [ ] Tous les cas d'erreur identifiés
- [ ] Fonctions autorisées documentées
- [ ] Edge cases listés
- [ ] Exemple valide compris