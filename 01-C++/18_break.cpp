#include <iostream>
using namespace std;

int main () {
   int a = 10;
   do {
      a = a + 1;
      if( a > 15) {
         break; // terminate the loop
      }
     cout << "value of a: " << a << endl;  
   } while( a < 20 );
   return 0;
}