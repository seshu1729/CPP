//polymorphism means having many forms.
//polymorphism occurs when there is a hierarchy of classes and they are related by inheritance.
//each of the child classes has a separate implementation for the function area()
// different classes with a same function name, parameters, but different implementations
//selection of the function to be called at any point based on the kind of object for which it is called. -- dynamic linkage, or late binding.
//The = 0 tells the compiler that the function has no body and above virtual function will be called pure virtual function.
#include <iostream> 
using namespace std;
 
class Shape {
   protected:
      int width, height;
      
   public:
      Shape( int a = 0, int b = 0){
         width = a;
         height = b;
      }
      virtual int area() //kept virtual ---signals to the compiler that we don't want static linkage for this function.
      { 
         cout << "Parent class area :" <<endl;
         return 0;
      }
};
class Rectangle: public Shape {
   public:
      Rectangle( int a = 0, int b = 0):Shape(a, b) { }
      
      int area () { 
         cout << "Rectangle class area :" <<endl;
         return (width * height); 
      }
};

class Triangle: public Shape {
   public:
      Triangle( int a = 0, int b = 0):Shape(a, b) { }
      
      int area () { 
         cout << "Triangle class area :" <<endl;
         return (width * height / 2); 
      }
};

// Main function for the program
int main() {
   Shape *shape;
   Rectangle rec(10,7);
   Triangle  tri(10,5);

   // store the address of Rectangle
   shape = &rec;
   
   // call rectangle area.
   shape->area();

   // store the address of Triangle
   shape = &tri;
   
   // call triangle area.
   shape->area();
   
   return 0;
}