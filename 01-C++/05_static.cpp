#include <iostream>
 
// Function declaration
void func();
 
static int count = 10; /* Global variable */

//The static storage class instructs the compiler to keep a local variable in existence during the life-time of the program 
//instead of creating and destroying it each time it comes into and goes out of scope. 
//Therefore, making local variables static allows them to maintain their values between function calls. 

int main() 
{
   while(count--) 
   {
      func();
   }
   return 0;
}

// Function definition
void func() 
{
   static int i = 5; // local static variable
   i++;
   std::cout << "i is " << i ;
   std::cout << " and count is " << count << std::endl;
}