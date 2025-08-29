#include <CL/sycl.hpp>
using namespace cl::sycl;
using namespace std;

static constexpr size_t N = 256; // Global size
static constexpr size_t B = 64;  // Work-group size

int main()
{
    queue q;
    cout << "Device name : " << q.get_device().get_info<info::device::name>() << "\n\n";
    
    //int *data = malloc_shared<int>(N, q);
    auto *data = malloc_shared<int>(N, q);
    for(int i=0; i<N; i++)
    {
        data[i] = i;
    }
    
    cout<<"Input data is..\n\n";
    for(int i=0; i<N; i++)
    {
        cout << data[i] << "\t";
    }
    
    cout<<"\n\nUsing sub_group in parallel_for\n";
    cout<< "Writing sub_group item values to broadcast value at index 3\n";
    q.parallel_for(nd_range<1>(N, B), [=](auto item) {
        
        auto sg = item.get_sub_group();
        //auto sg = item.get_group(); 
        auto i = item.get_global_id(0);
        
        data[i] = group_broadcast(sg, data[i], 0);

  }).wait();

  cout<<"\n\nData after group_broadcast..\n\n";
  for(int i=0; i<N; i++)
  {
      cout << data[i] << "\t";
  }
  cout << "\n\n";
  
  free(data, q);
  return 0;
}

