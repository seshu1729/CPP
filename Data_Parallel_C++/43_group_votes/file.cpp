#include <CL/sycl.hpp>
using namespace cl::sycl;
using namespace std;

static constexpr size_t N = 32; // global size
static constexpr size_t B = 16; // work-group size

int main()
{
    queue q;
    cout << "Device Name : " << q.get_device().get_info<info::device::name>() << "\n\n";
    
    auto input = malloc_shared<int>(N, q);
    auto all   = malloc_shared<int>(N, q);
    auto any   = malloc_shared<int>(N, q);
    auto none  = malloc_shared<int>(N, q);
    
    for(int i=0; i<N; i++)
    {
        if (i< 10)
        {
            input[i] = 0;
        }
        else
        {
            input[i] = i;
        }
    }
    
    cout<<"Input data is..\n\n";
    for(int i=0; i<N; i++)
    {
        cout << input[i] << "\t";
    }
    
    q.parallel_for(nd_range<1>(N, B), [=](auto item)[[intel::reqd_sub_group_size(8)]] {
        auto sg = item.get_sub_group();
        auto i = item.get_global_id(0);
        
        all[i] = all_of_group(sg, input[i]);
        any[i] = any_of_group(sg, input[i]);
        none[i] = none_of_group(sg, input[i]);
    }).wait();
    
    cout << "\n\noutput from all_of_group :\n";
    for(int i=0; i<N; i++)
    {
        cout << all[i] << "\t";
    }
    
    cout << "\n\noutput from any_of_group :\n";
    for(int i=0; i<N; i++)
    {
        cout << any[i] << "\t";
    }
    
    cout << "\n\noutput from none_of_group :\n";
    for(int i=0; i<N; i++)
    {
        cout << none[i] << "\t";
    }
    
    cout << "\n\n";
    
    free(input, q);
    free(all, q);
    free(any, q);
    free(none, q);
    
    return 0;
}

