#include <iostream>
#include <ctime>
using namespace std;
 
double a[] = {10.1, 12.6, 33.1, 24.1, 50.0};
 
double& setValues(int i) 
{
   return a[i];   // return a reference to the ith element
}

int main() 
{
   cout << "Value before change" << endl;
   for (int i = 0; i < 5; i++) 
   {
      cout << "a[" << i << "] = ";
      cout << a[i] << endl;
   }
 
   setValues(1) = 20.23; // change 2nd element
   setValues(3) = 70.8;  // change 4th element
 
   cout << "Value after change" << endl;
   for ( int i = 0; i < 5; i++ ) {
      cout << "a[" << i << "] = ";
      cout << a[i] << endl;
   }
   return 0;
}