## De que trata el libro

Un problema bastante conocido entre estudiantes de programación es el de acomodar un ***n*** cantidad de números y determinar cual es el ***k***° mas grande. A este se le conoce como un problema de selección, y existen distintas formas de solucionarlo, algunas un poco obvias (no tan obvias personalmente) una forma puede ser 
- Acomodar la ***N*** cantidad de números en un arreglo, ordenar este de mayor a menor con un método de ordenamiento como seria *bubble* e imprimir el elemento en la posición ***k*** como la respuesta.  

Otra respuesta podrida ser
- Leer los primeros elementos ***k*** ,ponerlos en un arreglo y acomodarlos de mayor a menor, para después leer los elementos restantes uno por uno. Si el siguiente elemento leído es mas pequeño que el elemento ***k***, se ignora. Si no es colocado en su lugar correcto en el arreglo, moviendo un elemento fuera de su lugar. Cuando el algoritmo se acaba, el elemento en la posición ***k*** es la respuesta (Realmente no se como quedaría esto codificado, a lo mucho hemos hecho algo *similar* pero mas sencillo que la primera opción).  

Los dos algoritmos son relativamente simple de codear sin embargo una pregunta surge de estos: ¿Cual es mejor? Y, ¿Alguno de los dos es suficientemente bueno?
En una simulación usando 30 millones de elementos y dándole a ***k*** un valor de 15,000,000 nos damos cuenta de que ninguno de los dos termina en un tiempo razonable, tomando días de procesamiento para terminar.
Un concepto importante a tener en cuenta es que en muchos problemas, escribir un programa que sirva no es suficiente. Si el programa se tiene que correr con tamaños grandes de información, el tiempo para correrlo se vuelve un problema. En este libro vamos a ver como estimar el tiempo para correr de un programa que usa inputs grandes y mas importantemente, como comparar el tiempo de dos programas sin tener que programarlos. Se verán técnicas que mejoraran drásticamente la velocidad de programas y otras que determinaran cuellos de botella en estos.

## Revision de Matemáticas
#### Exponentes
Se nos muestran resumidamente las leyes de exponentes 

$$
X^A X^B = X^{A+B}
$$ 
$$
{X^A \over X^B} = X^{A - B}
$$
$$
(X^A)^B = X^{AB}
$$
$$
X^N + X^N = 2X^N ≠ X^{2N}
$$
$$
2^N + 2 ^ N = 2^{N+1}
$$
#### Logaritmo
En la ciencia de las computadoras, todos los logaritmos son a la base de 2 a menos de que se especifique de otra forma 
###### Definición:
$$
X^A = B$$  
solo si
$$log_x B = A$$
Un logaritmo es el exponente al cual se necesita elevar una cantidad positiva para obtener como resultado un cierto número. Un exponente en tanto es el numero que denota la potencia a la cual debe elevarse otra cifra
De este modo, el logaritmo de un numero es el exponente al cual tiene que elevarse la base para llegar a dicho numero 
#### Series
Aquí vemos un breve repaso sobre series 
Las formulas mas fáciles de recordar son
![[Pasted image 20230921022935.png]]
Y el compañero 
*(No estoy muy seguro cual es la traducción correcta)*
![[Pasted image 20230921023043.png]]
Así mismo en la formula anterior, si 0< A < 1, entonces
![[Pasted image 20230921023110.png]]
#### Series
*(No entendí muy bien esta parte en el libro)*

Cuando dividimos dos enteros, tenemos una ecuación que se ve como lo siguiente:

$$
{A \over B} = Q
$$
Residuo:
$$ R $$
A es el dividendo  
B es el divisor  
Q es el cociente  
R es el residuo

A veces, solo estamos interesados en cuánto es el **residuo** cuando dividimos A entre B.  
Para estos casos hay un operador llamado el operador módulo (abreviado como mod).

#### La palabra con *P*

Las 2 formas mas comunes de comprobar las declaraciones en analysis  de estructura-data son Prueba por inducción y Prueba por contradicción.
La mejor forma de probar que un teorema es falso es presentando un contraargumento 
###### Prueba por Inducción
Este tiene dos partes estándar, la primera parte es establecer que el teorema es verdad para unos valores pequeños. Después se tiene que asumir una hipótesis inductiva, esto generalmente significa que el teorema se asume como verdad para todos los casos hasta un limite *k*. Con esta suposición, el teorema se demuestra como real para el valor siguiente, el cual es normalmente $$k+1$$
###### Prueba por contraargumento
En este caso lo único que se tiene que hacer es invertir los símbolos de mayor y menor que 
###### Prueba por Contradicción
En este tipo de comprobación se procede, asumiendo que el teorema es falso y mostrando que esta suposición implica que alguna propiedad conocida es falsa y por tanto, la suposición original esta equivocada. 
## Introducción breve a la recursion
La recursividad básicamente se basa en tener funciones que para solucionarse se hablan a si mismas, o en otras palabras, una función que se define en términos de si misma. 
Tomemos de ejemplo el siguiente código
```
1 int f( int x )
2 {
3 	if( x == 0 )
4 	return 0;
5	else
6	return 2 * f( x - 1 ) + x * x;
7 }

```
En la Linea 1, se declara la variable *f* que tiene de valor otra variable *x*
En la Linea 3 se evita redundancia estableciendo que si el valor de *x* es 0, todo el resto de la función también sera 0. Esto también se le conoce como el *caso base* el cual es en donde el valor de la función se sabe directamente sin tener que recurrir a recursion
La Linea 6 es en donde se hace la recursion, pues *dentro* de la función *f* se habla a *f* para determinar su valor usando el valor de *x*
## Clases de C++
### Sintaxis básica de classes
Una clase en C++ consiste de sus *miembros*. Estos pueden ser información o funciones. Las funciones se les llama *funciones de miembros*. Cada instancia de una clase es un **objeto**. Cada objeto contiene la información los componentes especificaron dentro de la clase. Una función de miembro, se usa para actuar como un objeto, estas funciones a menudo se les llama ***métodos***
Tomemos de ejemplo el siguiente codigo:
```
1 /**
2 * A class for simulating an integer memory cell.
3 */
4 class IntCell
5 {
6 public:
7 /**
8 * Construct the IntCell.
9 * Initial value is 0.
10 */
11 IntCell( )
12 { storedValue = 0; }
13
14 /**
15 * Construct the IntCell.
16 * Initial value is initialValue.
17 */
18 IntCell( int initialValue )
19 { storedValue = initialValue; }
20
21 /**
22 * Return the stored value.
23 */
24 int read( )
25 { return storedValue; }
26
27 /**
28 * Change the stored value to x.
29 */
30 void write( int x )
31 { storedValue = x; }
32
33 private:
34 int storedValue;
35 };
```
Aqui podemos ver la clase ***IntCell**. En esta clase, cada instancia de *IntCell* (un objeto) contiene un solo miembro de informacion llamado *storedValue*.
Todo lo demas en esta clase en particular es un metodo (aqui son 4)
Dos de estos metodos son *read* y *write*.
Los otros dos son metodos especiales conocidos como ***constructores**.

Primero que nada, pongamos nuestra atencion en las dos especificaciones *public* y *private* estas etiquetas determinan la visibilidad de los miembros de la clase, en este ejemplo, todo excepto *storedVallue* es publico. Un miembro que es *publico* puede ser accedido por cualquier metodo en cualquier clase, mientras que uno *privado* solo puede ser usado por metodos en su clase.
Normalmente, miembros de informacion se declaran en *private*.
Al usar miembros *privados* podemos cambiar la representación interna del objeto sin que afecte otras partes del programa que usen el objeto. Los usuarios de la clase no necesitan (ni deberían) que saber los detalles internos de como esta implementada una clase, pues esto en la mayoría de casos genera problemas.
Por ejemplo al hacer que una clase que guarda la fecha *privada* podemos evitar que alguien por fuera ponga fechas imposibles como *Febrero 30*.

Otra cosa que vemos en el ejemplo son los ***constructores***. Un constructor es un método que describe como una instancia de una clase es construida. Si no se define un constructor, uno que inicializa miembros de información usando los defaults del lenguaje se genera automáticamente.
La clase que tenemos de ejemplo (IntCell) define dos constructores. El primero se llama si no se especifica un parámetro y el segundo si un parámetro *int* se administra, y usa este para inicializar el miembro *storedValue*

*(Incluso ahora habiendo leído parte de este tema, todavía no le entiendo)

### Sintaxis y *Accessors* de Constructor extra
Aunque las clases funcionan como se estableció, hay algunas sintaxis extra que crean un código mejor. 
Los cuatro cambios se muestran en el nuevo código.
```
1 /**
2 * A class for simulating an integer memory cell.
3 */
4 class IntCell
5 {
6 public:
7 explicit IntCell( int initialValue = 0 )
8 : storedValue{ initialValue } { }
9 int read( ) const
10 { return storedValue; }
11 void write( int x )
12 { storedValue = x; }
13
14 private:
15 int storedValue;
16 };
```
Estas son las diferencias:

#### Parámetros *Default*

El constructor *IntCell* representa el **parámetro default**. Como resultado, sigue habiendo dos constructores *IntCell* definidos. uno acepta un *initialValue*, mientras que el otro es el constructor con parámetro 0.
El valor *default* de 0 significa que 0  se usa si no se da un parámetro como tal. Los *default* se pueden usar en cualquier función pero es mas común en constructores

#### Lista de inicialización
En la línea 8 del código se puede ver que el constructor *IntCell* us una **lista de inicialización** antes de cuerpo del constructor. Esta lista se usa para inicializar los miembros de información directamente. En este nuevo ejemplo no hay mucha diferencia pero usar este tipo de listas en vez de usar declaraciones de asignación en el cuerpo ahorra tiempo en caso de que los miembros de información son tipos de clases que tienen inicializaciones complejas.
En algunos casos, por ejemplo, si un miembro de información es *const* (en otras palabras que no se puede cambiar el objeto una vez construido), su valor solo se puede inicializar en una lista.
Así mismo, si el miembro es si mismo es un tipo de clase que no tiene un constructor de parámetro 0, entonces se *tiene* que inicializar con una lista de inicialización.
(No comprendo a que se refiere con "zero-parameter constructor")

#### Constructor *explicit*
El constructor *IntCell* es *explicit*. Todos los constructores de un-parámetro deberian de hacerse *explicit* para evitar 
Es un constructor que recibe parametros.
Si no se da parametro se vuelve uno implicito
This is a test btw

## Referencias
- J. Pérez Porto and A. Gardey, “Logaritmo,” _Definición.de_, 14-Nov-2018. [Online]. Available: https://definicion.de/logaritmo/. [Accessed: 20-Sep-2023].
- “¿Qué es la aritmética modular?,” Khan Academy. [Online]. Available: https://es.khanacademy.org/computing/computer-science/cryptography/modarithmetic/a/what-is-modular-arithmetic. [Accessed: 20-Sep-2023].
- M. A. Weiss, _Data Structures and Algorithm Analysis in C++_, 4th ed. Upper Saddle River, NJ: Pearson, 2013.