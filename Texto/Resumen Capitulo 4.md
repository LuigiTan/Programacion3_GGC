### Introducción 

A tree can be defined in several ways. One natural way to define a tree is recursively. A tree is a collection of nodes. The collection can be empty; otherwise, a tree consists of a distinguished node, r, called the root, and zero or more nonempty (sub)trees T1, T2, ... , Tk, each of whose roots are connected by a directed edge from r. The root of each subtree is said to be a child of r, and r is the parent of each subtree root.
From the recursive definition, we find that a tree is a collection of N nodes, one of which is the root, and N − 1 edges. That there are N − 1 edges follows from the fact that each edge connects some node to its parent, and every node except the root has one parent.

![[Pasted image 20231108163235.png]]

### Implementación

One way to implement a tree would be to have in each node, besides its data, a link to each child of the node. However, since the number of children per node can vary so greatly and is not known in advance, it might be infeasible to make the children direct links in the data structure, because there would be too much wasted space. The solution is simple: Keep the children of each node in a linked list of tree nodes.
There are many applications for trees. One of the popular uses is the directory structure in many common operating systems, including UNIX and DOS.

## Arboles Binarios

A binary tree is a tree in which no node can have more than two children. The next figure shows that a binary tree consists of a root and two subtrees, TL and TR, both of which could possibly be empty.
![[Pasted image 20231108203449.png]]

A property of a binary tree that is sometimes important is that the depth of an average binary tree is considerably smaller than N. An analysis shows that the average depth is O( N), and that for a special type of binary tree, namely the binary search tree, the average value of the depth is (logN). Unfortunately, the depth can be as large as N − 1, like in the following image.
![[Pasted image 20231108203630.png]]

### Implementación de binarios

Because a binary tree node has at most two children, we can keep direct links to them. The declaration of tree nodes is similar in structure to that for doubly linked lists, in that a node is a structure consisting of the element information plus two pointers (left and right) to other nodes.

We could draw the binary trees using the rectangular boxes that are customary for linked lists, but trees are generally drawn as circles connected by lines, because they are actually graphs. We also do not explicitly draw *nullptr*  links when referring to trees, because every binary tree with N nodes would require N + 1 *nullptr* links.

### Ejemplo: Arboles de expresiones (investigación)

Los árboles de expresiones son estructuras de datos que definen código. Se basan en las mismas estructuras que usa un compilador para analizar el código y generar el resultado compilado.

Los árboles binarios se utilizan para almacenar expresiones aritméticas en memoria, esencialmente en compiladores de lenguajes de programación. Una expresión es una secuencia de tokens (componentes de léxicos que siguen unas reglas establecidas). Un token puede ser un operando o bien un operador.
Los paréntesis no se almacenan en el árbol pero están implicados en la forma del árbol, como puede apreciarse en la siguiente imagen.

![[Pasted image 20231108210412.png]]
En pocas palabras, un árbol de expresión es un árbol binario con las siguientes propiedades:   
1. Cada hoja es un operando.   
2. Los nodos raíz y los nodos internos son operadores.   
3. Los subárboles son sub-expresiones cuyo nodo raíz es un operador.

Otro ejemplo:
$(a+b)-((c-d)+e)$

![[Pasted image 20231108211022.png]]

### Arboles ADT, Arboles Binarios de búsqueda

The property that makes a binary tree into a binary search tree is that for every node, X, in the tree, the values of all the items in its left subtree are smaller than the item in X, and the values of all the items in its right subtree are larger than the item in X. Notice that this implies that all the elements in the tree can be ordered in some consistent manner. On the next image the tree on the left is a binary search tree, but the tree on the right is not. The tree on the right has a node with item 7 in the left subtree of a node with item 6 (which happens to be the root). Basically, it doesn't count as a search tree because one of the numbers on the left subtree is larger than the root.
![[Pasted image 20231108211702.png]]

## Los arboles AVL (investigacion)

Un **árbol binario balanceado** (también conocidos simplemente como árboles AVL en honor a sus creadores Adelson-Velski y Landis) es un árbol binario de búsqueda (ABB) en el que las alturas de los dos subárboles de cada nodo difieren a lo más en 1.

El **balance** de un nodo en un árbol binario en general y de un árbol AVL en particular, se define como la altura de su subárbol izquierdo menos la altura de su subárbol derecho:

$$| altura(arbolIzquierdo) - altura(arbolDerecho) | < 2$$

También existe la correspondiente definición simétrica: la altura de su subárbol derecho menos la altura de su subárbol izquierdo; pero en este _blog_ se adoptará la primera. Por convención, la altura de un árbol AVL nulo o vacío se define como -1.  
Durante el proceso de inserción o eliminación puede ocurrir un desbalance, es decir, que el valor absoluto de la altura de alguno de los nodos del árbol AVL sea mayor que 1. 

En caso de existir **desbalance** en alguno de los nodos, es decir, una condición que incumpla lo establecido por la expresión anterior, se tiene que rebalancear el árbol para que éste siga siendo un árbol AVL válido.

En este sentido, existen cuatro casos que corrigen el balanceo de un árbol AVL:  

1. **Caso 1**: rotación simple derecha.
2. **Caso 2**: rotación simple izquierda.
3. **Caso 3**: rotación doble izquierda derecha.
4. **Caso 4**: rotación doble derecha izquierda.

### Rotación Simple

El primer caso se puede apreciar en la siguiente imagen

![[Pasted image 20231108213106.png]]

La figura (a) muestra hasta antes de la inserción del elemento representado por el cuadrado rojo (cuadrado más obscuro), un árbol AVL balanceado. El balance puede determinarse gráficamente por los niveles representados por líneas horizontales punteadas: el balance para los nodos _A_ y _B_ es 0 y 1 respectivamente. Al insertar el elemento representado por el cuadrado rojo (cuadrado más obscuro), se presenta un desbalance sobre el nodo _B_: ahora el balance para los nodos _A_ y _B_ es 1 y 2 respectivamente. 
 
Por otro lado, la figura (b) muestra la solución al desbalanceo descrito en el párrafo anterior. Para visualizarlo mejor, imagine que en la figura (a), en el nodo representado por _B_ existe una polea fija, de tal forma que al "jalar" _z_ hacia abajo, el subárbol izquierdo de _B_ representado por _A_ sube, mientras que _B_ baja convirtiéndose en el subárbol derecho de _A_. Note cómo _y_ pasa de ser subárbol derecho de _A_, a ser subárbol izquierdo de _B_.

(En el caso de que se necesite hacer una rotación a la izquierda, el proceso es análogo pero de manera simétrica al mostrado )

### Rotación Doble

El caso de rebalanceo que implica una rotación doble es un proceso un poco más elaborado que el de la rotación simple, ya que como su nombre lo indica, implica dos rotaciones. La rotación doble izquierda derecha se muestran en la siguiente imagen.

![[Pasted image 20231108213444.png]]

Ante una situación como la que se presenta en la figura (a) la solución está dada por la figura (c). Ahora bien, existe un paso intermedio entre éstas, mismo que está representado por la figura (b) y es el que se explicará a continuación:  

- La figura (a) muestra, hasta antes de la inserción del elemento representado por el cuadrado rojo (cuadrado más obscuro), un árbol AVL balanceado. El balance puede determinarse gráficamente por los niveles representados por líneas horizontales punteadas: el balance para los nodos _A_, _B_ y _C_ es 0, 0 y 1 respectivamente. Al insertar cualquiera de los elementos representados por el cuadrado rojo (cuadrado más obscuro), se presenta un desbalance sobre el nodo _C_: ahora el balance para los nodos _A_, _B_ y _C_ es -1, (1 o -1 según sea el elemento insertado) y 2 respectivamente.
- Aunque _C_ es el nodo desbalanceado, observe que el balance no se corrige si se realiza una rotación derecha sobre _C_ (asegúrese de comprobarlo). Por otro lado, note los signos de los balances generados por la inserción del elemento que provoca el desbalance.
- En base a lo anterior, la figura (b) muestra una rotación izquierda sobre _A_ aunque el nodo _A_ no está desbalanceado. Note que el balance no se ha corregido todavía, ya que el balance de _A_ es 0 o 1, el de _B_ es 2 o 1, y el de _C_ 2.
- Ahora bien, partiendo de la figura (b), una nueva rotación derecha sobre _C_ generará el árbol de la figura (c) mejorando significativamente el balance general de la mayoría de los nodos.

#### Usos
- Se usa para indexar registros enormes en bases de datos y también para buscar eficientemente en estos.
- Para todo tipos de colecciones en-memoria, incluyendo conjuntos *(sets?)* y diccionarios.
- Aplicaciones en bases de datos, donde inserciones y borrados son menos comunes pero la búsquedas frecuentes de información son necesarias.
- Software que necesita búsquedas optimizadas
- Se aplica en areas corporativas y juegos de *storyline* (?)

#### Ventajas
- Este tipo de arboles se pueden balancear a ellos mismos
- Muy probablemente no va a estar torcido
- Propicia búsquedas mas rápidas que los Arboles Rojo-Negros
- Mejor complejidad de tiempo de búsqueda comparado con otros arboles como el Binario
- La altura no puede exceder *log(N)*, donde N es el el numero total de nodos en el arbol

#### Desventajas
- Es difícil de implementar.
- Tiene muchos factores constantes para algunas de las operaciones
- Menos usado que los arboles Rojo-Negros.
- Debido a su balance estricto, los arboles AVL propician operaciones complicadas de inserción y remover mientras mas rotaciones se hagan.
- Toman mas procesamiento para balancear.

## Arboles biselados o Splay (investigación)

Un Arbol Biselado es un Árbol binario de búsqueda auto-balanceable, con la propiedad adicional de que a los elementos accedidos recientemente se accederá más rápidamente en accesos posteriores. Realiza operaciones básicas como pueden ser la inserción, la búsqueda y el borrado en un tiempo del orden de $O(log n)$. Para muchas secuencias no uniformes de operaciones, el árbol biselado se comporta mejor que otros árboles de búsqueda, incluso cuando el patrón específico de la secuencia es desconocido. Esta estructura de datos fue inventada por Robert Tarjan y Daniel Sleator.

Todas las operaciones normales de un árbol binario de búsqueda son combinadas con una operación básica, llamada biselación. Esta operación consiste en reorganizar el árbol para un cierto elemento, colocando éste en la raíz. Una manera de hacerlo es realizando primero una búsqueda binaria en el árbol para encontrar el elemento en cuestión y, a continuación, usar rotaciones de árboles de una manera específica para traer el elemento a la cima. Alternativamente, un algoritmo "de arriba a abajo" puede combinar la búsqueda y la reorganización del árbol en una sola fase.

### Ventajas e inconvenientes

El buen rendimiento de un árbol biselado depende del hecho de que es auto-balanceado, y además se optimiza automáticamente. Los nodos accedidos con más frecuencia se moverán cerca de la raíz donde podrán ser accedidos más rápidamente. Esto es una ventaja para casi todas las aplicaciones, y es particularmente útil para implementar cachés y algoritmos de recolección de basura; sin embargo, es importante apuntar que para un acceso uniforme, el rendimiento de un árbol biselado será considerablemente peor que un árbol de búsqueda binaria balanceado simple.

Estos arboles también tienen las ventaja de ser mucho mas simples de implementar que otros arboles binarios de búsqueda auto-balanceados, como los Rojo-Negro o los AVL, mientras que el rendimiento en promedio es igual de eficiente. 
Los arboles biselados a su vez no necesitan almacenar ninguna otra información adicional aparte de sus propios datos. No obstante, esos datos extras suelen proporcionar garantías en el peor de los casos.

Uno de los peores casos para el algoritmo básico del árbol biselado es el acceso secuencial a todos los elementos del árbol de forma ordenada. Esto deja el árbol completamente des balanceado. Volviendo a acceder al primer elemento se dispara una operación que toma del orden de $O(n)$ operaciones para volver a balancear el árbol antes de devolver este primer elemento. Esto es un retraso significativo para esa operación final.

## Dudas y Conclusiones

Los arboles son uno de los temas que a mi parecer son de los mas difíciles de comprender a la hora de querer perfeccionarlos o comprender como implementarlos en código, sin embargo; parece ser que estos a su vez son una herramienta muy buena para darle un orden a información dada y buscarla por lo que es bueno tratar de entender como funcionan. 
El libro en mi opinion nos suele saturar mucho a la hora de explicar, aparte de que lo suele hacer de de una forma algo desacomodada y muy técnica, lo cual solo ayuda a confundirnos y hacernos bolas mas fácil. Es por esto que varios de los temas preferí de buscarlos en internet para comprenderlos mejor, y debo admitir que si bien si termine con una mucho mejor comprensión de los temas investigados, todavía me costaría trabajo aplicarlos en código como tal. 
Como ejemplo y también una de las dudas que todavía me quedan son las rotaciones. Al leer como funcionan y ver una grafica representando el proceso tanto de la simple como de la doble, puedo entender que esta pasando casi al 100% pero estoy seguro (y me consta) que a la hora de tratar de implementarlo en código o ver un código que ya lo hace estaría muy perdido; lo mismo pasaría con los Splay, pero a lo que tengo entendido ese tipo de arboles no son muy óptimos y no tan populares así que es posible que no sean tan importantes como los otros.

## Referencias

- M. A. Weiss, _Data Structures and Algorithm Analysis in C++_, 4th ed. Upper Saddle River, NJ: Pearson, 2013.
- A. A. Follow, “AVL tree data structure,” _GeeksforGeeks_, 02-Jan-2023. [Online]. Available: https://www.geeksforgeeks.org/introduction-to-avl-tree/. [Accessed: 07-Nov-2023].
- M. Angel, “ARBOLES DE EXPRESIONES,” _Blogspot.com_, 10-Sep-2019. .
- V. mi P. Completo, “Fundamentos de la Programación Orientada a Objetos,” _Blogspot.com_. [Online]. Available: https://fundamentospoorrr.blogspot.com/2017/06/arboles-binarios-balanceados-avl.html. [Accessed: 04-Nov-2023].
- “Arbol biselado,” _Ecured.cu_. [Online]. Available: https://www.ecured.cu/Arbol_biselado. [Accessed: 07-Nov-2023].