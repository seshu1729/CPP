#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;
using namespace std;

int main() 
{
    constexpr int N=2; 
    vector<int> a{1,2,3,4,5,6,7,8};
    vector<int> b{2,2,2,2,2,2,2,2};
    vector<int> c{0,0,0,0,0,0,0,0};
    buffer<int,3> a1(a.data(),range<3> (N,N,N));
    buffer<int,3> b1(b.data(),range<3> (N,N,N));
    buffer<int,3> c1(c.data(),range<3> (N,N,N));
    
    queue q;
    cout << "Selected device name: " <<q.get_device().get_info<info::device::name>() << "\n";
    q.submit([&](handler &h){
        accessor a2(a1,h);
        accessor b2(b1,h);
        accessor c2(c1,h);
        
        h.parallel_for(range{N,N,N}, [=](id<3> idx)
                       {
                           int i=idx[0];
                           int j=idx[1];
                           int k=idx[2];
                           
                           c2[i][j][k] = a2[i][j][k] + b2[i][j][k];
                       });
    }).wait();
    
    host_accessor x(c1);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            for(int k=0;k<N;k++){
                cout<<"x["<<i<<"]["<<j<<"]["<<k<<"] = " <<x[i][j][k] <<" " ;
            }
            cout<<"\t";
        }
        cout<<"\n";
    }
        

    return 0;
}
