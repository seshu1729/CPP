#include <iostream>
using namespace std;

double getAverage(int arr[], int size);

int main() 
{
   int balance[5] = {1000, 2, 3, 17, 50};
   double avg;
   avg = getAverage( balance, 5 ) ;    // pass pointer to the array as an argument.
   cout << "Average value is: " << avg << endl; 
    
   return 0;
}

//void myFunction(int *array) {...}    can be passed in this format
//void myFunction(int array[10]) {...} can be passed in this format
//void myFunction(int array[]) {...}   can be passed in this format  ,  in call myFunction(array) , in return return array
double getAverage(int arr[], int size) 
{
  int i, sum = 0;       
  double avg;          

   for (i = 0; i < size; ++i) 
   {
    sum += arr[i];
   }
   avg = double(sum) / size;

   return avg;
}