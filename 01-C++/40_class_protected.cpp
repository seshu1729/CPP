//Data hiding
//public, private, and protected are called access specifiers
//protected member variable or function is very similar to a private member 
//but it provided one additional benefit that they can be accessed in child classes which are called derived classes.
#include <iostream>
using namespace std;
 
class Box 
{
   protected:
    double width;
};
 
class SmallBox:Box // SmallBox is the derived class.
{ 
   public:
    void setSmallWidth( double wid );
    double getSmallWidth( void );
};
 
double SmallBox::getSmallWidth(void) // Member functions of child class
{
   return width ;
}
 
void SmallBox::setSmallWidth(double wid) 
{
   width = wid;
}
 
int main() 
{
   SmallBox box;
   box.setSmallWidth(5.0); // set box width using member function
   cout << "Width of box : "<< box.getSmallWidth() << endl;
   
   return 0;
}