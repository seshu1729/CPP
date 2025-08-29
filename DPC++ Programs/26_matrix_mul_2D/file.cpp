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
    constexpr int P = 4;
    
    queue q;
    
    cout << "\nSelected device name: " <<q.get_device().get_info<info::device::name>() << "\n";
    cout << "Selected device vendor: " <<q.get_device().get_info<info::device::vendor>() << "\n";
    
    buffer<float, 2> a_buf(range(M, N));
    buffer<float, 2> b_buf(range(N, P));
    buffer<float, 2> c_buf(range(M, P));
    
    q.submit([&](auto &h) {
        accessor a_acc(a_buf, h, write_only);
        h.parallel_for(range(M, N), [=](auto index) {
            a_acc[index] = 1.0f;
        });
    });
    
    q.submit([&](auto &h) {
        accessor b_acc(b_buf, h, write_only);
        h.parallel_for(range(N, P), [=](auto index) {
            b_acc[index] = index[0] + 1.0f;
        });
    });
    
    q.submit([&](auto &h) {
        accessor a_acc(a_buf, h, read_only);
        accessor b_acc(b_buf, h, read_only);
        accessor c_acc(c_buf, h, write_only);
        
        h.parallel_for(range(M, P), [=](auto index) {
            int row = index[0]; //index[0] taking values from 0 to M
            int col = index[1]; //index[1] taking values from 0 to P
            float sum = 0.0f;
            
            for (int i = 0; i < N; i++) 
            {
                sum += a_acc[row][i] * b_acc[i][col];
                //c_acc[index] += a_acc[row][i] * b_acc[i][col];
            }
            
            c_acc[index] = sum;
        });
    });
    
    host_accessor e(a_buf, read_only);    
    host_accessor f(b_buf, read_only);    
    host_accessor g(c_buf, read_only);
    
    cout<<"\nInput Matrix A\n" ;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < P; j++){
            cout<<e[i][j]<<" " ;
        }
        cout<<"\n" ;
    }
    
    cout<<"\nInput Matrix B\n" ;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < P; j++){
            cout<<f[i][j]<<" ";
        }
        cout<<"\n" ;
    }
    
    
    cout<<"\nOutput Matrix C\n" ; 
    for (int i = 0; i < M; i++){
        for (int j = 0; j < P; j++){
            cout<<g[i][j]<<" ";
        }
        cout<<"\n" ; 
    }
    
    return 0;
}
