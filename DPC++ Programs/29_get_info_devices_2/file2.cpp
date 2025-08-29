#include <CL/sycl.hpp>
using namespace sycl;
using namespace std;

int main()
{
    for (auto dev : device::get_devices())
        cout << dev.get_info<info::device::name>() << "\n";
    
    
    
    
    auto C = context(device::get_devices());
    
    for (auto &D2 : device::get_devices()) 
    {
        auto Q2 = queue(D2);
        int *a2 = malloc_shared<int>(10, Q2);
        for(int i=0; i<10; i++) a2[i] = i;
        cout << "Selected device: " <<Q2.get_device().get_info<info::device::name>() << "\n\n";


        Q2.single_task([=](){
            for(int i=0;i<10;i++) a2[i] *= 3;
        }).wait();
    }
    
    for (auto &D : device::get_devices()) 
    {
        auto Q = queue(C, D);
        // All queues share the same context, data can be shared across queues.
        int *a = malloc_shared<int>(10, Q);
        for(int i=0; i<10; i++) a[i] = i;
        cout << "Selected device: " <<Q.get_device().get_info<info::device::name>() << "\n\n";


        Q.single_task([=](){
            for(int i=0;i<10;i++) a[i] *= 3;
        }).wait();
    }
    
    

    return 0;
}