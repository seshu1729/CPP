#include <CL/sycl.hpp>
#include <iostream>
using namespace cl::sycl;
using namespace std;

int main()
{
    try
    {
    buffer<int> B{ range{16} };
// ERROR: Create sub-buffer larger than size of parent buffer
// An exception is thrown from within the buffer constructor
    buffer<int> B2(B, id{8}, range{16});
    }
    catch (const exception& e)
    {
        cout << "Exception caught: " << e.what() << "\n";
    }
return 0;
}