# Examen 1 programación 3

# Examen de Programación 3

## Parte 1

Para la realización de este examen tendrán que Subir en `Classroom` un archivo `README.md` con las respuestas a las indicaciones, preguntas y calculos que se tengan que hacer en el siguiente examen. Para la entrega del código corregido tendrán que subirlo a su **Repositorio de GitHub** en una carpeta que tenga el nombre: <span style="color: #ff7600; ">Examen</span> Tendrán un lapso de 12 horas a partir de la publicación del espacio correspondiente en classroom.

### Creación de Clases

En este repositorio de [GitHub](https://github.com/BiomedicLJZ/Examen/tree/master/Examen_Programacion_3) cuentan con los archivos `.h` y `.cpp` de una clase, estos archivos están incompletos ya que les hace falta una serie de lineas críticas para su funcionamiento, su trabajo en este examen será hacer funcionar el archivo `main.cpp` utilizando la documentación disponible, **apuntes y conocimientos previos** para ello deberán:

1. Reparar el archivo de Interfaz `.h`
2. Reparar el archivo de implementación `.cpp`
3. Hacer funcionar el archivo `main.cpp`

## Parte 1.1

4. Responde a las siguientes preguntas:
   1. ¿Qué es un Rvalor y un Lvalor?
   2. ¿Porqué es necesario que una clase tenga constructores y operadores por **copia** y por **referencia**?
   3. ¿Qué función desarrollan los `::` en la implementación de la clase?
   4. ¿Cómo se le denomina a cuando una clase posee un operador puede tener múltiples implementaciones dependiendo de los argumentos que este reciba?
   5. ¿Cúal es la funcion del archivo `.h`?

## Parte 2

### Complejidad Temporal

Calcular la complejidad temporal en **Big(O) Notation** del siguiente algoritmo:

```cpp
#include <iostream>

int algoritmo1(int n) {
    int resultado = 0;

    for (int i = 0; i < n; i++) {
        resultado += i; // Operación simple O(1)
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            resultado += i * j; // Operación simple O(1)
        }
    }

    return resultado;
}

int main() {
    int n;
    std::cout << "Ingrese el valor de n: ";
    std::cin >> n;

    int resultado = algoritmo1(n);
    std::cout << "Resultado: " << resultado << std::endl;

    return 0;
}

```
