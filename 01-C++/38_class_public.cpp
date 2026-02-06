//Data hiding
//public, private, and protected are called access specifiers
//A public member is accessible from anywhere outside the class but within a program.

#include <iostream>
using namespace std;
 
class Line 
{
   public:
      double length;
      void setLength(double len);
      double getLength(void);
};

// Member functions definitions
double Line::getLength(void) 
{
   return length ;
}
 
void Line::setLength(double len) 
{
   length = len;
}
 
int main() 
{
   Line line;

   line.setLength(6.0);  // set line length
   cout << "Length of line : " << line.getLength() <<endl;
 
   // set line length without member function
   line.length = 10.0; // OK: because length is public
   cout << "Length of line : " << line.length <<endl;
   
   return 0;
}