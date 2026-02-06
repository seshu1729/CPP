#include <iostream>
using namespace std;
 
int main () {
   // Local variable declaration:
   int x, y = 10;

   x = (y < 10) ? 30 : 40;
   cout << "value of x: " << x << endl;
 
   return 0;
}