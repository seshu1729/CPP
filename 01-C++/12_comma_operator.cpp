#include <iostream>
using namespace std;

int main() {
   int i, j;
   
   j = 10;
   i = (j++, j+100, 999+j); //i takes only the last value in the bracket

   cout <<"i = "<< i<<" j = "<<j ;
   
   return 0;
}