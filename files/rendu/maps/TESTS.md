# Tests Cub3D

## Maps de test valides

### simple.cub
Map 10x10 avec un joueur orienté Nord.

### valid.cub
Map 16x9 avec un joueur orienté Nord.

## Tests d'erreur à créer

- Map sans joueur
- Map avec plusieurs joueurs
- Map non fermée
- Texture invalide
- Couleur invalide

## Commandes de test

```bash
# Test map valide
./cub3D maps/simple.cub

# Test map valide plus grande
./cub3D maps/valid.cub

# Test erreur (modifier le fichier .cub pour tester)
```

## Valgrind (après exécution)

```bash
valgrind --leak-check=full --show-leak-kinds=all ./cub3D maps/simple.cub
```