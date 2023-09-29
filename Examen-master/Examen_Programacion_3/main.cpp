#include <iostream>
#include "DoubleCell.h"
int main() {
   //Initialize a DoubleCell object
   DoubleCell dc(5);
   //initialize a DoubleCell object with no argument
   DoubleCell dc2;
   //Print the value of the DoubleCell object
   std::cout << "The value of dc is " << dc.GetValue() << std::endl;
   //Print the value of the DoubleCell object
   std::cout << "The value of dc2 is " << dc2.GetValue() << std::endl;
   //Assign a new value to the DoubleCell object
   dc2 = dc;
   //Add a double to the DoubleCell object
   dc2 = dc2 + 5.0;
   //Subtract a double from the DoubleCell object
   dc2 = dc2 - 15.0;

   //Print the value of the DoubleCell object
   std::cout << "The value of dc2 is " << dc2.GetValue() << std::endl;

}
