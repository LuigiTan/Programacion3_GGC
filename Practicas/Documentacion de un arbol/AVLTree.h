#ifndef AVL_TREE_H
#define AVL_TREE_H

#include<iostream>
#include<iomanip>
#include<algorithm>
#include<memory>//Obtiene la direccion real de un objeto

//Crea un template para poder trabajar con cualquier valor (este es para el nodo)
template <typename T>
class Node {
public:
    //La informacion que el nodo correspondiente va a guardar, como se vio arriba, se inicializa como tipo template para que pueda guardar
    //todo tipo de datos

    //Aqui se va a guardar la informacion del nodo
    T data;
    //Se inicializa la altura como tipo int y aqui guardarse
    int height;
    std::shared_ptr<Node<T>> left; //Puntero inteligente compartido para apuntar al nodo izquierdo
    std::shared_ptr<Node<T>> right; //Puntero inteligente compartido para apuntar al nodo derecho

    //Constructor de los nodos
    //Recibe [data] y lo guarda en la variable llamada tambien {data}
    //El resto de valores son lo que ahora sera el default
    Node(T data) : data(data), height(1), left(nullptr), right(nullptr) {}
};

//Template ahora para que el arbol pueda recibir cualquier dato
template <typename T>

//Clase principal
class AVLTree {
public:
    //Un puntero que permite que otros punteros apunten a diferentes lugares
    //Es un puntero inteligente que ahora apunta al nodo raiz
    std::shared_ptr<Node<T>> root;

    //Constructor (implicito?) que ahora guarda el puntero raiz como nulo
    AVLTree(): root(nullptr) {}

    //Funcion para agregar nodo
    //Recibe la informacion que se debe insertar como parametro
    void add(T data) {

    //Llama a insertar para poner el nodo en su posicion
        root = insert(root, data);
    }

    //Funcion para eliminar un nodo
    //Recibe la informacion dada de un nodo, la cual se usara para buscar y borrar ese mismo
    void remove(T data)  {

    //Llama al metodo de borrar nodo pasandole informacion de la raiz y la data del nodo a borrar para buscarlo
        root = deleteNode(root, data);
    }

    //Imprimir el arbol
    void print() {
        if (root != nullptr) {

        //Si el puntero de la raiz no es nulo, significa que el arbol no esta vacio asi que lo imprime
            print(root, 0);
        //En el caso de que si sea nulo, manda un mensaje de error
        } else {
            std::cout << "The tree is empty." << std::endl;
        }
    }

private:
    //Funcion para imprimir (parece ser recursiva)
    //El indent es algo que se usa para darle forma al arbol, es basicamente la sangria del texto
    //Empieza siendo 0 asi que el +8 es para que se mueva 8 espacios el texto cada que se
    //le vuelve a llamar
    /*
    Texto1
                Texto2
                            Texto3
     */

    void print(std::shared_ptr<Node<T>> node, int indent) {
        if(node) {
            //Checa si el nodo tiene un hijo a la derecha y se mueve hacia alla
            if(node->right) {
            //Imprime el nodo a la derecha
                print(node->right, indent + 8);
            }
            //Checa si [indent] tiene un valor y asigna eso como la width (quiere decir setwidth)
            if (indent) {
                std::cout << std::setw(indent) << ' ';
            }
            //Imprime el camino derecho del arbol

            if (node->right) {
                std::cout << " / (Right of " << node->data << ")\n" << std::setw(indent) << ' ';
            }
            std::cout << node->data << "\n" ;
            //Checa si el nodo tiene un hijo a la izquierda
            //Si si lo tiene, se mueve y lo imprime igual que arriba para el derecho
            if (node->left) {
                std::cout << std::setw(indent) << ' ' << " \\ (Left of " << node->data << ")\n";
                print(node->left, indent + 8);
            }
        }
    }
    //Se crea un nuevo nodo

    std::shared_ptr<Node<T>> newNode(T data) {
        return std::make_shared<Node<T>>(data);
    }

    //**A partir de aqui se hacen las rotaciones para rebalancear el arbol**
    //Se rota a la derecha para rebalancear el nodo determinado
    std::shared_ptr<Node<T>> rightRotate(std::shared_ptr<Node<T>> y) {
        std::shared_ptr<Node<T>> x = y->left; //El hijo a la izquierda de [y] se guarda como [x]
        std::shared_ptr<Node<T>> T2 = x->right;//El hijo a la derecha de [x] se guarda como [T2]

        x->right = y;//Se nombra [y] al hijo derecho de [x]
        y->left = T2;//Se nombra [T2] al hijo izquierdo de [y]

        y->height = max(height(y->left), height(y->right))+1;//Se reasigna la altura de [y]
        x->height = max(height(x->left), height(x->right))+1;//Se reasigna la altura de [x]

        return x;
    }

    //Se rota a la izquierda para rebalancear el nodo determinado
    std::shared_ptr<Node<T>> leftRotate(std::shared_ptr<Node<T>> x) {
        std::shared_ptr<Node<T>> y = x->right; //El hijo derecho de [x] se guarda como [y]
        std::shared_ptr<Node<T>> T2 = y->left; //El hijo izquierdo de [y] se guarda como [T2]

        y->left = x; //Se nombra [x] al hijo izquierdo de [y]
        x->right = T2;//Se nombra [T2] el hijo derecho de [x]

        x->height = max(height(x->left),height(x->right))+1;//Se reasigna la altura de [x]
        y->height = max(height(y->left),height(y->right))+1;//Se reasigna la altura de [y]

        return y;
    }
    //Se calcula el factor de equilibrio de un nodo
    int getBalance(std::shared_ptr<Node<T>> N) {
        //Si el nodo es {null} el resultado se regresa como 0
        if (N == nullptr)
            return 0;
        //Si el nodo no es {null} se resta la altura del sub-arbol izquierdo menos la del derecho
        return height(N->left) - height(N->right);
    }

    std::shared_ptr<Node<T>> insert(std::shared_ptr<Node<T>> node, T data) {
        //Si el nodo es {null}, se crea un nuevo nodo con informacion asignada
        if (node == nullptr)
            return (newNode(data));

        //Si el nodo pasa la condicion anterior y su informacion es menor a la del nodo
        //continua con una busqueda recursiva por la izquierda
        if (data < node->data)
            node->left = insert(node->left, data);

        //Si se cumplen las condiciones anteriores y la informacion es mayor a la del nodo, se continua
        //con una busqueda recursiva por la izquierda
        else if (data > node->data)
            node->right = insert(node->right, data);

        //Si ya existe un nodo con la informacion, se regresa este mismo
        else
            return node;

        //Calcula la altura del nodo
        node->height = 1 + max(height(node->left), height(node->right));

        //Se calcula el factor de equilibrio del nodo nuevo
        int balance = getBalance(node);

        //Si el factor de equilibrio es mas que 1 y la informacion es menor que la que hay en el hijo izquierdo
        if (balance > 1 && data < node->left->data)
            //Se hace una rotacion a la derecha
            return rightRotate(node);

        //Si el factor de equilibrio es menor que -1 y la informacion es mayor que la que hay en el hijo derecho
        if (balance < -1 && data > node->right->data)
            //Llama al metodo de rotacion a la izquierda
            return leftRotate(node);

        //Si el factor de equilibrio es mas que 1 y la informacion es mayor que la que hay en el hijo izquierdo
        if (balance > 1 && data > node->left->data) {
            //Rotamos a la izquierda en el hijo izquierdo
            node->left = leftRotate(node->left);
            //Y luego rotamos a la derecha
            return rightRotate(node);
        }
        //Si el factor de equilibrio es menor que -1 y la informacion es menor que la que hay en el hijo derecho
        if (balance < -1 && data < node->right->data) {
            //Rotamos a la derecha en el hijo derecho
            node->right = rightRotate(node->right);
            //Y luego rotamos a la derecha
            return leftRotate(node);
        }
        //Si no hay problemas de balance solo se regresa el nodo
        return node;
    }//No entendi en que momento se introduce el nodo como tal al arbol

    std::shared_ptr<Node<T>> minValueNode(std::shared_ptr<Node<T>> node) {
        //Declara un nuevo nodo llamado [current] con la informacion del nodo actual

        std::shared_ptr<Node<T>> current = node;

        //Mientras que el hijo izquierdo del nodo no es nulo
        while (current->left != nullptr)

        //Declara el nodo actual como su hijo izquierdo
            current = current->left;

        return current;
    }

    std::shared_ptr<Node<T>> deleteNode(std::shared_ptr<Node<T>> root, T data) {
        //Checa si la raiz es nula
        if (!root)
        //Si es nula devuelve la raiz pues no hay nada
            return root;


        //Si la data es menor que la data en la raiz
        if (data < root->data) {

        //En el hijo izquierdo del nodo, borra el nodo determinado
            root->left = deleteNode(root->left, data);
        }
        //Si la data es mas grande la data en la raiz
        else if(data > root->data) {
            //En el hijo derecho del nodo, borra el nodo determinado

            root->right = deleteNode(root->right, data);
        }
        //Reacomodo de los hijos
        else {
            //Si solo hay un hijo, este mismo toma el lugar del padre
            if(!root->left || !root->right) {
                root = (root->left) ? root->left : root->right;
            }
            //Si hay dos hijos, busca el nodo con mas valor del lado derecho y lo vuelve el nuevo padre
            else {
                std::shared_ptr<Node<T>> temp = minValueNode(root->right);
                root->data = temp->data;
                //Elimina el nodo original que se convirtio en el padre
                root->right = deleteNode(root->right, temp->data);
                //Resetea el temp
                temp.reset();
            }
        }
        //Si no existe root (o es un puntero null) se regresa este mismo (osea se regresa nada) para que no siga buscando
        if(!root)
            return root;

        //Calcula la altura del nodo
        root->height = 1 + max(height(root->left), height(root->right));

        //Saca el factor de equilibrio
        int balance = getBalance(root);

        //Si el balance del nuevo nodo es mas que uno y el del nodo a la izquierda de raiz mayor o igual a 0
        //Rota a la derecha

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        //Si el balance es menos que -1 y el del nodo a la derecha de raiz menor o igual a cero
        //Se rota a la izquierda
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);


        //Si el balance es mayor que 1 y el del nodo a la izquierda de raiz menor que 0
        //Rota a la izquierda en el hijo izquierdo de la sub-raiz y luego a la derecha en esta

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        //Si el balance es menor que -1 y el del nodo a la derecha de raiz mayor que 0
        //Rota a la derecha en el hijo derecho de la sub-raiz y luego a la izquierda en esta

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        //Si no hay problema de balance o se soluciono, se regresa
        return root;
    }

    //Si el nodo exite regresa la altura que tiene
    //Si no regresa 0

    int height(std::shared_ptr<Node<T>> N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }
    //Regresa el mayor de los valores pasados

    int max(int a, int b) {
        return (a > b)? a : b;
    }
};

#endif /* AVL_TREE_H */
