# Compilation instruction

## first clone with submodule

```{.sh}
git clone --recurse-submodules git@github.com:Carl-Delrieu/Projet_IG_23_24.git Animation
```

## second builds external

```{.sh}
cd Animation
cmake -S . -B build
cmake --build build -j 
```

This will install the dependencies in Animation/external/Bundle-GNU (or similar depending on your compiler)


## Then build the main project

go back to Animation
cmake -S . -B build

```{.sh}
cd ../
```

and build with the external install dir specified

```{.sh}
cmake -S . -B build  -DCMAKE_PREFIX_PATH=external/Bundle-GNU/
cmake --build build -j
```

run `./Bundle-GNU/Debug/bin/main-app` 


___

# Rapport

Travail à faire (en partant du code fourni, à adapter suivant ce que vous avez) :
- [x] définir une classe Bone contenant une transformation
- [x] ajouter les données de poids au Vertex
- [x] calculer les poids pour chaque Vertex
- [x] définir 2 Bones succéssif dont les articlulations se trouvent respectivement à la base et au milieu du cylindre
- [x] animer l'articulation du milieu (vous pouvez ajouter des primitives visuelles pour afficher avec deux segments les deux bones)
- [ ] ajouter au maillage une donnée "pose de référence"
- [x] animer les points du maillage en CPU (et mettre à jour les données sur le GPU)
- [x] effectuer le même calcul sur GPU (en envoyant les poids et les matrices de transformation au shader).