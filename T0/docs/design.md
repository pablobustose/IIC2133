## DOCUMENTO DE DISEÑO T0 IIC2133

- Nombre Alumno: Pablo Bustos Espina
- Email Alumno: pablo.bustos@uc.cl

### Análisis de enunciado
Tras la lectura y detenido análisis que realicé del enunciado, logré determinar cómo abordar el problema utilizando debidas estructuras de datos para cada caso. A grandes rasgos, se puede comprender que para la implementación de los escuadrones se utilizarán arrays y para los guerreros pertenecientes a cada escuadron se utilizarán listas ligadas, lo cual será explicado en el tercer punto. 

Además, se diseñará un struct tanto para los guerreros como para los escuadrones, ya que estos poseen ciertos atributos base que varían entre estos, por lo que tener este "molde" simplificará el desarrollo del código.

### Planificación de la solución

Para comenzar abordando el problema, se definirá el struct de los guerreros con algunas de sus funciones básicas para luego comenzar progresivamente con las funciones que permiten crear los ejércitos y escuadrones. Esto permitirá ir comprobando la correctitud del struct previo a su implementación, lo que podría haber sido una posible fuente de error futura. A los guerreros se le agregará un atributo que apunte a la direccion de memoria del guerrero anterior, ya que al estar relacionado a través de listas ligadas, puede beneficiar y simplificar posibles funciones a lo largo del código. 

Luego, se definirá un struct de escuadrones, los cuales tendran ciertos atributos que beneficien la utilización de listas ligadas para los guerreros, tales como primer guerrero y último guerrero. Para cada ejército estos escuadrones estarán guardados en la memoria a través de un array.

Ya teniendo en cuenta estas breves definiciones de lo básico del código, se comenzarán realizando las funcionalidades solicitadas en orden, para así ir aumentando progresivamente la utilidad del código.

### Justificación

Con respecto a la utilización de arrays en los escuadrones, se tomó dicha decisión ya que al ser un número fijo, no se va a solicitar más memoria en un futuro. Por lo que tener a todos los escuadrones de un ejército juntos afectará de manera positiva ya que acceder a los datos necesario de cada escuadrón será mucho más fácil. Cabe recalcar que para beneficiar aún más la accesibilidad, se utilizará un array para juntar ambos ejércitos, en donde estos guardarán información sobre punteros de punteros. Además, el número de escuadrones amigos fue ingresado como una variable a los escuadrones, en vez que a los ejércitos, ya que de esa forma se logra posible la utilización de punteros a punteros.

Con respecto a las listas ligadas, se determinó dicha estructura para los guerreros ya que el número de estos en cada escuadrón es muy variable y dinámico, en donde movimientos como el trasladar guerreros de un escuadrón a otro se logrará con muchisima facilidad. Cabe recalcar que la conexión entre los escuadrones y guerreros se encuentra sólamente en los parámetros de primer guerrero y último guerrero, los cuales son punteros que apuntan a dicha dirección de memoria. 
