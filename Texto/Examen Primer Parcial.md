## Parte 1.1

- #### 1. ¿Qué es un **Rvalor** y un **Lvalor**?
- Un **Rvalor** es un valor el cual no tiene un espacio de memoria como tal. Por ende no tiene una dirección de memoria y al acceder a este solo se usa un solo amperson (&). Un ejemplo de esto seria que la computadora lea el numero 10, su valor existe mas no esta almacenado en un espacio de memoria.
- Por otro lado un **Lvalor** es un valor que si tiene asignado un espacio de memoria. En el caso de estos, para acceder a estos se necesitan 2 amperson (&&) uno para ver la dirección de memoria y otro para ver dentro de esta. Las variables son el ejemplo principal de estos.
- #### 2. ¿Porqué es necesario que una clase tenga constructores y operadores por copia y por referencia?
- Porque, dependiendo de la situación o propósito del código, se necesita actualizar un dato dependiendo a lo que el usuario va diciendo, ó se necesita el dato tal cual cómo se veía cuando el código lo tomo, esto porque se trabaja con **Rvalores** y con **Lvalores**.
- #### 3. ¿Qué función desarrollan los :: en la implementación de la clase?
- [::] hace que la función que sea que se encuentre a la derecha solo se realice dentro de la función a la izquierda. Mientras que [:] lo hace global
- #### 4. ¿Cómo se le denomina a cuando una clase posee un operador puede tener múltiples implementaciones dependiendo de los argumentos que este reciba?
- Sobrecarga u *Overload*
- #### 5. ¿Cuál es la función del archivo .h ?
- Un header o archivo de encabezado es una librería extra que se usa para incluir declaraciones de variables, constantes, funciones y parámetros. Tambien sirve para agregar funciones extras.


## Parte 2

```C++
#include <iostream>
int algoritmo1(int n) {
	int resultado = 0;
	
	for (int i = 0; i < n; i++) 
	{
		resultado += i; // Operación simple O(1)
	}
	for (int i = 0; i < n; i++) 
	{
		for (int j = 0; j < n; j++) 
		{
			resultado += i * j; // Operación simple O(1)
		}
	}
	return resultado;
}
int main()	{
	int n;
	std::cout << "Ingrese el valor de n: ";
	std::cin >> n;
	int resultado = algoritmo1(n);
	std::cout << "Resultado: " << resultado << std::endl;
	return 0;
}
```
- Este código es de complejidad cuadrada $O(n^2)$. Pues hay un *for* anidado