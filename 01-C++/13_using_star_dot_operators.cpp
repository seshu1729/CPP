#include <iostream>
using namespace std;

class sample
{
	private:
		int a;
	public:
		int b;
		void init(int a)
		{
		    this->a = a;
		}
		void display()
		{
		    cout<<"a: "<<a<<endl;
		}
};

int main()
{
	sample *sam = new sample();         //pointer to an object declaration
	cout<<"Using * and . Operators\n";  //value assignment to a and back
	(*sam).init(100);
	(*sam).b=200;
	(*sam).display();           	    //printing the values
	cout<<"b: "<<(*sam).b<<endl;
	
	cout<<"Using Arrow Operator (->)\n";//value assignment to a and back
	sam->init(100);
	sam->b=200;
	sam->display();                     //printing the values
	cout<<"b: "<<sam->b<<endl;	
	
	return 0;			
}