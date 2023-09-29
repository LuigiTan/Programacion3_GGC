#ifndef DOUBLE_CELL_H
#define DOUBLE_CELL_H

class DoubleCell {
public:
    // Default constructor
    DoubleCell();
    // Constructor with value
    explicit DoubleCell(double value);//Declara DoubleCell con un valor tipo double

    // Copy constructor
    DoubleCell(const DoubleCell &other);

    //Reference constructor
    DoubleCell (DoubleCell &&other) noexcept;
    // Destructor
    ~DoubleCell() = default;//Se igualan los valores usados a default para que no generen
    //problemas después

    // Assignment operator by copy
    DoubleCell &operator=(const DoubleCell &other);
    // Assignment operator by reference
    DoubleCell &operator=(DoubleCell &&other) noexcept;

    // Assignment operator for double
    DoubleCell &operator=(double value);

    // Arithmetic operators
    DoubleCell operator +(const DoubleCell& other) const;
    DoubleCell operator +(const double other) const;
    DoubleCell operator -(const DoubleCell& other) const;
    DoubleCell operator -(const double other) const;
    DoubleCell operator *(const DoubleCell& other) const;
    DoubleCell operator *(const double other) const;
    DoubleCell operator /(const DoubleCell& other) const;
    DoubleCell operator /(const double other) const;
    //Se establece que debe de hacer la clase con diferentes operaciones tanto en caso de
    //un RValor como en el caso de un LValor

    // Setters
    void SetValue(double); //Se declara SetValue como void porque no debe de regresar nada
    // Getters

       double GetValue() const;

private:
    double Storedvalue;
};

#endif  // DOUBLE_CELL_H
