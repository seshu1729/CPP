#include <iostream>
#include <string>

using namespace std;

int main () {

   string str1 = "Hello";
   string str2 = "World";
   string str3;
   int  len ;

   // copy str1 into str3
   str3 = str1;
   cout << "str3 = str1; str3 : " << str3 << endl;

   // concatenates str1 and str2
   str3 = str1 + str2;
   cout << "str3 = str1 + str2; str3 : " << str3 << endl;

   // total length of str3 after concatenation
   len = str3.size();
   cout << "len = str3.size() :  " << len << endl;
   
   char a[6] = {'h','a','p','p','y','\0'};
   string s = "String" ;
   cout <<"s + a = " << s + a << endl;

    string str4;
  
    cout << "getline(cin, str4); Please enter your name: \n";
    getline(cin, str4);
    cout << "Hello, " << str4 << " and str4 size is = "<< str4.size()<<endl ;
    cout << "is str4 empty ? "<< str4.empty()<<endl ;
    cout << "used str4.append() "<< str4.append(" where are u...?")<<endl;
    
    int i4 = stoi(str4);
    cout<<i4 << " is i4 = stoi(str4);" <<endl ;

   	int i5 = stod(str4);
    cout<<i5<< " is i5 = stod(str4);" <<endl ;
    
    string str5 = "dog" ;
    string str6 = "cat" ;
    cout<< "str5 " <<str5 ;
    cout<< "\nstr6 " <<str6 ;
    cout<< "\nstr5.compare(str6) = "<<str5.compare(str6) <<endl ;
    cout<< "str5.compare(str5) = "<<str5.compare(str5) <<endl ;
    cout<< "str6.compare(str5) = "<<str6.compare(str5) <<endl ;
    
    string str7 = str6.assign(str6);
    cout<< str7 <<endl ;
    
    string str8 = "where is the cat dog";
    string str9 = str8.assign(str8,0,7);//where i
    
    cout<< "str8 is "<<str8 <<endl ;
    cout<< "str9 is "<<str9 <<endl ;
    
    str9 = str8.assign(str8,1,9);//here i 
    cout<< "str8 is "<<str8 <<endl ;
    cout<< "str9 is "<<str9 <<endl ;
    
    str9 = str8.find("r",0);
    cout<< "str8 is "<<str8 <<endl ;
    cout<< "str9 is "<<str9 <<endl ;
   return 0;


}