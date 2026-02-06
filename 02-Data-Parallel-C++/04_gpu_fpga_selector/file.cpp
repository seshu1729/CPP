#include <CL/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>
#include <iostream>

using namespace sycl;
using namespace std;

int main() 
{
queue my_gpu_queue( gpu_selector_v );
//queue my_fpga_queue( ext::intel::fpga_selector{} );
queue my_fpga_emu_queue( ext::intel::fpga_emulator_selector{} );

cout << "Selected device 1: " << my_gpu_queue.get_device().get_info<info::device::name>() << "\n";
//cout << "Selected device 2: " << my_fpga_queue.get_device().get_info<info::device::name>() << "\n";
cout << "Selected device 2: " << my_fpga_emu_queue.get_device().get_info<info::device::name>() << "\n";    

return 0;
}