#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;
 
int main () 
{
   int i,j;
   //srand((unsigned)time( NULL )); // we can also right   
   srand(time(0));              // set the seed
   for( i = 0; i < 10; i++ )    /* generate 10  random numbers. */
   {
      //j = rand() ;               // generate actual random number
      //int randNum = rand()%(max-min + 1) + min; //can be used for generating between 2 numbers
       j = rand() %100;              // generate actual random number betwwn 0 to 100
      cout <<" Random Number : " << j << endl;
   }
   return 0;
}