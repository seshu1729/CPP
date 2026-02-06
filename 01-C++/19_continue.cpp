#include <iostream>
using namespace std;
 
int main () 
{
   int a = 10;  // Local variable declaration:
   do {    // do loop execution
      if( a == 15) 
      {
         a = a + 1;
        continue;
        cout << "inside block value of a: " << a << endl;
      }
      a = a + 1;
      cout << "value of a: " << a << endl;
   } 
   while( a < 20 );
 
   return 0;
}