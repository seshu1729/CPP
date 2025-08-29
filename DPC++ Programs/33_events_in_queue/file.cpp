#include <CL/sycl.hpp>
using namespace cl::sycl;
using namespace std;

static const int N = 1024;

int main() 
{
    queue q;
    cout << "Device Name: " << q.get_device().get_info<info::device::name>() << "\n";
    
    
    //auto *data1 = static_cast<int *>(malloc(N * sizeof(int)));
    //auto data1 = static_cast<int *>(malloc(N * sizeof(int)));
    int *data1 = static_cast<int *>(malloc(N * sizeof(int)));
    int *data2 = static_cast<int *>(malloc(N * sizeof(int)));
    
    for (int i = 0; i < N; i++)
    {
        data1[i] = 25;
        data2[i] = 27;
    }
    
    auto data1_device = malloc_device<int>(N, q);
    auto data2_device = malloc_device<int>(N, q);
    
    cout<<"e1 is used for copying data1 to data1_device\n";
    auto e1 = q.memcpy(data1_device, data1, N * sizeof(int));
    
    cout<<"e2 is used for copying data2 to data2_device\n";
    auto e2 = q.memcpy(data2_device, data2, N * sizeof(int));
    
    cout<<"e3 performs square root operartion on data1_device after e1\n";
    auto e3 = q.parallel_for(N, e1, [=](auto i) { 
        data1_device[i] = sqrt(data1_device[i]);
    });
    
    cout<<"e4 performs cubic root operartion on data2_device after e2\n";
    auto e4 = q.parallel_for(N, e2, [=](auto i) { 
        data2_device[i] = cbrt(data2_device[i]); 
    });
    
    cout<<"e5 performs addition of data1_device and data2_device\n";
    auto e5 = q.parallel_for(N, {e3,e4}, [=](auto i) { data1_device[i] += data2_device[i]; });
    
    
    q.memcpy(data1, data1_device, N * sizeof(int), e5).wait();
    
    
    cout<<"verifying the results with data1....\n";
    int fail = 0;
    for (int i = 0; i < N; i++)
    {
        if(data1[i] != 8)
        {
            fail = 1;
            break;
        }
    }
    
    if(fail == 1)
    {
        cout << " FAIL !\n";
    }
    
    else
    {
        cout << " PASS !\n";
    }
    
    free(data1_device, q);
    free(data2_device, q);
    
    return 0;
}
