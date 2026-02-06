#include <CL/sycl.hpp>
using namespace cl::sycl;
using namespace std;

static constexpr size_t N = 256; // global size
static constexpr size_t B = 64;  // work-group size

int main()
{
    queue q;
    cout << "Device Name : " << q.get_device().get_info<info::device::name>() << "\n\n";
    
    //int *data = malloc_shared<int>(N, q);
    auto *data = malloc_shared<int>(N, q);
    
    for (int i = 0; i < N; i++)
    {
        data[i] = i;
    }
    
    cout<<"Input data is..\n\n";
    for (int i = 0; i < N; i++)
    {
        cout << data[i] << "\t";
    }
    
    q.parallel_for(nd_range<1>(N, B), [=](auto item) {
        auto sg = item.get_sub_group();
        //auto sg = item.get_group();
        auto i = item.get_global_id();
        
        int result = reduce_over_group(sg, data[i], std::plus<>());     // Adds all elements in sub_group using sub_group collectives
        //int result = reduce_over_group(sg, data[i], maximum<>());     // returns maximum value in sub_group
        //int result = reduce_over_group(sg, data[i], minimum<>());     // returns minimum value in sub_group
        
        if (sg.get_local_id()[0] == 0)                               // write sub_group sum in first location for each sub_group
        {
            data[i] = result;
        }
        else
        {
            data[i] = 0;
        }
    }).wait();
    
    cout<<"\n\nAfter reduction..\n\n";
    for (int i = 0; i < N; i++)
    {
        cout << data[i] << "\t";
    }
    
    cout<<"\n\n";
    
    free(data, q);
    return 0;
}