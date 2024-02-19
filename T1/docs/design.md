# DOCUMENTO DE DISEÑO T1 IIC2133

- Nombre Alumno: Pablo Bustos Espina
- Email Alumno: pablo.bustos@uc.cl

## Análisis de enunciado

Tras la lectura y detenido análisis que realicé del enunciado, logré determinar cómo abordar el problema utilizando debidas estructuras de datos para cada caso. Para ambas partes de la tarea, con el objetivo de implementar árboles al momento de resolver los problemas, se crearán structs de nodos, los cuales tendrán sus respectivos atributos y punteros a sus hijos.

Además, se crearán algunos atributos estratégicos para los nodos, para que se facilite la resolución del problema, los cuales serán explicados en el tercer punto.

## Planificación de la solución

Para comenzar a abordar la tarea, se comenzará con la primera parte, ya que se ve más sencilla a simple vista. Primero se definirá el struct de nodo con sus atributos, para luego implementar una función que cree el BST a partir de los inputs que se van entregando. Una vez realizado esto, gracias al enunciado, se logra interpretar que la función invert afecta a la gran mayoria de las funciones, por lo que se implementará esa función primero, dándole un atributo bool estratégico a la raiz para saber si se ha invertido el árbol o no. Ya habiendo realizado eso, se implementarán el resto de las funciones, las cuales utilizarán este atributo booleano para saber como realizar su tarea.

Con respecto a la segunda parte de la tarea, también se comenzará implementando un struct de nodo para que luego se pueda crear el QuadTree en base a la imagen entregada. Como se sabe que cada nodo puede tener hasta 4 hijos, se hará un array con punteros a sus hijos, facilitando el acceso a ellos. Además, para simplificar el recorrido del arbol al momento de realizar las funciones dadas, se calcularán las medias y desviaciones estándares de cada nodo para que tengan dichos valores como atributos, y una vez realizado esto, se implementarán las funciones de filtro y compresión.

## Justificación
Con respecto a la utilización de structs de nodos en ambas partes, se tomó dicha decisión ya que se deben implementar árboles, tanto BST como Quadtree, por lo que dicha estructura permitirá crearlos con facilidad. 

Además, atribuirle un booleano en la primera parte para saber si el árbol está invertido o no ayudará con el desarrollo del resto de las funciones, ya que solo se tendrá que pensar en el caso que no está invertido, y si lo está, se tendra que hacer la función de manera inversa.

Por último, con respecto a la segunda parte, se utilizó un array de tamaño 4 para los hijos de cada nodo, ya que siempre serán cuatro y se logrará que así se accedan a ellos de manera más fácil y rápida. También, se calcularon las variables numéricas de una sola vez, ya que así al momento de aplicar las funciones solamente se tendrán que verificar dichos valores.
