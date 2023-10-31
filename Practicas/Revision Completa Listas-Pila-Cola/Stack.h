//
// Created by Luigi on 10/30/2023.
//

#ifndef REVISION_COMPLETA_LISTAS_PILA_COLA_STACK_H
#define REVISION_COMPLETA_LISTAS_PILA_COLA_STACK_H
#include <iostream>
#include <cstdlib>
#include <stack>

template <typename StData>
class Stack : private DLList<StData> {//Crea la clase "Stack" que hereda DLList con los datos de [StData]
public:
    Stack() {
        DLList<StData>::init();
        //Inicializa Stack en [init] declarado en DLList
    }

    ~Stack(){
        //El destructor le habla a la funcion clear
        clear();
        //Borra la head
        delete DLList<StData>::head;
        //Borra la tail (el final del stack)
        delete DLList<StData>::tail;
    }

    void push(StData &data){
        //Inserta StData al principio del Stack por copia
        DLList<StData>::push_front(data);
    }
    void push(StData &&data){
        //Inserta StData al principio del Stack por referencia
        DLList<StData>::push_front(data);
    }

    void pop(){
        //Borra StData al principio del Stack
        DLList<StData>::pop_front();
    }

    void clear(){
        //Usa la funcion dentro de DLList para borrar StData
        DLList<StData>::clear();
    }

    void print(){
        //Imprime el Stack
        DLList<StData>::print();
    }

    StData top(){
        //Imprime solamente el primer valor
        return DLList<StData>::head->next->data;
    }
};

#endif //REVISION_COMPLETA_LISTAS_PILA_COLA_STACK_H
