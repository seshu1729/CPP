#include <iostream>
using namespace std;

void swap(int &x, int &y); // function declaration

int main () 
{
   int a = 100;
   int b = 200;
 
   cout << "Before swap, value of a :" << a << endl;
   cout << "Before swap, value of b :" << b << endl;

   swap(a, b);  /* calling a function to swap the values using variable reference.*/

   cout << "After swap, value of a :" << a << endl;
   cout << "After swap, value of b :" << b << endl;
 
   return 0;
}

void swap(int &x, int &y) // function definition to swap the values.
{
   int temp;
   temp = x; /* save the value at address x */
   x = y;    /* put y into x */
   y = temp; /* put x into y */
  
   return;
}