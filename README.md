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