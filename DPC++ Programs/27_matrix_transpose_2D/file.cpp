#include <CL/sycl.hpp>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;
using namespace sycl;

int main()
{
    constexpr int M = 4;
    constexpr int N = 4;
    
    queue q;
    
    buffer<float, 2> a_buf(range(M, N));
    buffer<float, 2> b_buf(range(M, N));
    
    q.submit([&](auto &h) {
        accessor a_acc(a_buf, h, write_only);
        h.parallel_for(range(M, N), [=](auto index) {
            a_acc[index] = 1.0f + index[0] ;
        });
    });
    
    q.submit([&](auto &h) {
        accessor a_acc(a_buf, h, read_only);
        accessor b_acc(b_buf, h, write_only);
        h.parallel_for(range(M, N), [=](id<2> index) {
            int i = index[0]; //index[0] taking values from 0 to M
            int j = index[1]; //index[1] taking values from 0 to P
            b_acc[i][j]  = a_acc[j][i]; 
        });
    });
    
    host_accessor e(a_buf, read_only);    
    host_accessor f(b_buf, read_only);
    
    cout<<"Input Matrix \n" ;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            cout<<e[i][j]<<" " ;
        }
        cout<<"\n" ;
    }
    
    cout<<"\nTransposed Matrix \n" ;  
    for (int i = 0; i < M; i++){
        for (int j = 0; j < N; j++){
            cout<<f[i][j]<<" ";
        }
        cout<<"\n" ;
    }
    
    return 0;
}
