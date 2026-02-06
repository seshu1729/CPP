#include <iostream>
#include <sstream>
#include <string>

using namespace std;
 
int main() 
{
   int a ;
   double b = 21.09399;
   float c = 10.20;
   char d = 'A';
   
   a = (int) b;
   cout << "Line 1 - Value of (int)b is :" << a << endl ;
   
   a = (int) c;
   cout << "Line 2 - Value of (int)c is :" << a << endl ;
   
   a = (int) d;
   cout << "Line 3 - Value of (int)d is :" << a << endl ;
   
   string e = "John Doe 02.01.1970" ;
   string   fname;
   string   lname;
   int      day;
   int      month;
   int      year;
   char     sep;

    stringstream data(e);
    data >> fname >> lname >> day >> sep >> month >>sep >> year;
    //The operator >> when used with a string variable will read a single (white) space separate word. 
    //When used with an integer variable will read an integer from the stream (discarding any proceeding (white) space).
    cout << "fname : " << fname << " \nlname : " << lname << " \nsep : " << sep << "\n";
    cout << "Day : " << day << " \nMonth : " << month << " \nYear : " << year << "\n";
   
   return 0;
}