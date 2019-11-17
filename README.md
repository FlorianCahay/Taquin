# Taquin
Jeu du taquin avec une interface graphique utilisant la [LibMLV](www-igm.univ-mlv.fr/~boussica/mlv/).

## Compilation et exécution
Pour générer l'exécutable, placez-vous dans le répertoire racine du projet avec un terminal et tapez:
```bash
make
```
Les fichiers .o se trouveront dans le répertoire /bin/ et l'exécutable du projet se trouvera à la racine du projet.

Ensuite pour exécuter le script tapez:
```bash
./taquin
```

## Nettoyage
Pour supprimer seulement les fichiers objets (.o):
```bash
make clean
```
Pour supprimer tous les fichiers générés:
```bash
make mrproper
```
