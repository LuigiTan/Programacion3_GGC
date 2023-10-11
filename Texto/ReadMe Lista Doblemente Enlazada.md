A continuación se presenta la documentación de el Template DLList. El cual sirve para hacer una Lista doblemente enlazada

```C++
template <typename Object>  
  
class DLList {  
private:  
    struct Node{  
        Node *prev;  
        Object data;  
        Node *next;  
  
        //Constructor por copia  
        Node(const Object &d = Object{}, Node *n = nullptr)  
                :data{d}, next{n}, prev{n} {}  
  
        //Constructor por referencia  
        Node(Object &&d, Node *n = nullptr)  
            : data{std::move(d)}, next {n}, prev{n}{}  
    };//final struct node  
public:  
    class iterator{  
    public:  
        //Constructor implicito, se hace nulo el puntero  
        iterator() : current{nullptr} {}  
  
        // define * como puntero  
        Object &operator * (){  
        //Si el nodo actual es igual a nulo (si escribiste un valor no valido) saca error  
            if (current == nullptr)  
                throw std::logic_error("");  
            return current -> data;  
        }  
        //Enseña como moverse por la lista [Que hacer]  
        iterator &operator++() {  
        //Si existe el current nos vamos al siguiente, de lo contrario saca error  
        //Lo compara al "default" que tiene 3 datos, y si solo tiene 2 saca error, el primero caeria en este caso        //pero funciona diferente            if(current)  
                current = current -> next;  
            else  
                throw std::logic_error("Trying to increment past the end.");  
            //*this ahorra memoria y en este caso usa el último valor que se uso en la funcion (current)  
            return *this;  
        }  
        //[Como moverse]  
        iterator &operator++(int){  
            //En este caso *this agarra el valor de el current viejo (el nodo que quieres dejar atras)  
            iterator old = *this;  
            //Incrementa los valores de los 3 valores de current  
            ++(*this);  
            return old;  
        }  
        //Todo lo que esta acontinuacion con [--] es lo mismo que lo que hicimos arriba para [++]  
        //pero ponerlo con [--] es lo que nos ayuda a volver la lista una de doble enlace pues nos enabilita  
        //hacernos para atras        //Una lista simple solo tienes caminos para adelante mientras que una doble tiene soble sentido        iterator &operator--() {  
            if(current)  
                current = current->prev;  
            else  
                throw std::logic_error("Trying to decrease past the beginning.");  
            return this;  
        }  
        iterator operator--(int) {  
            iterator old =this;  
            --(*this);  
            return old;  
        }  
        //Compara las direcciones de memoria y dependiendo de si son iguales regresa true, si no false  
        bool operator == (const iterator &rhs) const {  
            return current == rhs.current;  
        }  
  
        //Aquí se hace un doble negativo, si son iguales, se regresa que la desigualdad es falsa  
        //te dice que "no son desiguales (osea, son iguales)        bool operator != (const iterator &rhs) const {  
            return !(*this == rhs);  
        }  
        //Fin de atributos publicos  
    private:  
        //Apunta al nodo al que estoy trabajando en ese momento  
        //Debido a como esta declarado, current siempre se compara como su direccion de memoria        Node *current;  
        iterator(Node *p) : current{p}{}  
        //da acceso a los atributos privados, se ve inutil pero nos permite restringir acceso a posibles librerias  
        //que incorporemos en el futuro        friend class DLList<Object>;  
        //fin atributos privados  
    }; //fin iterator  
public: //Valores públicos  
  
    //Define la dimension de la lista    //Cuando se llame al constructor ya tiene que estar establecida una caberza y una cola    //Es un constructor pues    DLList() : head(new Node()), tail(new Node()), theSize(0) {  
        head->next = tail;  
    }  
  
    //Destructor de la lista  
    //Primero borra el contenido y despues la cola y la cabeza    ~DLList() {  
        //~DLList es el destructor, mientras que [clear();] es una funcion dentro de este  
        clear();  
        delete head;  
        delete tail;  
    }  
    //Estrablece dos iteradores al principio (head) y al final (tail). En el caso de al principio, regresa el espacio de  
    //memoria de [head] y aparte el siguiente nodo    iterator begin() { return {head -> next}; }  
    iterator end() {return {tail};}  
    //Se regresa el tamaño de la lista, para que el iterador sepa cuando  
    //debe recorrer    int size() const {return theSize; }  
    bool empty() const { return size() == 0; }  
  
    //Si no esta vacia, borra el objeto al frente de la lista  
    void clear() { while (!empty()) pop_front(); }  
  
    //Si la lista esta vacia, arroja un error, de otra forma regresa al inicio  
    //No se muy bien que hacer el amperson en este caso    Object &front() {  
        if (empty())  
            throw std::logic_error("List is empty.");  
        return *begin();  
    }  
  
    //Funciones de push  
    //Aqui se hace push al frente de la lista    //Por copia ( si le pasa algo al valor original, afecta el valor tomado), solo toma constantes    //Por ejemplo solo toma algo como un valor simple como [15]    void push_front(const Object &x) { insert (begin(), x) ;}  
    //Por referencia (toma el valor como propio y borra el espacio de memoria donde estaba antes)  
    //Pasa cuando se introducen variables como seria [Valor1]    void push_front(Object &&x) {insert (begin(), std::move(x)); }  
  
    //Funciones de push pero ahora con back, osea se introducen al final de la lista  
    void push_back(const Object &x) { insert(end(), x); }  
    void push_back(Object &&x) { insert(end(), std::move(x)); }  
  
  
    //Elimina el valor que hay en frente de la lista  
    //Si la lista esta vacia arroja un error    void pop_front() {  
        if(empty())  
            throw std::logic_error("List is empty.");  
        erase(begin());  
    }  
  
    //Recibe un iterador, lee esa posicion e inserta un valor en la posicion dada  
    //Esto es con copia    iterator insert(iterator itr, const Object &x) {  
        Node *p = itr.current;  
        head ->next = new Node{x, head->next};//El segundo head->next no estoy seguro que hace  
        theSize++;  
        return iterator(head -> next);  
    }  
  
    //Aqui se hace con referencia  
    iterator isert(iterator itr, Object &&x) {  
        Node *p = itr.current;  
        head->next = new Node{std::move(x), head->next};  
        theSize++;  
        return iterator(head->next);  
    }  
  
    //Funcion insert  
    //Toma una posicion donde queremos que se inserte y una constante    //Se necesista un iterador y se manda la posicion como paramatro    //Baciamente se usa cuando se da un numero en vez de un iterador y lo traduce    void insert(int pos, const Object &x) {  
        insert(get_iterator(pos), x);  
    }  
  
    //Crea el iterador y lo posiciona en begin()  
    iterator get_iterator(int a)  
    {  
        //Con un for se suma al itr hasta que sea igual al [int] que el usuario introdujo  
        iterator itr = begin();  
        for(int i = 0; i != a; ++i) {//No entiendo porque aqui es [!=] cuando se deberia de sumar y repetir el for  
            //hasta que [i] se vuelva igual a            ++itr;  
        }  
        return itr;  
    }  
  
    //Recibe un iterador dado por el usuario (en forma de int que luego se traduce a itr)  
    //Y borra el dato en la posicion dada    iterator erase(iterator itr) {  
        //Si el valor de itr es igual al final de la lista, suelta un error de logica  
        if (itr == end())  
            throw std::logic_error("Cannot erase at end iterator");  
        //El nodo llamado p, empieza desde el espacio de memoria de la cabeza  
        Node *p = head;  
        //Mientras que el siguiente nodo de p sea diferente al nodo que el usuario establecio que quiere borrar  
        //p avanza al siguiente nodo hasta volverse el nodo que el usuario quiere borrar        while (p->next != itr.current)  
        {  
            p = p->next;  
        }  
        //El siguiente de p se vuelve el siguiente al nodo que el usuario quiere quitar  
        //(osea que estan en la misma posicion)        p->next = itr.current->next;  
        //Se borra el itr actual (el que puso el usuario)  
        delete itr.current;  
        //Se le resta uno al tamaño de la lista  
        theSize--;  
        //Se regresa el nodo siguiente a p  
        return iterator(p->next);  
    }  
//Basicamente el traductor de int a itr  
//Se le habla a la funcion erase, pasando como parametro la funcion get iterator con [pos] como parametro  
//Osea que se manda [pos] como lo que queremos que se tradusca a itr  
    void erase(int pos)  
    {  
        erase(get_iterator(pos));  
    }  
  
    //Imprime la lista  
    void print() {  
        //Se establece que [itr] empieza en el principio (la cabeza)  
        iterator itr = begin();  
        //Mientras qeu itr sea diferente del final (la cola) se realiza lo de adentro  
        while (itr != end()) {  
            //Como itr ya esta declarado como puntero desde el principio, otro [*] hace que se saque el valor  
            //dentro del espacio de memoria            std::cout << *itr << " ";  
            ++itr;  
        }  
        std::cout << std::endl;  
    }  
  
private:  
    Node *head;  
    Node *tail;  
    int theSize;  
    //init necesita acceso a los datos privados para inicializar una lista vacia  
    void init() {  
        theSize = 0;  
        head->next = tail;  
    }  
};//final lista

```