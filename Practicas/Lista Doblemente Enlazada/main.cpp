#include <iostream>
#include "DLList.h"

int main() {
    // Test integer list
    DLList<int> integerList;
    integerList.push_back(10);
    integerList.push_front(20);
    integerList.insert(1, 30);
    std::cout << "Integer list: ";
    integerList.print();
    integerList.erase(1);
    std::cout << "Integer list after erase: ";
    integerList.print();
    integerList.clear();
    std::cout << "Integer list after clear: ";
    integerList.print();

    // Test double list
    DLList<double> doubleList;
    doubleList.push_back(1.5);
    doubleList.push_front(2.5);
    doubleList.insert(1, 3.5);
    std::cout << "\nDouble list: ";
    doubleList.print();
    doubleList.erase(1);
    std::cout << "Double list after erase: ";
    doubleList.print();
    doubleList.clear();
    std::cout << "Double list after clear: ";
    doubleList.print();

    // Test char list
    DLList<char> charList;
    charList.push_back('a');
    charList.push_front('b');
    charList.insert(1, 'c');
    std::cout << "\nChar list: ";
    charList.print();
    charList.erase(1);
    std::cout << "Char list after erase: ";
    charList.print();
    charList.clear();
    std::cout << "Char list after clear: ";
    charList.print();

    return 0;
}