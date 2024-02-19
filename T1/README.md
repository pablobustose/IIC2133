# Tarea 1 2023-2

Enlace a Tests de la Tarea:
[https://drive.google.com/drive/folders/1pob_8wDD6W57fhC58EnNExNfSLtDldow?usp=sharing](https://drive.google.com/drive/folders/1pob_8wDD6W57fhC58EnNExNfSLtDldow?usp=sharing)

Repositorio de Talleres y Capsulas útiles:
[https://github.com/IIC2133-PUC/Talleres](https://github.com/IIC2133-PUC/Talleres)

## Ejecución

Para compilar:

```bash
make clean && make
```

Ejecutar parte BST:

```bash
./bstRey input.txt output.txt
```

Ejecutar parte Quadtree:

```bash
./hadaCompress imgs/egg_king.png out.png filter 5
```

En caso de querer utilizar utilizar ```valgrind```:

```bash
valgrind ./nombre_del_ejecutable input output
```

## Librerias requridas

Debes instalar `libpng-dev` en caso que no lo tengas instalado. (Make avisara si no lo tienes instalado)

### WSL

```bash
sudo apt install libpng-dev
```

### macOS (Apple Silicon M1, M2)

Para ejecutar esta tarea en Mac con Apple Silicon, se debe utilizar un entorno virtualizado. Para reducir las complicaciones que pueden surgir de usar `edd-docker` desarrollamos dos nuevas herramientas que simplifican el proceso:

- [edd-runner](https://github.com/IIC2133-PUC/edd-runner)
- [edd-dev-container](https://github.com/IIC2133-PUC/edd-dev-container)

### macOS (Intel)

```bash
brew install libpng
brew install zlib
```