//Address of Operator &
//Indirection Operator *
#include <iostream>
using namespace std;
const int MAX = 3;

int main () 
{
   int var= 3000 , *ptr , val;
   int var2 = 4000 , *ptr2 , **ptr3 , val2 ,val3;
   ptr = &var; // take the address of var
   val = *ptr; // take the value available at ptr
   cout << "\nValue of var :" << var << "\n ptr :" << ptr <<"\n val :" << val << endl;
   
   ptr2 = &var2 ; 
   ptr3 = &ptr2 ;
   val2 = *ptr2 ;
   val3 = **ptr3;
   
   cout << "\n\nValue of var2 :" << var2 << "\n ptr2 :" << ptr2 <<"\n ptr3 :" << ptr3 <<" \nval2 :" << val2 <<" \nval3 :" << val3 << endl;
   
   int *ptr4 = NULL;
   cout << "The value of ptr4 is " << ptr4 ;//Null pointer
   ptr4++; // ptr4 is pointing to the next int location address, it is pointer arithmatic ,++, --, +, -  
   //only this 4 can be used for arithmatic operations can be used
   cout << "\nThe value of ptr4++ is " << ptr4<<endl ;//Null pointer
   if (ptr4 < ptr4 +2)
   {
   cout<< ptr4  <<" :ptr4 is lesser ptr4 + 2 :"<< ptr4 + 2<<endl ; //pointer comparison
   }

    int  arr[MAX] = {10, 100, 200};
 
   for (int i = 0; i < 4; i++) {
      *arr = i;    // This is a correct syntax
     // arr++;       // This is incorrect.
     *(arr + 3) = 500; //valid
     //cout<<*(arr + i)<<"\n";
     cout<<arr[i]<<"\n";
   }
   
   
   return 0;
}