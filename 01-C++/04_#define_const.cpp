//two simple ways in C++ to define constants
//#define preprocessor  ==== #define identifier value
//const keyword         ==== const type variable = value

#include <iostream>
using namespace std;

#define LENGTH 10   
//const int  WIDTH  = 5;
#define NEWLINE '\n'

int main() {
   int area;  
   const int  WIDTH  = 5;
   //const char NEWLINE = '\n';
 
   area = LENGTH * WIDTH;
   cout << area;
   cout << NEWLINE;
   return 0;
}