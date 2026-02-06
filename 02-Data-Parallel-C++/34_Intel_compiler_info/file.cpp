//#include <CL/sycl.hpp>
#include <iostream>
//using namespace sycl;
using namespace std;

int main()
{
   //std::cout << "SYCL_LANGUAGE_VERSION: " << SYCL_LANGUAGE_VERSION << std::endl;
   cout << "__INTEL_LLVM_COMPILER: " << __INTEL_LLVM_COMPILER << std::endl;
   cout << "__VERSION__: " << __VERSION__ << std::endl;

    return 0;
}