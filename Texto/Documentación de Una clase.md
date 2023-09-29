### IntCell.h

Este programa en si busca crear una clase que imite las propiedades de el tipo de variable "Int"

```
#ifndef INTCELL_H
#define INTCELL_H //En estas dos lineas se checa que INTCELL_H ya exista y si no, se define.

class IntCell {
public: //Todods los valores publicos (que se pueden ver y cambiar por quien sea)
    explicit IntCell(int newValue = 0);//Constructor "explicit", se especifica que el nuevo valor tiene que ser un entero y se iguala a 0
    IntCell(const IntCell &rhs); 
    IntCell(IntCell &&rhs) noexcept; //Las dos ultimas lineas son constructores implicitos, cubren dos posibilidades. Una en la que lo que esta a la derecha del [=] es un RValor por lo cual no tiene espacio de memoria y la otra si lo que esta a la derecha es una variable (o LValor). Esto se puede apreciar en los amperson pues en el caso de la primera como es un RValor, solo se tiene que acceder a 1 cosa mientras que en la segunda se usan 2 porque primero se accede a la direccion de memoria y luego a lo que hay dentro. Asi mismo "Const" solo se usa en la primera para evitar un caso donde se cambie el valor indicado y eso rompa lo que hicimos 
    ~IntCell() = default; //El destructor, se iguala a default para deshacerse de todo lo que este gastando memoria que se haya generado durante los pasos anteriores 

    IntCell &operator=(const IntCell &rhs); 
    IntCell &operator=(IntCell &&rhs) noexcept; //Al igual que arriba, se le dice al operador [=] que tipo de dato se puede usar, el primero por referencia y el otro por copia (Por eso se usa el const en la primera)

    // Overloaded assignment operator to accept primitive int
    IntCell &operator=(int rhs);//Se le dice al operador que puede usar datos de tipo entero (int)

    int getValue() const;
    void setValue(int newValue);//Se asignan nuevas (funciones? No tengo muy bien entendido que hace esto aparte de establecer espacios donde vamos a estar moviendo valores)

private:
    int storedValue;//Se crea una variable privada (que nadie puede ver o mover) y se crea una nueva variable donde se va a guardar el valor que se introduzca
};

#endif  // INTCELL_H
```
### IntCell.cpp

```
#include "IntCell.h" //Se incluye el .h para porder trabajar con el cuando se necesite

// Default constructor
IntCell::IntCell(int newValue) : storedValue(newValue) {}
//Constructor Implicito, se llama a la variable privada [storedValue] (no se que en particular es lo que permite cambiarla considerando que es privada) y se establece que el nuevo valor se va a guardar ahi

// Copy constructor
IntCell::IntCell(const IntCell &rhs) : storedValue(rhs.storedValue) {}//Copia el valor de la derecha de un operador a storedValue

// Move constructor
IntCell::IntCell(IntCell &&rhs) noexcept : storedValue(rhs.storedValue) { //Este constructor hace lo mismo que el de por copia pero es para Lvalores pues tiene 2 amperson para sacar el valor de algo que tenga direccion de memoria
   // rhs.storedValue = 0; //Se le asigna a [rhs.storedValue] un valor de 0 (Sin embargo creo que esto se supone que este comentado por las barras a la izquierda asi que no entiendo el punto de la linea)
}
// Copy assignment operator
IntCell &IntCell::operator=(const IntCell &rhs) {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
    }
    return *this;
}

// Remove Move assignment operator
IntCell &IntCell::operator=(IntCell &&rhs) noexcept {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0; //Si el valor de IntCell no es igual a lo que este a la derecha del operador, [storedValue] se iguala a [rhs.storedValue] (no entiendo bien la diferencia) y luego este ultimo se iguala a 0
    }
    return *this; //Se regresa el valor actual de IntCell
}

// Removed overloaded assignment operator to accept any data

// Overloaded assignment operator to accept only integer data
IntCell &IntCell::operator=(int rhs) { //Se especifica que solo se reconozca lo que este a la derecha del operador si es un tipo entero
    storedValue = rhs; //Se le asigna a storedValue el valor de lo quu este a la derecha del operador (en este caso [=])
    return *this; //Se regresa el valor de IntCell
}
```