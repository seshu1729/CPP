// With an inline function, the compiler tries to expand the code in the body of the function in place of a call to the function.
//This copies the function to the location of the function call in compile-time and may make the program execution faster

#include <iostream>
using namespace std;

inline int max_num(int x, int y) 
{
  return (x > y)? x : y;
}

int main() 
{
   cout << "Greater of ( 40, 50 ) is: " << max_num(40,50) << endl;
   cout << "Greater of ( 90, 50 ) is: " << max_num(90,50) << endl;
   cout << "Greater of ( -5, 34 ) is: " << max_num(-5,34) << endl;
   return 0;
}