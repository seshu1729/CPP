//Every object has a special pointer this which points to the object itself.
#include<iostream>
using namespace std;

/* local variable is same as a member's name */
class Test
{
private:
int x=10;
public:
void setX (int x)
{
	// The 'this' pointer is used to retrieve the object's x
	// hidden by the local variable 'x'
	this->x = x;
}
void print() { cout << "x = " << x << endl; }
//static void fun1() { cout << "Inside fun1()"; } 		// it will print automatically
//void fun2() { cout << "Inside fun2()"; this->fun1(); } 	// it will print when obj.fun2() calls from main() 
//static void fun2() { cout << "Inside fun2()"; this->fun1(); } // produces an error
};

int main()
{
Test obj;
int x = 20;
obj.setX(x);
obj.print();
return 0;
}
