//
// Created by Luigi on 9/19/2023.
//
#ifndef TEMA_1_FLOATCELL_H
#define TEMA_1_FLOATCELL_H

class FloatCell {
    public:
    explicit  FloatCell(float value = 0);
    FloatCell(const FloatCell &rhs);
    FloatCell(FloatCell &&rhs) noexcept;
    ~FloatCell()= default; //Esto es un destructor, sirve para que no este
    //abarcando memoria
    //Los Rvalores son numeros fijos que no tienen direccion de memoria
    //Los LValores si tienen una direccion de memoria
    //Las constantes (const) son diferentes, pues si tienen una direccion
    //de memoria, pero no se pueden cambiar dentro del codigo
    //Los :: significan dentro del scope, la funcion solamente dentro de
    //la clase especificada
    FloatCell &operator=(const FloatCell &rhs);
    FloatCell &operator=(FloatCell &&rhs) noexcept;

    FloatCell &operator = (int rhs);

    int getValue() const;
    void setValue(int newValue);

private:
    int storedValue;


    //Un getter se usa para obtener el valor que esta guardando una
    //variable
};


#endif //TEMA_1_FLOATCELL_H
