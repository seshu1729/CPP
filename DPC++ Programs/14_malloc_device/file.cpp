#include <CL/sycl.hpp>
#include <iostream>
#include <sycl/ext/intel/fpga_extensions.hpp>

using namespace std;
using namespace cl::sycl;
static const int N = 16;

int main() 
{
    queue q{ext::intel::fpga_emulator_selector{}};
    cout << "Selected Device : " << q.get_device().get_info<info::device::name>() << "\n";
    //int *data = static_cast<int *>malloc(N * sizeof(int));
    
    int *data = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) data[i] = i;
    
    int *data_device = malloc_device<int>(N, q);                  // Explicit USM allocation using malloc_device
    
    q.memcpy(data_device, data, sizeof(int) * N).wait();          // copy mem from host to device

    q.parallel_for(range(N), [=](id<1> i) { data_device[i] *= 2; }).wait();

    q.memcpy(data, data_device, sizeof(int) * N).wait();          // copy mem from device to host
    
    for (int i = 0; i < N; i++) cout << data[i] << "\n";
    
    free(data_device, q);
    free(data);
    
    return 0;
}
