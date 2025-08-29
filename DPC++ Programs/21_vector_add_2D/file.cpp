#include <CL/sycl.hpp>
#include <iostream>
using namespace cl::sycl;
using namespace std;

int main() 
{
    constexpr int N=3; 
    vector<int> a{1,2,3,4,5,6,7,8,9};
    vector<int> b{2,2,2,2,2,2,2,2,2};
    vector<int> c{0,0,0,0,0,0,0,0,0};
    buffer<int,2> a1(a.data(),range<2> (N,N));
    buffer<int,2> b1(b.data(),range<2> (N,N));
    buffer<int,2> c1(c.data(),range<2> (N,N));
    
    queue q;
    cout << "Selected device name: " <<q.get_device().get_info<info::device::name>() << "\n";
    q.submit([&](handler &h){
        accessor a2(a1,h);
        accessor b2(b1,h);
        accessor c2(c1,h);
        auto out = stream(512,1024,h);
        h.parallel_for(range{N,N}, [=](id<2> idx){
        out<<"\na2 = "<<a2[idx];
        });
        
        /*h.parallel_for(range{N,N}, [=](id<2> idx)
                       {
                           int i=idx[0];
                           int j=idx[1];
                           c2[i][j] = a2[i][j] + b2[i][j];
                       });*/
    }).wait();
  
    host_accessor x(c1);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            std::cout<<x[i][j]<<" " ;
        }
        cout<<"\n";
    }

    return 0;
}
