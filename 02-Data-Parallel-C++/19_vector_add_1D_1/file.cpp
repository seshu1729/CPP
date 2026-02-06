#include <CL/sycl.hpp>
#include <sycl/ext/intel/fpga_extensions.hpp>
using namespace sycl;
using namespace std;

int main() 
{

//std::vector<float> A(5), B(5), C(5); ==> a,b,c data
std::vector<double> A(10,2.5), B(10,3.35), C(10);

{

buffer bufA {A}, bufB {B}, bufC {C};
queue q( ext::intel::fpga_emulator_selector{} );
//queue q(gpu_selector_v);    //error: Double type is not supported on this platform
cout << "Selected device name: " <<q.get_device().get_info<info::device::name>() << "\n";

q.submit([&](handler &h) 
{
auto X = bufA.get_access(h, read_only);
auto Y = bufB.get_access(h, read_only);
auto Z = bufC.get_access(h, write_only);
h.parallel_for(10, [=](auto i)
{
Z[i] = X[i] + Y[i];
});
});

}
    
for (int i = 0; i < 10 ; i++)
{
cout << "C[" << i << "] = " << C[i] << std::endl;
}
return 0;

}
