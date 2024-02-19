# DOCUMENTO DE DISEÑO T0 IIC2133

- Nombre Alumno: Pablo Bustos Espina
- Email Alumno: pablo.bustos@uc.cl

## Análisis de enunciado

Tras la lectura y detenido análisis que realicé del enunciado, logré determinar cómo abordar el problema utilizando debidas estructuras de datos para cada caso. La primera parte del enunciado se realizará utilizando backtracking, en donde se irá rellenando recursivamente el mapa hasta estar completo. Por otro lado, se utilizará una tabla de hash para la segunda parte, en donde se utilizará una función de hash para ir organizando los datos y facilitar el acceso a estos.

Para lograr ambas partes, se definirán ciertos structs, los cuales serán explicados en el siguiente punto.

## Planificación de la solución

Para comenzar a abordar la tarea, se comenzará con la primera parte, en donde primero se definirá el struct Celda, el cual va a estar presente en cada posición del mapa, siendo este una matriz de nxm. Además, cada celda tendrá ciertos atributos como por ejemplo un booleando si está visitado o no, en donde también tendrá un puntero a un struct Tile, el cual será el que está ubicado en la celda. Para la lógica, me basaré un poco en el pseudo código del laberinto visto en clases, en donde lo adaptaré al problema e implementaré las funciones necesarias como comprobar si el tile estará bien ubicado en cierta celda o no.

Por otro lado, para la segunda parte de la tarea, utilizaré una función de hash, la cual será el resto entre un número arbitrario (luego de probar varias veces, con 20 me funcionó) y el largo del escuadrón. Utilicé el largo debido a que, al ver los inputs, se logra ver que están bien distribuidos los datos en base a su alrgo, por lo que con dichos valores y función, se logrará un resultado más óptimo y veloz. Para la implementación, me basaré en la cápsula de hashing publicada en el repositorio.


## Justificación

Con respecto a la utilización de un struct de celda, se tomó dicha decisión porque se debía de llevar un registro de si se ha visitado o no la celda en cierto momento, y si este atributo se agregaba al struct de Tile, iba a haber una mezcla de información entre elementos de distinta celda pero mismo Tile.

Por otro lado, la función de hash utilizada en la segunda parte logró un resultado positivo. Como mencioné anteriormente, al estar bien distribuidos los datos en la tabla de hash, se logra un resultado promedio más veloz, por lo que fue una decisión acertada.
