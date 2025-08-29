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
buffer<float, 2> c_buf(range(M, N));
    
q.submit([&](auto &h) {
    accessor a_acc(a_buf, h, write_only);
    h.parallel_for(range(M, N), [=](auto index) {
        a_acc[index] = 1.0f;
    });
    });

q.submit([&](auto &h) {
    accessor b_acc(b_buf, h, write_only);
    h.parallel_for(range(M, N), [=](auto index) {
        b_acc[index] = index[0] + 1.0f;
      });
    });
    
q.submit([&](auto &h) 
{
accessor a_acc(a_buf, h, read_only);
accessor b_acc(b_buf, h, read_only);
accessor c_acc(c_buf, h, write_only);

h.parallel_for(range(M, N), [=](auto index) 
{
int j = index[0]; //index[0] taking values from 0 to M
float sum = 0.0f;
/*
//for (int i = 0; i < N; i++) 
//{
//sum = a_acc[j][i] + b_acc[j][i];
//c_acc[index] = a_acc[j][i] + b_acc[j][i];
//c_acc[j][i] = a_acc[j][i] + b_acc[j][i];  
*/
c_acc[index] = a_acc[index] + b_acc[index];    
//}

//c_acc[index] = sum;
});
});

host_accessor e(a_buf, read_only);    
host_accessor f(b_buf, read_only);    
host_accessor g(c_buf, read_only);

for (int i = 0; i < M; i++){
for (int j = 0; j < N; j++){
cout<<e[i][j]<<" " ;
}
cout<<"\n" ;
}

cout<<"\n" ;

for (int i = 0; i < M; i++){
for (int j = 0; j < N; j++){
cout<<f[i][j]<<" ";
}
cout<<"\n" ;
}

cout<<"\n" ;    
    
for (int i = 0; i < M; i++){
for (int j = 0; j < N; j++){
cout<<g[i][j]<<" ";
}
cout<<"\n" ; 
}

return 0;
}