#include "DoubleCell.h"
#include <stdexcept>

// Default constructor
DoubleCell::DoubleCell()
    :Storedvalue(0.0){}

// Constructor with value
DoubleCell::DoubleCell(double value)
    : Storedvalue(value){}

// Copy constructor
DoubleCell::DoubleCell(const DoubleCell &other)
    : Storedvalue(other.Storedvalue){}

//Reference  constructor
DoubleCell::DoubleCell(DoubleCell &&other) noexcept
        : Storedvalue(other.Storedvalue){}


// Destructor
   //El destructor ya está en el .h

// Assignment operator by copy
DoubleCell &DoubleCell::operator=(const DoubleCell &other){
    if (this != &other){
        Storedvalue = other.Storedvalue;
    }
    //Se copia la información del valor a la derecha en Stored value
    return *this;//Y se regresa el valor en DoubleCell
}

// Assignment operator by reference
DoubleCell& DoubleCell::operator=(DoubleCell&& other) noexcept
{
    if (this != &other)//Se saca la referencia de lo que este a la
        //derecha (other) del simbolo igual y se guarda en Storedvalue
    {
        Storedvalue = other.Storedvalue;
        other.Storedvalue = 0;
    }
    return *this;
}

// Assignment operator for double
DoubleCell& DoubleCell::operator=(double value){ //Se le asigna valor a StoredValue
            Storedvalue = value;
            return *this;
}

// Arithmetic operators
//DoubleCell adding
DoubleCell DoubleCell::operator +(const DoubleCell& other) const{//Se establece una copia del valor de la derecha (other)
    //se tiene que sumar a Storedvalue
    return DoubleCell(Storedvalue + other.Storedvalue);
}

//primitive double adding
DoubleCell DoubleCell::operator +(double value) const {//Se suma el valor directo de value a Storedvalue
    return DoubleCell(Storedvalue + value);
}
//DoubleCell substracting
DoubleCell DoubleCell::operator -(const DoubleCell& other) const {//Lo mismo que en DoubleCell adding
    return DoubleCell(Storedvalue - other.Storedvalue);//pero con resta
}
//primitive double substracting
DoubleCell DoubleCell::operator -(double value) const{
    return DoubleCell(Storedvalue - value);//Lo mismo que en primitive double adding pero con resta
}

//DoubleCell multiplication
    DoubleCell DoubleCell::operator *(const DoubleCell& other) const{//Lo mismo que en DoubleCell adding
        return DoubleCell(Storedvalue * other.Storedvalue);//pero con multiplication
}

//primitive double multiplication
    DoubleCell DoubleCell::operator *(double value) const {//Lo mismo que en primitive double adding
    return DoubleCell(Storedvalue * value); //pero con multiplication
}
//DoubleCell division
DoubleCell DoubleCell::operator /(const DoubleCell& other) const{//Lo mismo que en las operaciones anteriores con referencia
    //pero con division
    if(other.Storedvalue == 0){//Sin embargo, aquí antes de regresar el resultado de la operacion, se espcifica que si
        //el valor a la derecha de la division es 0, no haga la operacion y solo muestre un mensaje de clarificacion,
        //pues no se puede dividir entre 0
        throw std::invalid_argument("Division by zero");
    }
    return DoubleCell(Storedvalue / other.Storedvalue);
}

//Primitive double division
DoubleCell DoubleCell::operator /(double value) const{//Lo mismo que en la division de arriba, pero aquí se cubre el caso
    if(value == 0){//de usar el valor directo para dividir. Al igual que arriba, se cubre el caso de division entre 0
        throw std::invalid_argument("Division by zero");
    }
    return DoubleCell(Storedvalue / value);
}

// Setters
void DoubleCell::SetValue(double value)
{
            Storedvalue = value;
}

// Getters
double DoubleCell::GetValue() const
{
    return Storedvalue;
}
