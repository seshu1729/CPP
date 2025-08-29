#include <CL/sycl.hpp>
#include <iostream>
using namespace cl::sycl;
using namespace std;

int main()
{
// Create queue to use the CPU device explicitly
queue Q( cpu_selector_v );

cout << "\nSelected device name: " << Q.get_device().get_info<info::device::name>() << "\n";
cout << "Selected device vendor: " << Q.get_device().get_info<info::device::vendor>() << "\n\n";
    
return 0;
}