#include <iostream>
#include <cstring>
using namespace std;

int main () 
{  
   char greeting[6] = {'H', 'e', 'l', 'l', 'o', '\0'};
   cout << "Greeting message: ";
   cout << greeting << endl;
   char str1[10] = "Hello";
   char str2[10] = "World";
   char str3[10];
   char str4[10] = "titan";
   int  len ;
   int ch = 'o';
   
   cout << "str1 : " << str1 << endl;
   cout << "str2 : " << str2 << endl;
   cout << "str3 : " << str3 << endl;
   strcpy( str3, str1);         // copy str1 into str3
   cout << "strcpy( str3, str1) : " << str3 << endl;
   
   strcat( str1, str2);         // concatenates str1 and str2
   cout << "strcat( str1, str2) : " << str1 << endl;
   
   len = strlen(str1);          // total lenghth of str1 after concatenation
   cout << "strlen(str1) : " << len << endl;
   
 
   cout << "strcmp(str1, str2); : " << strcmp(str1, str2) << endl; //0 if str1 == str2 ; <0 if str1<str2; >0 if str1>str2
   cout << "strcmp(str2, str1); : " << strcmp(str2, str1) << endl; //0 if str1 == str2 ; <0 if str1<str2; >0 if str1>str2

   cout << "\nstr1 : " << str1 << endl;
   cout << "str2 : " << str2 << endl;
   cout << "str3 : " << str3 << endl;
   cout << "str4 : " << str4 << endl;
   cout<<"strchr(str1, ch): " << strchr(str1, ch)<<endl; //Returns a pointer to the first occurrence of character ch in string str1
   
   cout<<"strstr(str1, str3): "<<strstr(str1, str3)<< endl; //Returns a pointer to the first occurrence of string str3 in string str1
   cout<<"strstr(str1, str4): "<<strstr(str1, str4)<< endl; //Returns a pointer to the first occurrence of string str4 in string str1

   return 0;
}