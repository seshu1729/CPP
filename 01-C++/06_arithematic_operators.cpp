#include <iostream>
using namespace std;
 
int main() {
   int a = 21;
   int b = 10;
   int c ;
 
   c = a + b;
   cout << "c = a + b - Value of c is :" << c << endl ;
   
   c = a - b;
   cout << "c = a - b - Value of c is  :" << c << endl 
   ;
   c = a * b;
   cout << "c = a * b - Value of c is :" << c << endl ;
   
   c = a / b;
   cout << "c = a / b - Value of c is  :" << c << endl ;
   
   c = a % b;
   cout << "c = a % b - Value of c is  :" << c << endl ;
   
   
   cout << "\nbefore c = a++ - Value of a,c is :" <<a<<" " <<c << endl ;
   c = a++; 
   cout << "after c = a++ - Value of a,c is :" << a<<" " <<c << endl ;
   
   cout << "\nbefore c = a-- - Value of a,c is :" <<a<<" " <<c << endl ;
   c = a--; 
   cout << "after c = a-- - Value of a,c is  :" <<a<<" " <<c << endl ;
   
   cout << "\nbefore c = ++a - Value of a,c is :" <<a<<" " <<c << endl ;
   c = ++a; 
   cout << "after c = ++a - Value of a,c is :"  <<a<<" " <<c << endl ;
   
   cout << "\nbefore c = --a - Value of a,c is :" <<a<<" " <<c << endl ;
   c = --a; 
   cout << "after c = --a - Value of a,c is  :" <<a<<" " <<c << endl ;
   
   
   
   
   cout << "\n  ++a - Value of a is :" <<++a << endl ;
   cout << "after ++a Value of a is :"  <<a << endl ;
   cout << "\n  --a - Value of a is :" <<--a<< endl ;
   cout << "after --a - Value of a" <<a<< endl ;
   
   
   return 0;
}