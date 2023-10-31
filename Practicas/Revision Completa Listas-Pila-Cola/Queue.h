//
// Created by Luigi on 10/30/2023.
//

#ifndef REVISION_COMPLETA_LISTAS_PILA_COLA_QUEUE_H
#define REVISION_COMPLETA_LISTAS_PILA_COLA_QUEUE_H


template<typename QData>
class Queue : private DLList<QData>{//Crea la clase "Queue" que hereda DLList con los datos de [QData]
public:
    Queue(){
        DLList<QData>::init();
        //Inicializa Queue en [init] declarado en DLList
    }

    ~Queue(){
        //El destructor le habla a la funcion clear
        clear();
        //Borra la head
        delete DLList<QData>::head;
        //Borra la tail (el final de la queue)
        delete DLList<QData>::tail;
    }

    void enqueue(QData &data){
        //Inserta QData al final de la Queue por copia
        DLList<QData>::push_back(data);
    }

    void enqueue(QData &&data){
        //Inserta QData al final de la Queue por referencia
        DLList<QData>::push_back(data);
    }

    void dequeue(){
        //Borra QData al principio de la Queue
        DLList<QData>::pop_front();
    }

    void print(){
        //Imprime la cola (la queue)
        DLList<QData>::print();
    }

    void clear(){
        //Usa la funcion dentro de DLList para borrar QData
        DLList<QData>::clear();
    }

    QData front(){
        //Imprime el primer valor de la Queue
        return DLList<QData>::head->next->data;
    }
};

#endif //REVISION_COMPLETA_LISTAS_PILA_COLA_QUEUE_H
