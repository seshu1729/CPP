#include <iostream>
using namespace std;

int main() 
{
   cout << "Size of short :        " << sizeof(short) << endl;
   cout << "Size of int :          " << sizeof(int) << endl;
   cout << "Size of float :        " << sizeof(float) << endl;
   cout << "Size of long :         " << sizeof(long) << endl;
   cout << "Size of double :       " << sizeof(double) << endl;
   
   cout<<"\n";
   
   cout << "Size of short int :    " << sizeof(short int) << endl;
   cout << "Size of signed int :   " << sizeof(signed int) << endl;
   cout << "Size of unsigned int : " << sizeof(unsigned int) << endl;
   cout << "Size of long int :     " << sizeof(long int) << endl;
   cout<<"\n";
   
   cout << "Size of long long :    " << sizeof(long long) << endl;
   cout << "Size of long double :  " << sizeof(long double) << endl;
   
   cout<<"\n";
   
   cout << "Size of char :         " << sizeof(char) << endl;
   cout << "Size of char16_t :     " << sizeof(char16_t) << endl;
   cout << "Size of char32_t :     " << sizeof(char32_t) << endl;
   cout << "Size of wchar_t :      " << sizeof(wchar_t) << endl;
   
// number definition:
   short  s;
   int    i;
   long   l;
   float  f;
   double d;
   
   // number assignments;
   s = 10;      
   i = 1000;    
   l = 1000000; 
   f = 230.47;  
   d = 30949.374;
   
   cout<<"\n";
   // number printing;
   cout << "short  s :" << s << endl;
   cout << "int    i :" << i << endl;
   cout << "long   l :" << l << endl;
   cout << "float  f :" << f << endl;
   cout << "double d :" << d << endl;
 
   return 0;
}