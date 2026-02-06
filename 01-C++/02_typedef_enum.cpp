#include <iostream>
using namespace std;

int main() {
 
   //typedef type newname;
   typedef int feet;
   feet distance=5;
   
   //enum enum-name { list of names } var-list; 
    enum color { red, green = 33, blue } c;
   int a = red;
   int b = green;
   c = blue;
   
   
   cout << "distance and Size of distance : " <<distance<< "  "<<sizeof(distance) << endl;
   cout << " a: " <<a <<" b: " <<b <<" c: "<<c<< " sizeof(a) "<<sizeof(a) << endl; 
   return 0;
}