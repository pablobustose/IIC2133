# DOCUMENTO DE DISEÑO T3 IIC2133

- Nombre Alumno: Pablo Bustos Espina
- Email Alumno: pablo.bustos@uc.cl

## Análisis de enunciado

Tras la lectura y detenido análisis que realicé del enunciado, logré determinar cómo abordar el problema utilizando debidas estructuras de datos y algoritmos para cada caso. La primera parte del enunciado se realizará utilizando programación dinámica, en donde se irá verificando a través de esta técnica las ganancias respectivas de realizar una fiesta en un pueblo, en donde conlleva que se deben de saltar los vecinos respectivos. Por otro lado, para la segunda parte de la tarea se utilizará un algoritmo DFS que logrará la complejidad deseada para encontrar los puntos de articulación de los grafos. Por último, para la modelación del problema de cobertura mínima, se realizará un algoritmo de Kruskal para obtener el MST, para luego implementar un algoritmo que optimice el resultado.

Para lograr las partes de la tarea, se definirán ciertos structs, los cuales serán explicados en el siguiente punto.

## Planificación de la solución

Para comenzar a abordar la tarea, se comenzará con la primera parte, en donde primero se definirá el struct Pueblo, el cual va a tener su ganancia respectiva y serán ingresados en un array con todos los pueblos. Luego, se aplicará la función de programación dinámica, la cual irá guardando en otro array los valores que va obteniendo para lograr su ventaja de "memoria" al momento de realizar su ejecución.

Por otro lado, para la segunda parte de la tarea, se creará un struct de Nodo, el cual tendrá atributos para saber si fue visitado, sus vecinos, etc. Con esto se construirá y obtendrá un grafo no dirigido, al cual se le aplicará el algoritmo para verificar si es punto de articulación o no. La clave de esto está en el atributo "visitado" de cada nodo, el cual permitirá identificar y llevar el correcto conteo de todos los nodos.

Por último, se implementará el algoritmo de Kruskal que hemos visto en clases, en donde utilizaré 3 structs (Nodo, Conexión y Heap). Para tener el orden previo que requiere Kruskal, ordenaré las conexiones mediante el uso de Heap (como se ve en la cápsula de video), logrando una complejidad favorable. Luego, me basaré en el pseudocódigo de Kruskal de clases para modificarlo y aplicarlo al problema de la tarea. Con esto, obtendré el MST, para luego aplicarle el algoritmo que lo optimice.

## Justificación

Con respecto a la utilización de programación dinámica para el primer problema, esta se utilizará debido a que sirve bastante con los problemas de optimización, ya que va utilizando "memoria" para que al momento de dividir el problema en subproblemas, se simplifique y no calcule innecesariamente los datos nuevamente, beneficiando la complejidad.

Respecto a la segunda parte, se utilizará DFS ya que es bastante útil al momento de trabajar con grafos e ir recorriéndolos, como fue visto en clases. Además, la creación del struct de Nodo es fundamental para implementar dicho algoritmo, ya que ordena el código y facilita el manejo de los datos en este para generar el grafo.

Finalmente, se utilizará Kruskal ya que, como se desea primeramente obtener el MST del grafo completo del enunciado, dicho algoritmo es bastante útil. Además, se utiliza Heap para ordenar las conexiones de los nodos, ya que se logra una complejidad promedio beneficiosa en comparación con otros algoritmos de búsqueda, debido a la estructura que posee, tanto la inserción como eliminación.






