//class constructor is a special member function of a class that is executed whenever we create new objects of that class.
//Parameterized Constructor
//A default constructor does not have any parameter, but if you need, a constructor can have parameters. 
#include <iostream>
using namespace std;

class Line 
{
   public:
      void setLength( double len );
      double getLength( void );
      Line(double len);  // This is the constructor
 
   private:
      double length;
};
 
Line::Line( double len)  // Member functions definitions including constructor
{
   cout << "Object is being created, length = " << len << endl;
   length = len;
}
void Line::setLength(double len) 
{
   length = len;
}
double Line::getLength(void) 
{
   return length;
}

int main() 
{
   Line l(10.0);
    
   cout << "Length of line : " << l.getLength() <<endl; // get initially set length. 
  
   l.setLength(6.0);  // set line length again
   cout << "Length of line : " << l.getLength() <<endl;
 
   return 0;
}