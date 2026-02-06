#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;
using namespace std;

constexpr int N = 20;

int main() 
{
    queue Q;
    int* host_array = malloc_host<int>(N, Q);
    for(int i = 0; i < N; i++) {
        host_array[i] = i;
    }
    cout<< "\nAccess hostArray on host"<<"\n" ;
    
    for(int i = 0; i < N; i++) {
        cout<< host_array[i] <<"\t";
    }
    
    Q.submit([&](handler& h) {
        auto out = stream(1024, 1024 * 2, h);
        cout<<"\nAccess hostArray on device"<<"\n" ;
        
        h.parallel_for(N, [=](id<1> i) {
            host_array[i] = host_array[i] + 1;
            out<<host_array[i]<<"\t";
        });
    });

  Q.wait();

  free(host_array, Q);
  return 0;
}