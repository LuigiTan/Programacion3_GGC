#include "FloatCell.h" //Se incluye el .h para porder trabajar con el cuando se necesite

// Default constructor
FloatCell::FloatCell(float newValue) : storedValue(newValue) {}
//Constructor Implicito, se llama a la variable privada [storedValue] (no se que en particular es lo que permite cambiarla considerando que es privada) y se establece que el nuevo valor se va a guardar ahi

// Copy constructor
FloatCell::FloatCell(const FloatCell &rhs) : storedValue(rhs.storedValue) {}//Copia el valor de la derecha de un operador a storedValue

// Move constructor
FloatCell::FloatCell(FloatCell &&rhs) noexcept : storedValue(rhs.storedValue) { //Este constructor hace lo mismo que el de por copia pero es para Lvalores pues tiene 2 amperson para sacar el valor de algo que tenga direccion de memoria
    // rhs.storedValue = 0; //Se le asigna a [rhs.storedValue] un valor de 0 (Sin embargo creo que esto se supone que este comentado por las barras a la izquierda asi que no entiendo el punto de la linea)
}
// Copy assignment operator
FloatCell &FloatCell::operator=(const FloatCell &rhs) {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
    }
    return *this;
}

// Remove Move assignment operator
FloatCell &FloatCell::operator=(FloatCell &&rhs) noexcept {
    if (this != &rhs) {
        storedValue = rhs.storedValue;
        rhs.storedValue = 0; //Si el valor de FloatCell no es igual a lo que este a la derecha del operador, [storedValue] se iguala a [rhs.storedValue] (no entiendo bien la diferencia) y luego este ultimo se iguala a 0
    }
    return *this; //Se regresa el valor actual de FloatCell
}

// Removed overloaded assignment operator to accept any data

// Overloaded assignment operator to accept only float data
FloatCell &FloatCell::operator=(float rhs) { //Se especifica que solo se reconozca lo que este a la derecha del operador si es un tipo flotante
    storedValue = rhs; //Se le asigna a storedValue el valor de lo que este a la derecha del operador (en este caso [=])
    return *this; //Se regresa el valor de FloatCell
}