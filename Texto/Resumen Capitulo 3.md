# Listas, Stacks y Queues

En este capitulo se discuten 3 de las estructuras de información mas simples y básicas. Basicamente cualquier programa importante va a usar al menos una de estas esctructuras explicitamente, y un *stack* siempre se usa implicitamente en un programa aunque no se declare uno. 
Aqui veremos:
- Intruduccion al concepto de *Abstract Data Types* (ADTs) [Tipos de informacion abstracta]
- Mostrar como realizar operaciones en listas eficientemente
- Introducir el stack ADT y su uso al implementar recurcion
- Introducir la queue[cola] ADT y su uso en sistemacion de operacion y diseño de algoritmos

## Abstract Data Types (ADTs) [Tipos de datos abstractos]

Un *Abstract Data Type* es un conjunto de objetos junto a un conjunto de operaciones. Los *abstract data types* son abstracciones matemáticas sin embargo en la definición de estos no se mencione como se tiene que implementar el conjunto de operaciones. Objetos como listas, conjuntos y graficas, así como sus operaciones pueden ser vistas como ADTs, justo como integrales, reales y booleanos son tipos de información.
Algunas de las operaciones de ADT son *add*, *remove*, *size* y *contains* o, alternativamente puede que solo queramos los dos operadores *union* y *find*, las cuales definiría un ADT diferente en el ***set(?)***. 
La clase de C++ permite la implementación de ADTs, con escondimiento apropiado de los detalles de la implementación. Esto, por lo tanto hace que cualquier otra parte del programa que necesite realizar una operación en el ADT pueda hacerlo llamando el método apropiado. Si por alguna razon, los detalles de implementación necesitan ser cambiados, hacerlo debería de ser fácil, simple de hacer cambiando las rutinas que  que realizan las operaciones de la ADT.

##### Definición mas simple:
*"Un Tipo de dato abstracto (en adelante TDA) es un conjunto de datos u objetos al cual se le asocian operaciones. El TDA provee de una interfaz con la cual es posible realizar las operaciones permitidas, abstrayéndose de la manera en como estén implementadas dichas operaciones. Esto quiere decir que un mismo TDA puede ser implementado utilizando distintas estructuras de datos y proveer la misma funcionalidad.*

*El paradigma de orientación a objetos permite el encapsulamiento de los datos y las operaciones mediante la definición de clases e interfaces, lo cual permite ocultar la manera en cómo ha sido implementado el TDA y solo permite el acceso a los datos a través de las operaciones provistas por la interfaz."*
## La Lista ADT

Hay un conjunto popular de operaciones en las listas ADT: *printList* y *makeEmpty* las cuales hacen cosas obvias. *Find* que regresa la posición de la primera ocurrencia de un objeto; *insert* y *remove* que generalmente inserta y remueve algún elemento de alguna posición en la lista, y *findKth* el cual devuelve el elemento en alguna posición (especificado como un argumento).
Vamos a ver como funcionan:
Si la lista es [34, 12, 52, 16, 12], entonces *find(52)* va a regresar [2] (la posición de 52 en la lista); *insert(x, 2)* va a hacer que la lista se vuelva [34, 12, x, 52, 16, 12] (si insertamos en la posición dada); y *remove(52)* va hacer que la lista se vuelva [34, 12, x, 16, 12].

Todas estas introducciones pueden ser implementadas simplemente usando un arreglo. Aunque los arreglos son creados con una capacidad pre-establecida, la clase *vector* que almacena internamente un arreglo, permite que el arreglo crezca duplicando su capacidad cuando se necesite. Esto soluciona el problema mas serio al usar un arreglo, el cual es que históricamente, para usar un arreglo, un estimado del tamaño máximo de la lista es necesario. Con *vector* este ya no es el caso.

### Listas enlazadas simples

Para evitar el costo lineal de *insertion* y *deletion* necesitamos asegurarnos que la lista no esta almacenada de forma contigua, ya que de otra forma partes completas de la lista necesitarían ser movidas.
La lista enlazada consiste de una serie de nodos que no son necesariamente adyacentes en la memoria. Cada nodo contiene el elemento en cuestión un link a un nodo conteniendo su sucesor. A esto le llamamos el link *next*. El link *next* de la ultima cell apunta a *nullptr*.
Para ejecutar *printList()* o *find(x)*, simplemente comenzamos en el primer nodo de la lista y luego recorremos la lista siguiendo los siguientes enlaces. La operación *findKth* toma O(i) tiempo y funciona al recorrer atreves de la lista de una forma obvia. 
El método *remove* puede ser ejecutado en un cambio al puntero *next*
El método *insert* requiere obtener un nuevo nodo del sistema usando una llamada *new* y luego ejecutando dos maniobras de puntero *next*
Como podemos ver, por lo general si sabemos donde se va a hacer un cambio, insertar o remover elementos de una lista enlazada no requiere mover muchas cosas, si no que solo involucra un numero constante de cambios a los enlaces de los nodos

Si bien la siguiente imagen de ejemplo es para punteros, también aplica para el tema de listas para entender mejor como funciona.
![[Pasted image 20231004225206.png]]
A continuación hay otros ejemplos de como funcionan las diferentes operaciones

##### Lista enlazada
![[Pasted image 20231004225405.png]]

##### Borrado en una lista enlazada 
![[Pasted image 20231004225459.png]]

##### Inserción en una lista enlazada 
![[Pasted image 20231004225542.png]]

##### Una lista doblemente enlazada
![[Pasted image 20231004225625.png]]

## *vector* y *list* en el STL

El lenguaje de programación C++ incluye en su librería una implementación de estructuras de datos comunes. Esta parte del lenguaje es conocido popularmente como "Standard Template Library" (STL). La lista ADT es una de las estructuras de datos implementadas en la STL. A estas estructuras de datos también se les denomina como *collections* o *containers*.
Hay dos implementaciones populares de la lista ADT. El *vector* proporciona una implementación de matriz ampliable de la lista ADT. La ventaja de utilizar el *vector* es que es indexable ***-(no se que significa indexable)-*** en tiempo constante. La desventaja es que la inserción de nuevos elementos y la eliminación de elementos existentes cuesta muchos recursos, a menos que los cambios se realicen al final del vector.
Por otro lado la *list* proporciona implementación de la lista ADT en forma de lista doblemente enlazada. La ventaja de utilizar la lista es que la inserción de nuevos elementos y la eliminación de elementos existentes es económica, siempre que se conozca la posición de los cambios. No obstante, la lista no es fácilmente *indexable*. Tanto el *vector* como la *list* son ineficientes para búsquedas.

El *vector* y la *list* son plantillas de clase que se instancian con el tipo de objetos que almacenan.. Los siguientes métodos están disponibles en todos los *containers* STL:

- `int size () const`: devuelve el número de elementos en el *container*.
- `void clear()`: remueve todos los elementos del *container*.
- `bool empty() const`: devuelve *true* si el *container* no contiene elementos, y de otra forma *false*
- `void push_back( const Object & x )`: añade [x] al final de la lista
- `void pop_back( )`: remueve el elemento al final de la lista
- `const Object & back( ) const`: devuelve el elemento al final de la lista 
- `const Object & front( ) const`: devuelve el elemento al frente de la lista

Ya que una lista doblemente enlazada permita cambios eficientes al frente, pero un *vector* no, los siguientes métodos solo funcionan para *list* 

- `void push_front( const Object & x )`: añade *x* al frente de la lista.
- `void pop_front( )`: remueve el elemento al frente de la lista.

El *vector* tiene sus propios métodos que no son partes de *list*. Dos métodos permiten indexar eficientemente. Los otros 2 le permiten al programador ver y cambiar la capacidad interna. Estos métodos son:

- `Object & operator[] ( int idx ):` devuelve el elemento en el índice *idx* en el *vector*, sin *bound-checking* ***(no se que significa eso)***
- `Object & at( int idx ):` devuelve el elemento en el índice *idx* en el *vector*, con *bound-checking*.
- `int capacity( ) const:` devuelve la capacidad interna de un *vector* 
- `void reserve( int newCapacity ):` establece una nueva capacidad. Si una estimación buena esta disponible, puede ser usada para evitar expansión del *vector*.

##### Indexable:
Quiere decir que algo se puede *indexar*
**Indexación** es el acto y la consecuencia de indexar**: realizar indices. La noción de índice, a su vez, tiene varios usos, aunque en este caso nos interesa sobre todo su acepción como una lista o catálogo de obras, artículos, capítulos, etc. que tiene un cierto orden.
La acción de indexar, por lo tanto, refiere al registro ordenado de informaciones y datos con el objetivo de generar un índice. La idea de indexación se utiliza principalmente en el terreno de Internet y en la economía.
***(Parece que era bastante obvio que significa)***
### Iteradores

En algunas operaciones en listas, mas precisamente, aquellas para insertar o remover elementos de la mitad de la lista requieren la posición del elemento. En el STL una posición se presenta por un *iterator* [iterador] anidado ***(como que anidado? Dice nested)***.
En particular, para una `list<string>` la posición es representada por el *type* `list<string>::iterator`; para un `vector<int>`, la posición es representada por un *class* `vector<int>::iterator` y así.

#### Conseguir un Iterador

Las listas STL (y todos los demás *containers* STL) definen un par de métodos
- `iterator begin( )`: returns an appropriate iterator representing the first item in the container.
- `iterator end( )`: returns an appropriate iterator representing the endmarker in the container (i.e., the position after the last item in the container).`

El método *end* puede parece un poco inusual, ya que regresa un iterador que esta *"out of bounds"* . Para ver la idea considera el siguiente código. 
``` C++
for( int i = 0; i != v.size( ); ++i )
	cout << v[ i ] << endl;
```

#### Métodos de Iteradores

Aparte de copiar, las operaciones mas usadas en iteradores incluyen las siguientes :
- `itr++ and ++itr`: advances the iterator `itr` to the next location. Both the prefix and postfix forms are allowable.
- `*itr`: returns a reference to the object stored at iterator `itr`’s location. The reference
returned may or may not be modifiable (we discuss these details shortly).
- `itr1==itr2`: returns true if iterators `itr1` and `itr2` refer to the same location and false
otherwise. 
- `itr1!=itr2`: returns true if iterators `itr1` and `itr2` refer to a different location and false otherwise.

Con estos operadores, el código para imprimir seria.
```C++
for( vector<int>::iterator itr = v.begin( ); itr != v.end( ); ++itr )
	cout << *itr << endl;
```

El uso de la sobrecarga de operadores permite acceder al elemento actual y luego avanzar al siguiente elemento usando `*itr++`. Por lo tanto, una alternativa al fragmento anterior es

```C++
vector<int>::iterator itr = v.begin( );
while( itr !=v.end( ) )
	cout << *itr++ << endl;
```

#### Operaciones de *containers* que requieren iteradores

Los 3 métodos mas populares que requieren iteradores son aquellos que añaden o remueven de la lista (ya sea un *vector* o una *list*) en una posición especificada:
- `iterator insert( iterator pos, const Object & x )`: adds [x] into the list, prior to the position given by the iterator *pos*. This is a constant-time operation for *list*, but not for vector. The return value is an iterator representing the position of the inserted item.
- `iterator erase( iterator pos )`: removes the object at the position given by the iterator. This is a constant-time operation for *list*, but not for *vector*. The return value is the position of the element that followed *pos* prior to the call. This operation invalidates *pos*, which is now stale, since the container item it was viewing has been removed.
- `iterator erase( iterator start, iterator end )`: removes all items beginning at position *start*, up to, but not including *end*. Observe that the entire list can be erased by the `call c.erase( c.begin( ), c.end( ) )`.

#### Uso de *erase* en una Lista



```C++
1 template <typename Container>
2 void removeEveryOtherItem( Container & lst )
3 {
4	auto itr = lst.begin( ); // itr is a Container::iterator
5
6	while( itr != lst.end( ) )
7	{
8		itr = lst.erase( itr );
9		if( itr != lst.end( ) )
10			++itr;
11		}
12 }
```

Usar iteradores para remover cada otro elemento en una lista (ya sea un *vector* o *list*) es eficiente para una lista, pero no para un vector
En este caso, si la lista contiene [6, 5, 1, 4, 2]  entonces después de que el método es llamado, esta va a contener [5, 4]. Hacemos esto avanzando atreves de la lista y usando el método *erase* en cada segundo elemento. En una *list* esto va a ser una rutina de tiempo linear porque cada una de las llamada a *erase* toma tiempo constante, pero en un *vector* la rutina completa tomara un tiempo cuadrático ya que cada llamada a *erase* es ineficiente.
El uso de ***auto*** en la línea 4 es una caracteristica de C++11 que permite tener que escribir `Container::iterator`

#### `const_iterators`

***(con toda honestidad, toda esta sección me fue perdiendo gradualmente)***

El resultado de `*itr` no es solo el valor del elemento que el iterador esta viendo sino que también es el elemento en si. Esta distinción hace a los iteradores muy poderosos pero también introduce algunas complicaciones. La siguiente rutina funciona para tanto *vector* como *list* y corre en tiempo linear.
```C++
template <typename Container, typename Object>
void change( Container & c, const Object & newValue )
{
	typename Container::iterator itr = c.begin( );
	while( itr != c.end( ) )
		*itr++ = newValue;
}
```

Para ver el problema potencial, supongamos que el *Container c* fue pasado a una rutina usando llamada por referencia constante. Esto significa que esperaríamos que no se permitieran cambios en c, y el compilador se aseguraría de ello no permitiendo llamadas a ninguno de los mutadores de c.

Toda colección de STL no solo contiene un iterador de tipo anidado si no también un *const_iterator* de tipo anidado. La principal diferencia entre estos dos es que `operator*` para *const_iterator* devuelve una referencia constante, y por lo tanto `*itr` para const_iterator no puede aparecer en la parte izquierda de la declaración de una asignación.
Además, el compilador va a forzar el uso de un *const_iterator* para checar una colección constante, proporcionando 2 versiones de *begin* y *end*.
- `iterator begin( )`
 - `const_iterator begin( ) const`
 - `iterator end( )`
 - `const_iterator end( ) const`

![[Pasted image 20231005023500.png]]
***(^no entendí nada de esto^)***

Si se usa *auto* para declarar los iteradores, el compilador deducirá por nosotros si se sustituye un *iterador* o un *const_iterador*; en gran medida, esto libera al programador de tener que estar pendiente del iterador correcto.

Una característica adicional en C++11 permite escribir código que funciona incluso si el *container* no tiene funciones *begin* y *end*. A estas se les llaman [Non-member free functions] o *Funciones libres sin miembros* en español. En estas mismas *begin* y *end* son definidas de forma que permiten el uso de *begin(c)* en cualquier lugar donde *c.begin()* esta permitido. Escribir código usando *begin(c)* sobre el otro tiene la ventaja que permite que el código genérico funcione tanto en *containers* que tienen *begin*/*end* de miembros, así como en aquellos que no tienen *begin*/*end* pero pueden ser aumentados con Funciones Libres sin Miembros adecuadas.
```C++
template <typename Container>
void print( const Container & c, ostream & out = cout )
{
	if( c.empty( ) )
		out << "(empty)";
	else
	{
		auto itr = begin( c ); // itr is a Container::const_iterator

		out << "[ " << *itr++; // Print first item

		while( itr != end( c ) )
			out << ", " << *itr++;
		out << " ]" << endl;
	}
}
```

La adición de *begin* y *end* como funciones libres en C++11 es posible gracias a la adición de características de lenguaje como *auto* y *decltype*.

```C++
template<typename Container>
auto begin( Container & c ) -> decltype( c.begin( ) )
{
	return c.begin( );
}
template<typename Container>
auto begin( const Container & c ) -> decltype( c.begin( ) )
{
	return c.begin( );
}
```

### Implementación de *vector*

##### Algunas características importantes de los arreglos primitivos de C++:

- El arreglo es simplemente un puntero hacia un bloque de memoria; el tamaño real del arreglo debe de ser mantenido separadamente por el programador
- El bloque de memoria puede ser asignado por medio de `new[]` pero luego debe ser liberado mediante `delete[]`
- El bloque de memoria no puede ser reajustado en su tamaño, pero un bloque nuevo mas grande puede ser obtenido e inicializado con el bloque viejo, ya entonces el bloque viejo puede ser liberado

#### Detalles principales de un vector

- El *vector* mantendrá el arreglo primitivo (a través de una variable puntero al bloque de memoria asignado), la capacidad del arreglo y el número actual de elementos almacenados en el *vector*.
- El *vector* implementara el *Big-Five* para proporcionar una semántica de copia profunda para el constructor copy y operator=, y proporcionará un destructor para reclamar el arreglo primitivo.
- El *vector* va a proporcionar una rutina *resize* que cambiara el tamaño del *vector* y una rutina *reserve* que cambiara la capacidad de este. La capacidad es cambiada al obtener un nuevo bloque de memoria para el arreglo primitivo, copiando el bloque viejo al bloque nuevo y reclamando el bloque viejo.
- El *vector* proporcionara una implementación de `operator[]`, este se implementa normalmente con una una version *accessor* y una *mutator*.
- El *vector* proporcionara rutinas básicas como `size`, `empty`, `clear`, `back`,` pop_back` y `push_back`. Esta ultima rutina llamara a reserve si el tamaño y la capacidad son iguales.
- El *vector* proporcionara soporte para los `iterator` y `const_iterator`, y los métodos asociados `begin` y `end`.

***(A continuación el libro presenta varias paginas en donde se muestra un código y se explica este, pero si soy completamente honesto, no los entendí para nada)***

### Implementación de `list`

En esta sección se proporciona la implementación de una plantilla de clase  *list* usable. Esta lista sera implementada como una lista de doble enlace, por lo que necesitaremos mantener punteros a los dos lados de la lista (al principio y al final). Hacer esto nos permite mantener un costo de tiempo constante por operación mientras que la operación se realice en una posición conocida.

Necesitamos 4 clases

- La clase *list* que contiene enlaces a ambos lados, el tamaño de la lista y un anfitrión de métodos
- La clase *Node* que probablemente sea una clase privada anidada. Un nodo contiene los datos y punteros a los nodos anteriores y siguientes, junto con los constructores apropiados.
- La clase `const_iterator`  que abstrae la noción de posición y es una clase anidada publica. Este iterador guarda un puntero al nodo actual y proporciona implementación de operaciones basicas de iterado, todo esto en la forma de operadores sobrecargados como `=`, `==`, `!= `y `++`.
- La clase iterador que abstrae la noción de una posición y es una clase publica anidada. Este tiene la misma funcionalidad que `const_iterator`, excepto que `operator*` devuelve una referencia al elemento que se esta viendo, en vez de una referencia constante a este. Un problema técnico importante es que un `iterator` puede ser usado en cualquier rutina que requiere un `const_iterator`, peor no al revés. 

Gracias a que la clases iterador guardan un puntero en el "nodo actual" y el marcador final es una posición valida, tiene sentido crear un nodo extra al final de la lista para representar el marcador final. Además podemos crear un nodo extra al frente de la lista, obviamente para representar el marcador al principio. Estos nodos extra son conocidos en ocasiones como ***Nodos centinela***; mas específicamente, el nodo al inicio se conoce como *header node* (nodo cabecera), y a el nodo al final como *tail node* (nodo cola).
La ventaja de utilizar estos nodos adicionales es que simplifican enormemente la codificación al eliminar un foco de casos especiales. Por ejemplo, si no utilizamos un *header node*, eliminar el primer nodo se convierte en un caso especial, porque debemos restablecer el enlace de la lista al primer nodo durante la eliminación y porque el algoritmo de eliminación en general necesita acceder al nodo antes de que este mismo se elimine.

***(Al igual que en el tema anterior, el libro a continuación presenta varas paginas de puro código y sus explicaciones, pero otra vez no les entendí nada)***

![[Pasted image 20231005222101.png]]![[Pasted image 20231005222114.png]]
![[Pasted image 20231005222128.png]]

### Diferencia entre un vector y una lista
Una lista en la STD es una implementación de la estructura de datos llamada Lista Doblemente Enlazada. Tiene como característica que insertar y eliminar, al principio, al final o en medio, se hace en tiempo constante. Mientras que obtener datos se realiza en un tiempo O(n), donde n es el tamaño de la lista. Son particularmente eficientes en casos en los que tienes que insertar más veces que consultar los datos.

Un vector en la STD es un array que es dinámico: cuando inicializas uno se reserva memoria en forma de array para almacenar datos. Esto hace que la consulta de datos se realice en tiempo constante, pero agregar datos al principio y al final del vector, se realice en un tiempo O(n), donde n es el tamaño del vector. ¿Por qué? Porque al igual que los arrays comunes no se puede sobrepasar el tamaño del array que inicialmente ser reservó. Un vector lo que hace es reservar un array mas grande y copiar el antiguo array en el nuevo. Los vectores son utilizados para guardar datos en los que se inserta poco y se consulta mucho.


# Opiniones criticas y conclusiones

Personalmente creo que este capitulo aunque fueron muchas menos paginas que el anterior, este se sintió igual o hasta mas pesado que el anterior, si bien el anterior tenia muchos tecnicismos y formas de escribir y explicar código, así como sintaxis que nunca habíamos visto, estos capítulos tomaron eso y nos lo pusieron más elaborado aun. Incluso cuando algunos de los párrafos se sabían explicar bien y aclararon varias cosa, conforme mas avanzamos en el libro mas se nos muestran las fallas de este, la tendencia a estar referenciando figuras que aun ni salen, repetir muchas cosas redundantes o cortar abruptamente texto para poner una figura o fragmento de texto dejando una explicación a la mitad, genera muchas situaciones de confusión. Sin embargo  cuando el libro logra explicar algo de una manera simple y sin rodeos lo suele hacer bien y no suelen quedar muchas dudas al respecto (aunque no siento que suela pasar mucho). 
En mi opinion, ya que mucho del Código que vemos es uno hecho con la intención de ser lo mas óptimos posibles, para facilitarnos mas el entendimiento deberíamos ver los códigos de 2 formas, primero de la forma mas fácil posible sin ser eficientes, y luego la forma optima para que podamos comparar que partes hacen que y de que forma se optimiza el uso de recursos.

En cuanto al contenido de este capitulo, lo que mas siento que pude entender y sacar al tema es como las diferentes especificaciones de *vector* y *list* hacen que ninguno sea mas util que el otro, cada uno tiene sus usos en diferentes situaciones, el vector tiene una facilidad para consultar datos pero añadir o eliminar elementos no es eficiente, mientras que en las listas es mas fácil y eficiente añadir o eliminar pero consultar no tanto. Otra ejemplo es que un vector puede tener mas uso en ciertas situaciones donde no se tengan tantos datos pero se tenga un flujo constante de estos, ya que al ser dinámico no se tiene que perder mucho tiempo en establecer espacios pero mientras mas se añada, muchos mas recursos se usan a comparación de en una lista.

## Referencias 
- M. A. Weiss, _Data Structures and Algorithm Analysis in C++_, 4th ed. Upper Saddle River, NJ: Pearson, 2013.
- “No title,” _Cplusplus.com_. [Online]. Available: https://cplusplus.com/reference/list/list/. [Accessed: 06-Oct-2023].
- “No title,” _Cplusplus.com_. [Online]. Available: https://cplusplus.com/reference/vector/vector/. [Accessed: 06-Oct-2023].
- “Tipos de datos abstractos,” _Uchile.cl_. [Online]. Available: https://users.dcc.uchile.cl/~bebustos/apuntes/cc30a/TDA/. [Accessed: 06-Oct-2023].
- P. Porto and M. Merino, “Indexación,” _Definición.de_, 28-Jun-2018. [Online]. Available: https://definicion.de/indexacion/. [Accessed: 06-Oct-2023].