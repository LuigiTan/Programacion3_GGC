# Lista enlazada

```C++
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
            //el objeto al que apunte        }  
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
  
	//Borra el primer elemento de la lista apuntando al frente con el metodo begin.
	//Si la lista esta vacia, saca un error para aclarar que no hay nada ahi
	void pop_front() {  
        if(empty())  
            throw std::logic_error("List is empty.");  
        erase(begin());  
    }  
  
    //Se inserta un nuevo elemento por copia a donde el apuntador estés señalando
    //Se incrementa el tamaño de la lista +1
    //Y se regrasa el apuntador/iterador al nodo siguiente    
    iterator insert(iterator itr, const Object &x) {  
        Node *p = itr.current;  
        head->next = new Node{x, head->next};  
        theSize++;  
        return iterator(head->next);  
    }  
    //Se inserta un nuevo elemento por referencia igual que arriba, solo que aqui se usa el metodo "move"
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
    void print() {  
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
```


# Lista Doblemente enlazada

```C++
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
        //Lo compara al "default" que tiene 3 datos, y si solo tiene 2 saca error, el primero caeria en este caso pero funciona diferente
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
        //pero ponerlo con [--] es lo que nos ayuda a volver la lista una de doble enlace pues nos permite hacernos para atras
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
        //da acceso a los atributos privados, se ve inutil pero nos permite restringir acceso a posibles libreriasq que incorporemos en el futuro
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
  
    //Establece dos iteradores al principio (head) y al final (tail). En el caso de al principio, regresa el espacio de memoria de [head] y aparte el siguiente nodo
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
  
        //Como itr ya esta declarado como puntero desde el principio, otro [*] hace que se saque el valor dentro del espacio de memoria
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
```

# Pila

```C++
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
```

# Cola

```C++
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
```



### Dudas

Si bien el concepto y diferencias de concepto entre una Pila y una Cola me quedaron claros (aunque siendo honesto seguido confundo los nombres en español e incluso luego me hago bolas con los nombres en ingles) sus usos particulares en juegos me eluden un poco.
Pero sobre eso creo que la duda mas grande que me quedo (aparte de varios aspectos de código de las listas en si) es que según varios compañeros, la lista doblemente enlazada que hicimos originalmente, estaba mal, me explicaron porque pero no entiendo para nada como es que lograron arreglarla.







