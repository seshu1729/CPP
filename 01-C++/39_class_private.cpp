//Data hiding
//public, private, and protected are called access specifiers
//A private member variable or function cannot be accessed, or even viewed from outside the class. 
//Only the class and friend functions can access private members.By default all the members of a class would be private
//until you label a member, it will be assumed a private member
#include <iostream>
using namespace std;
 
class Box 
{
   public:
      double length;
      void setWidth( double wid );
      double getWidth( void );
 
   private:
      double width;
};
 
// Member functions definitions
double Box::getWidth(void) 
{
   return width ;
}
 
void Box::setWidth(double wid) 
{
   width = wid;
}

int main() 
{
   Box box;
 
   // set box length without member function
   box.length = 10.0; // OK: because length is public
   cout << "Length of box : " << box.length <<endl;
 
   // set box width without member function
   // box.width = 10.0; // Error: because width is private
   box.setWidth(10.0);  // Use member function to set it.
   cout << "Width of box : " << box.getWidth() <<endl;
 
   return 0;
}