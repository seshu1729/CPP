#include <CL/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp> // For fpga_selector and emulator try ==> icpx -fsycl -fintelfpga -DFPGA_EMULATOR file.cpp
#include <iostream>
#include <string>

using namespace cl::sycl;
using namespace std;

int main() 
{

queue q1( default_selector_v );
cout<<"\ndefault_selector_v:\n" ;
cout << " -> Device name: "   << q1.get_device().get_info<info::device::name>() << "\n";
cout << " -> Device vendor: " << q1.get_device().get_info<info::device::vendor>() << "\n";
    
queue q2( cpu_selector_v );
cout<<"\ncpu_selector_v:\n" ;
cout << " -> Device name: "   << q2.get_device().get_info<info::device::name>() << "\n";
cout << " -> Device vendor: " << q2.get_device().get_info<info::device::vendor>() << "\n";

queue q3( gpu_selector_v );
cout<<"\ngpu_selector_v:\n" ;
cout << " -> Device name: "   << q3.get_device().get_info<info::device::name>() << "\n";
cout << " -> Device vendor: " << q3.get_device().get_info<info::device::vendor>() << "\n";

queue q4( accelerator_selector_v );
cout<<"\naccelerator_selector_v:\n" ;
cout << " -> Device name: "   << q4.get_device().get_info<info::device::name>() << "\n";
cout << " -> Device vendor: " << q4.get_device().get_info<info::device::vendor>() << "\n";

queue q5( ext::intel::fpga_emulator_selector_v );
cout<<"\next::intel::fpga_emulator_selector{}:\n" ;
cout << " -> Device name: "   << q5.get_device().get_info<info::device::name>() << "\n";
cout << " -> Device vendor: " << q5.get_device().get_info<info::device::vendor>() << "\n";
  

queue q6( ext::intel::fpga_selector_v );
cout<<"\next::intel::fpga_selector{}\n" ;
cout << " -> Device name: "   << q6.get_device().get_info<info::device::name>() << "\n";
cout << " -> Device vendor: " <<q6.get_device().get_info<info::device::vendor>() << "\n";
/*
queue q7( host_selector{} ); // deprecated in oneAPI 2023. May not be accessible after oneAPI 2023.0.0 release
cout<<"\nhost_selector{}:\n" ;
cout << " -> Device name: "   << q7.get_device().get_info<info::device::name>() << "\n";
cout << " -> Device vendor: " << q7.get_device().get_info<info::device::vendor>() << "\n";
*/


    
/*
output_dev_info( device{ default_selector_v}, "\n default_selector" );
output_dev_info( device{ cpu_selector_v}, "\ncpu_selector" );
output_dev_info( device{ gpu_selector_v}, "\ngpu_selector" );
output_dev_info( device{ accelerator_selector_v},"\naccelerator_selector" );
output_dev_info( device{ ext::intel::fpga_emulator_selector{}}, "\nfpga_emulator_selector" );
//output_dev_info( device{ ext::intel::fpga_selector{}}, "\nfpga_selector" );
//output_dev_info( device{ host_selector}, "\nhost_selector" ); // deprecated in oneAPI 2023. May not be accessible after oneAPI 2023.0.0 release
*/

return 0;
}

/*
void output_dev_info( const device& dev, const std::string& selector_name) 
{
std::cout << selector_name << ": Selected device name: " <<dev.get_info<info::device::name>() << "\n";
std::cout << " Selected device vendor: " <<dev.get_info<info::device::vendor>() << "\n";
}
*/
