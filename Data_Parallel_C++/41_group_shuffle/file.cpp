#include <CL/sycl.hpp>
using namespace cl::sycl;
using namespace std;

static constexpr size_t N = 256; // global size
static constexpr size_t B = 64;  // work-group size

int main() 
{
    queue q;
    cout << "Device Name: " << q.get_device().get_info<info::device::name>() << "\n";
    
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
        auto sg = item.get_sub_group();                                                // get_group will not work here
        auto i = item.get_global_id();
        
        data[i] = permute_group_by_xor(sg, data[i], 1);                                //swap adjacent items in array
        // -1 = will return the sub-group values in reverse order
        //  0 = will return the sub-group values with same values
        //  2 = will return the sub-group values by shuffling 2 values
    }).wait();
    
    cout<<"\n\nAfter shuffle..\n\n";
    for (int i = 0; i < N; i++)
    {
        cout << data[i] << "\t";
    }
    
    free(data, q);
    
    return 0;
}