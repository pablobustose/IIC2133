# Tarea 2 2023-2

## Ejecución

Para compilar:

```bash
make clean && make
```

Ejecutar parte 1:

```bash
./worldGen input.txt output.txt
```

Ejecutar parte 2:

```bash
./squads input.txt output.txt
```

Para comparar respuestas: 

```bash
diff -b correct_output.txt student_output.txt
```

En caso de querer utilizar utilizar ```valgrind```:

```bash
valgrind ./nombre_del_ejecutable input output
```