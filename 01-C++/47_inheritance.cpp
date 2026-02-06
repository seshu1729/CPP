//Access	        	public    	protected	private
//=======================================================================
//Same class	        	yes		yes		yes
//Derived classes		yes		yes		no
//Outside classes	 	yes		no		no
//A derived class can access all the non-private members of its base class. 
//Thus base-class members that should not be accessible to the member functions of derived classes 
//should be declared private in the base class.
//A derived class inherits all base class methods with the following exceptions −

//1. Constructors, destructors and copy constructors of the base class.
//2. Overloaded operators of the base class.
//3. The friend functions of the base class.
//the base class may be inherited through public, protected or private inheritance. mostly public we use

//Public Inheritance − When deriving a class from a public base class, 
//public members of the base class become public members of the derived class and 
//protected members of the base class become protected members of the derived class. 
//A base class's private members are never accessible directly from a derived class, 
//but can be accessed through calls to the public and protected members of the base class.

//Protected Inheritance − When deriving from a protected base class, 
//public and protected members of the base class become protected members of the derived class.

//Private Inheritance − When deriving from a private base class, 
//public and protected members of the base class become private members of the derived class.

#include <iostream>
 
using namespace std;

// Base class
class Shape {
   public:
      void setWidth(int w) {
         width = w;
      }
      void setHeight(int h) {
         height = h;
      }
      
   protected:
      int width;
      int height;
};

// Derived class
class Rectangle: public Shape {
   public:
      int getArea() { 
         return (width * height); 
      }
};

int main(void) {
   Rectangle Rect;
 
   Rect.setWidth(5);
   Rect.setHeight(7);

   // Print the area of the object.
   cout << "Total area: " << Rect.getArea() << endl;

   return 0;
}