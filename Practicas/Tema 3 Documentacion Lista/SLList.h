#ifndef SLLLIST_H
#define SLLLIST_H

#include <iostream>
#include <utility>

template <typename Object> //Se inicia con template para volverlo dinamico. Para que pueda usar cualquier tipo de dato
class SLList {
private:
    //Cada Cuadrito
    struct Node  {
        Object data; //Guarda los datos correspondientes
        Node *next;//Anya (Señala a que espacio ir despues)

        //Constructor por copia
        Node(const Object &d = Object{}, Node *n = nullptr)
                : data{d}, next{n} {}//Apunta a "n" con data de "d"

        //Constructor por referencia
        //Al recibir un nodo como parametro, cambia sus datos deta y next
        Node(Object &&d, Node *n = nullptr)
                : data{std::move(d)}, next{n} {}
    };

public:
    class iterator { //Declara la clase iterador
    public:
        iterator() : current{nullptr} {}//Se apunta el punter a nullptr para que no tenga la probabilidad de apuntar a algun lugar en donde ya hay informacion


        Object &operator*() { //Se declara un operador puntero
            if(current == nullptr) //Si el puntero tiene valor nulo, se
                //arroja un mensaje de error de logica
                throw std::logic_error("Trying to dereference a null pointer.");
            return current->data;//Si el puntero contiene algo se regresa
            //el objeto al que apunte
        }
        //Todo esto se encarga de mover el apuntador de la memoria
        iterator &operator++() {//Usa el ++ para desplazarse por la lista.
            //Este se usa para leer y moverse por los nodos.
            //Si existe un nodo siguiente, cambia el puntero actual al de este
            //nodo y lo regresa
            if(current)
                current = current->next;
            else //Si el puntero no tiene un siguiente nodo, se arroja un
                //error logico
                throw std::logic_error("Trying to increment past the end.");
            return *this;
        }

        iterator operator++(int) {//Por otra parte este solo lleva el conteo de del nodo en el que se encuentra
            iterator old = *this;
            ++(*this);//Este hace la operacion de sumar en si
            return old;
        }
        //Se declara el operador de igualdad (su uso pues)
        //Si los dos iteradores tienen el mismo apuntador, se regresa verdadero
        //de lo contrario se regresa falso
        bool operator==(const iterator &rhs) const {
            return current == rhs.current;
        }
        //Se declara el operador de desigualdad
        //Lo mismo que en el de igualdad pero al revez
        //Si ambos iteradores tienen el mismo apuntador al nodo, se regresa falso
        //De lo contrario, verdadero
        bool operator!=(const iterator &rhs) const {
            return !(*this == rhs);
        }

    private:
        Node *current; //Se guarda un puntero al nodo actual
        iterator(Node *p) : current{p} {} // Constructor. Se apunta a el
        //nodo que recibe como parametro
        friend class SLList<Object>;//Es una forma de decir que a los atributos privados solo puede acceder uno, y SLList
    };

public:
    SLList() : head(new Node()), tail(new Node()), theSize(0) {//Se define el inicio, el final y el tamaño de la lista
        head->next = tail;//Apunta el nodo de la cabeza al nodo cola
    }

    ~SLList() {
        clear();//Borra todos los elementos de la lista
        delete head;//Borra la informacion de la cabeza
        delete tail;//Borra la informacion de la cola
    }

    iterator begin() { return {head->next}; }//Regresa el principio de la
    //lista, el nodo de la cabeza

    iterator end() { return {tail}; }//Regresa el final de la lista
    //el nodo cola

    int size() const { return theSize; }//Regresa el tamaño de la lista
    bool empty() const { return size() == 0; }//Checa que la lista este vacia
    //y regresa true o false dependiendo de esto

    void clear() { while (!empty()) pop_front(); }//Si la lista no esta vacia, la va borrando hasta que lo este

    Object &front() {//Si la lista no esta vacia, arroja el primer valor, de otra forma suelta un error de logica aclarando que si esta vacia
        if(empty())
            throw std::logic_error("List is empty.");//Esto sirve para que nos demos cuenta si cometemos un error
        return *begin();
    }

    void push_front(const Object &x) { insert(begin(), x); }
    //Se introducen objetos al principio de la lista por copia (arriba) y
    // por referencia (abajo)
    void push_front(Object &&x) { insert(begin(), std::move(x)); }

    //Borra el primer elemento de la lista apuntando al frente con el metodo
    //begin.
    //Si la lista esta vacia, saca un error para aclarar que no hay nada ahi
    void pop_front() {
        if(empty())
            throw std::logic_error("List is empty.");
        erase(begin());
    }

    //Se inserta un nuevo elemento por copia a donde el apuntador esté
    //señalando
    //Se incrementa el tamaño de la lista +1
    //Y se regrasa el apuntador/iterador al nodo siguiente
    iterator insert(iterator itr, const Object &x) {
        Node *p = itr.current;
        head->next = new Node{x, head->next};
        theSize++;
        return iterator(head->next);
    }
    //Se inserta un nuevo elemento por referencia igual que arriba, solo que
    //aqui se usa el metodo "move"
    iterator insert(iterator itr, Object &&x) {
        Node *p = itr.current;
        head->next = new Node{std::move(x), head->next};
        theSize++;
        return iterator(head->next);
    }
    //Se borra el elemento en donde este el apuntador
    //Si se intenta borrar el iterador, se suelta un error logico
    //Una vez borrado se reduce el tamaño de la lista menos 1
    iterator erase(iterator itr) {
        if (itr == end())
            throw std::logic_error("Cannot erase at end iterator");
        Node *p = head;
        while (p->next != itr.current) p = p->next;
        p->next = itr.current->next;
        delete itr.current;
        theSize--;
        return iterator(p->next);
    }
    //Imprime la lista.
    //Usando el iterador va imprimiendo los contenidos de la lista
    void printList() {
        iterator itr = begin();
        while (itr != end()) {
            std::cout << *itr << " ";
            ++itr;
        }
        std::cout << std::endl;
    }

private:
    Node *head;//Donde inicia la lista
    Node *tail;//Donde finaliza la lista
    int theSize;//Tamaño de la lista
    void init() {
        theSize = 0;//Tamaño default de la lista
        head->next = tail;//En caso de que la lista este vacia el siguiente
        //elemento despues del inicio es la cola

    }
};

#endif
