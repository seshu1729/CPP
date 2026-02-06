#include <iostream>
using namespace std;

int main() {
   int a = 21;
   int b = 10;
   int c ;

   if( a == b ) 
   {
      cout << " a == b a is equal to b" << endl ;
   } 
   else 
   {
      cout << " a == b a is not equal to b" << endl ;
   }
   
   if( a < b ) 
   {
      cout << " a < b a is less than b" << endl ;
   } 
   else 
   {
      cout << " a < b a is not less than b" << endl ;
   }
   
   if( a > b ) 
   {
      cout << " a > b a is greater than b" << endl ;
   } 
   else 
   {
      cout << " a > b a is not greater than b" << endl ;
   }
   
   /* Let's change the values of a and b */
   a = 5;
   b = 20;
   if( a <= b ) 
   {
      cout << "  b >= a a is either less than or equal to  b" << endl ;
   }
   
   if( b >= a ) 
   {
      cout << "  b >= a b is either greater than or equal to b" << endl ;
   }
   
   if( a != b ) 
   {
      cout << " a != b a is greater than b" << endl ;
   } 
   else 
   {
      cout << " a != b a is not greater than b" << endl ;
   }
   return 0;
}
