#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;
using namespace std;

int main()
{

// Create queue on whatever default device that the implementation chooses. Implicit use of the default_selector. 
queue Q;
    
cout << "\nSelected device name: " <<Q.get_device().get_info<info::device::name>() << "\n";
cout << "Selected device vendor: " <<Q.get_device().get_info<info::device::vendor>() << "\n";
cout << "Selected device version: "<<Q.get_device().get_info<info::device::version>() << "\n";
cout << "Selected device max compute units: " <<Q.get_device().get_info<info::device::max_compute_units>() << "\n";
cout << "Selected device local mem size: "    <<Q.get_device().get_info<info::device::local_mem_size>() << "\n";
cout << "Selected device driver version: "    <<Q.get_device().get_info<info::device::driver_version>() << "\n";
cout << "Selected device max work group size: "       <<Q.get_device().get_info<info::device::max_work_group_size>() << "\n";
cout << "Selected device max work item dimensions: "  <<Q.get_device().get_info<info::device::max_work_item_dimensions>() << "\n";
cout << "d.has(aspect::image): "  <<Q.get_device().has(aspect::image) << "\n";
cout << "d.get_info<info::device::image_support>(): "  <<Q.get_device().get_info<info::device::image_support>() << "\n";
cout << "__INTEL_LLVM_COMPILER : "  <<__INTEL_LLVM_COMPILER << "\n";

    
return 0;
}