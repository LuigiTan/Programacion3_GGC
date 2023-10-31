#include <iostream>
#include "DLList.h"
#include "Stack.h"
#include "Queue.h"
#include "SLList.h"

int main() {
    // Test Simple List
    SLList<int> simpleList;
    simpleList.push_front(20);
    simpleList.push_front(10);
    simpleList.push_front(30);
    simpleList.push_front(40);
    simpleList.push_front(50);
    std::cout << "Simple list: ";
    simpleList.print();
    simpleList.pop_front();
    std::cout << "Simple list after pop: ";
    simpleList.print();
    simpleList.clear();
    std::cout << "Simple list after clear: ";
    simpleList.print();


    // Test integer Double Linked List
    DLList<int> integerList;
    integerList.push_back(10);
    integerList.push_front(20);
    integerList.insert(1, 40);
    int a =3;
    integerList.insert(integerList.begin()+2, 30);
    integerList.insert(a, 12);
    std::cout << "Integer list: ";
    integerList.print();
    (void)integerList.erase(integerList.begin() + 1);
    std::cout << "Integer list after erase: ";
    integerList.print();
    integerList.clear();
    std::cout << "Integer list after clear: ";
    integerList.print();

    // Test double Double-Linked List
    DLList<double> doubleList;
    doubleList.push_back(1.5);
    doubleList.push_front(2.5);
    doubleList.insert(1, 3.5);
    doubleList.insert(doubleList.begin()+2, 4.5);
    doubleList.insert(2, 5.5);
    std::cout << "\nDouble list: ";
    doubleList.print();
    doubleList.erase(doubleList.begin() + 1);
    std::cout << "Double list after erase: ";
    doubleList.print();
    doubleList.clear();
    std::cout << "Double list after clear: ";
    doubleList.print();

    // Test char Double Linked List
    DLList<char> charList;
    charList.push_back('a');
    charList.push_front('b');
    charList.insert(1, 'c');
    std::cout << "\nChar list: ";
    charList.print();
    charList.erase(charList.begin() + 1);
    std::cout << "Char list after erase: ";
    charList.print();
    charList.clear();
    std::cout << "Char list after clear: ";
    charList.print();

    //Boolean list
    DLList<bool> boolList;
    boolList.push_back(true);
    boolList.push_front(false);
    boolList.insert(1, true);
    std::cout << "\nBoolean list: ";
    boolList.print();
    boolList.erase(boolList.begin() + 1);
    std::cout << "Boolean list after erase: ";
    boolList.print();
    boolList.clear();
    std::cout << "Boolean list after clear: ";
    boolList.print();

    //Test int Stack
    Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << "\nStack: ";
    stack.print();
    stack.pop();
    std::cout << "Stack after pop: ";
    std::cout << stack.top() << std::endl;

    //Test double Stack
    Stack<double> doubleStack;
    doubleStack.push(1.5);
    doubleStack.push(2.5);
    doubleStack.push(3.5);
    std::cout << "\nDouble Stack: ";
    doubleStack.print();
    doubleStack.pop();
    std::cout << "Double Stack after pop: ";
    std::cout << doubleStack.top() << std::endl;
    doubleStack.clear();

    //Test Queue
    Queue<int> queue;
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    std::cout << "\nQueue: ";
    queue.print();
    queue.dequeue();
    std::cout << "Queue after dequeue: ";
    std::cout << queue.front() << std::endl;
    queue.clear();

    /*
     * This is completely optional, but if you want a challenge, try to implement an explicit constructor for the Data Structure classes that takes in an initialiser list. For example, you should be able to do something like this:
     * DLList<int> list = {1, 2, 3, 4, 5};
     * Stack<int> stack = {1, 2, 3, 4, 5};
     * Queue<int> queue = {1, 2, 3, 4, 5};
     * SLList<int> simpleList = {1, 2, 3, 4, 5};

     * For anyone able to do this, you will get 20 bonus points on the assignment. You can do this for any of the Data Structures, but you only get the bonus points once.
     */

    return 0;
}