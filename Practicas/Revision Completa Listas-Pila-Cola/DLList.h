//
// Created by Luigi on 10/30/2023.
//

#ifndef REVISION_COMPLETA_LISTAS_PILA_COLA_DLLIST_H
#define REVISION_COMPLETA_LISTAS_PILA_COLA_DLLIST_H


#include <iostream>
#include <utility>

template <typename Object>
class DLList{
private:
    struct Node  {
        Object data;
        Node *next;
        Node *prev;

        //Constructor de copia
        Node(const Object &d = Object{}, Node *n = nullptr, Node *p = nullptr)
                : data{d}, next{n}, prev{p} {}

        //Constructor de referencia
        Node(Object &&d, Node *n = nullptr, Node *p = nullptr)
                : data{std::move(d)}, next{n}, prev{p} {}
    };

public:
    class iterator{
    public:
        //Constructor implicito, se hace nulo el puntero
        iterator() : current{nullptr} {}

        //Define * para que se comporte como puntero
        Object &operator*() {

        //Si el nodo actual es igual a nulo (si escribiste un valor no valido) saca error
            if(current == nullptr)
                throw std::logic_error("Trying to dereference a null pointer.");
            return current->data;
        }

        //Movimiento
        //Operador hace que pueda moverse por la lista.
        //Si existe el current nos vamos al siguiente, de lo contrario saca error.
        //Lo compara al "default" que tiene 3 datos, y si solo tiene 2 saca error, el primero caeria en este caso
        //pero funciona diferente
        iterator &operator++() {
            if(current)
                current = current->next;
            else
                throw std::logic_error("Trying to increment past the end.");
            return *this;
            //*this ahorra memoria y en este caso usa el último valor que se uso en la funcion (current)
        }
        //Como moverse
        iterator operator++(int) {
        //En este caso *this agarra el valor de el current viejo (el nodo que quieres dejar atras)

            iterator old = *this;
            ++(*this);
            return old;
        }

        //Todo lo que esta acontinuacion con [--] es lo mismo que lo que hicimos arriba para [++]
        //pero ponerlo con [--] es lo que nos ayuda a volver la lista una de doble enlace pues nos permite
        //hacernos para atras
        //Una lista simple solo tienes caminos para adelante mientras que una doble tiene doble sentido

        iterator &operator--() {
            if(current)
                current = current->prev;
            else
                throw std::logic_error("Trying to decrease past the beginning.");
            return *this;
        }

        iterator operator--(int) {
            iterator old = *this;
            --(*this);
            return old;
        }
        //Es para decirle al programa que hacer cuando solo hay un simbolo [+]
        //Es para moverse
        iterator &operator+(int addition){

            for(int i = 0; i<addition;i++){
                ++(*this);
            }
            return  *this;
        }

        //Operadores para realizar comparaciones
        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }
        //Aquí se hace un doble negativo, si son iguales, se regresa que la desigualdad es falsa
        //te dice que "no son desiguales (osea, son iguales)
        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }

    protected:
        //Apunta al nodo al que estoy trabajando en ese momento
        //Debido a como esta declarado, current siempre se compara como su direccion de memoria
        Node *current;
        iterator(Node *p) : current{p} {}
        //da acceso a los atributos privados, se ve inutil pero nos permite restringir acceso a posibles librerias
        //que incorporemos en el futuro
        friend class DLList<Object>;

        Object & retrieve() const{
            return current->data;
        }
    };

public:
    //Define la dimension de la lista
    //Cuando se llame al constructor, ya tiene que estar establecida una cabeza y una cola
    DLList() {
        init();
    }

    //Destructor de la lista
    //Primero borra el contenido y despues la cola y la cabeza
    ~DLList() {
    //~DLList es el destructor, mientras que [clear();] es una funcion dentro de este
        clear();
        delete head;
        delete tail;
    }

    //Establece dos iteradores al principio (head) y al final (tail). En el caso de al principio, regresa el espacio de
    //memoria de [head] y aparte el siguiente nodo
    iterator begin() { return {head->next}; }
    iterator end() { return {tail}; }

    //Se regresa el tamaño de la lista, para que un iterador sepa cuanto debe recorrer
    int size() const { return theSize; }
    bool empty() const { return size() == 0; }

    //Si no esta vacia, borra el objeto al frente de la lista
    void clear() { while (!empty()) pop_front(); }

    //Si la lista esta vacia da un error, si no regresa al inicio
    //No se que hace el amperson aqui
    Object &front() {
        if(empty())
            throw std::logic_error("List is empty.");
        return *begin();
    }

    //Funcion de pushfront por copia
    //Por copia ( si le pasa algo al valor original, afecta el valor tomado), solo toma constantes
    //Por ejemplo solo toma algo como un valor simple como [15]
    void push_front(const Object &x) {
        insert(begin(), x);
    }
    //Funcion de pushfront por referencia
    //Por referencia (toma el valor como propio y borra el espacio de memoria donde estaba antes)
    //Pasa cuando se introducen variables como seria [Valor1]
    void push_front(Object &&x) {
        insert(begin(), std::move(x));
    }
    //Pushback por copia
    void push_back(const Object &x) {
        insert(end(), x);
    }
    //Funcion de pushback por referencia
    void push_back(Object &&x) {
        insert(end(), std::move(x));
    }

    //Elimina el valor de en frente de la lista
    //Si la lista esta vacia arroja un error
    void pop_front() {
        if(empty())
            throw std::logic_error("List is empty.");
        erase(begin());
    }

    //Recibe un iterador, lee esa posicion e inserta un código en la posicion que le demos
    //Este funciona por copia
    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.current;
        theSize++;
        return {p->prev = p->prev->next = new Node{x, p, p->prev}};
    }

    //Insert por referencia
    iterator insert(iterator itr, Object &&x) {
        Node *p = itr.current;
        theSize++;
        return {p->prev = p->prev->next = new Node{std::move(x), p, p->prev}};
    }
//Funcion insert
//Toma una posicion donde queremos que se inserte y una constante
//Se necesista un iterador y se manda la posicion como parametro
//Basicamente se usa cuando se da un numero en vez de un iterador y lo traduce
    void insert(int pos, const Object &x) {
        insert(get_iterator(pos), x);
    }
//Con un for se suma al itr hasta que sea igual al [int] que el usuario introdujo
    iterator get_iterator(int a)
    {
        //Crea el iterador y lo posisciona en el principio de la lista
        iterator it = begin();
        for(int i = 0; i != a; ++i) {//Repite mientras que sea diferente a [a]
            ++it;
        }
        return it;
    }

    //Recibe un iterador (en forma de int que luego se traduce a itr) y borra el dato en la posicion que le digamos
    iterator erase(iterator itr) {

    //Si el valor de itr es igual al final de la lista, suelta un error de logica
        if (itr == end())
            throw std::logic_error("Cannot erase at end iterator");
        Node *p = itr.current;
        iterator returnValue(p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        //Se borra el itr que puso el usuario
        delete p;
        //Se le resta uno al tamaño de la lista
        theSize--;
        //Se regresa el nodo siguiente
        return returnValue;
    }

//Basicamente el traductor de int a itr
//Se le habla a la funcion erase, pasando como parametro la funcion get iterator con [pos] como parametro
//Osea que se manda [pos] como lo que queremos que se tradusca a itr
    void erase(int pos)
    {
        erase(get_iterator(pos));
    }

    //Getter para toda la lista
    //(Imprime la lista)
    void print() {

        //Se establece que [itr] empieza en el principio (la cabeza)
        iterator itr = begin();

        //Mientras qeu itr sea diferente del final (la cola) se realiza lo de adentro
        while (itr != end()) {

        //Como itr ya esta declarado como puntero desde el principio, otro [*] hace que se saque el valor
        //dentro del espacio de memoria
            std::cout << *itr << " ";
            ++itr;
        }
        std::cout << std::endl;
    }


protected:
    Node *head;
    Node *tail;
    int theSize;

    //init necesita acceso a los datos privados para inicializar una lista vacia
    void init() {
        head = new Node;
        tail = new Node;
        theSize = 0;

        head->next = tail;
        head->prev = nullptr;

        tail->prev = head;
        tail->next = nullptr;
    }


};


#endif //REVISION_COMPLETA_LISTAS_PILA_COLA_DLLIST_H
