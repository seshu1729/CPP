#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;
using namespace std;

int main() 
{
// Create queue to use the host device explicitly
queue Q( host_selector{} ); // deprecated in oneAPI 2023. May not be accessible after oneAPI 2023.2.0 release

cout << "\nSelected device name: " << Q.get_device().get_info<info::device::name>() << "\n";
cout << "Selected device vendor: " << Q.get_device().get_info<info::device::vendor>() << "\n\n";

return 0;
}