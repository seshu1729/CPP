#include <CL/sycl.hpp>
using namespace sycl;
using namespace std;
constexpr int N = 10;
int main()
{
    queue Q;
    int *host_array = malloc_host<int>(N, Q);
    int *shared_array = malloc_shared<int>(N, Q);
    
    for (int i = 0; i < N; i++) 
    {
        host_array[i] = i;                             // Initialize hostArray on host
    }
    
    cout<<"access sharedArray and hostArray on device\n";
    Q.submit([&](handler &h) {
        h.parallel_for(N, [=](id<1> i) {
            // access sharedArray and hostArray on device
            shared_array[i] = host_array[i] + 1;
        });
    }).wait();
    
    
    cout<<"access sharedArray and hostArray on host\n";
    for (int i = 0; i < N; i++) 
    {
        host_array[i] = shared_array[i];              // read sharedArray on host
        shared_array[i] = shared_array[i] + 1;        // write sharedArray on host
        cout<< shared_array[i]<<"\n" ;
        
        shared_array[i] = host_array[i];              // read hostArray on host
        host_array[i] = host_array[i] + 1;            // write hostArray on host
        cout<< host_array[i]<<"\n" ;
    }

  free(shared_array, Q);
  free(host_array, Q);
  return 0;
}