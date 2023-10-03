//
// Created by Luigi on 9/19/2023.
//
#ifndef FLOATCELL_H
#define FLOATCELL_H //En estas dos lineas se checa que FLOATCELL_H ya exista y si no, se define.

class FloatCell {
public: //Todos los valores publicos (que se pueden ver y cambiar por quien sea)
    explicit FloatCell(float newValue = 0);//Constructor "explicit", se especifica que el nuevo valor tiene que ser un
    // flotante y se iguala a 0
    FloatCell(const FloatCell &rhs);
    FloatCell(FloatCell &&rhs) noexcept; //Las dos ultimas lineas son constructores implicitos, cubren dos posibilidades.
    // Una en la que lo que esta a la derecha del [=] es un RValor por lo cual no tiene espacio de memoria y la otra si
    // lo que esta a la derecha es una variable (o LValor). Esto se puede apreciar en los amperson pues en el caso de
    // la primera como es un RValor, solo se tiene que acceder a 1 cosa mientras que en la segunda se usan 2 porque
    // primero se accede a la direccion de memoria y luego a lo que hay dentro. Asi mismo [Const] solo se usa en la
    // primera para evitar que puedas cambiar el valor que vas a copiar
    ~FloatCell() = default; //El destructor, se iguala a default para deshacerse de
    //todo lo que este gastando memoria que se haya generado durante los pasos anteriores

    FloatCell &operator=(const FloatCell&rhs) ;
    FloatCell &operator=(FloatCell &&rhs) noexcept; //Aqui se le esta eseñando al operador que hacer en cualquiera de
    // los dos casos de arriba, que el valor a la derecha sea una constante o que sea una variable el primero por
    // referencia y el otro por copia (Por eso se usa el [const] en la primera)

    // Overloaded assignment operator to accept primitive float
    FloatCell &operator=(float rhs);//Se le dice al operador que puede usar datos de tipo float

    float getValue() const; //Permite mostrar el valor guardado en storedValue
    void setValue(float newValue);//Permite agregar el valor a storedValue

private:
    float storedValue;//Se crea una variable privada (que nadie puede ver o mover) y se crea una nueva variable donde
    // se va a guardar el valor que se introduzca
};

#endif  // FLOATCELL_H

