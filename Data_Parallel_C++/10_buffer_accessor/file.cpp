#include <CL/sycl.hpp>
#include <array>
#include <iostream>
using namespace sycl;
using namespace std;

int main() 
{
constexpr int N = 10;
queue Q;

auto A = (int *) malloc(N * sizeof(int));
auto B = (int *) malloc(N * sizeof(int));
auto C = (int *) malloc(N * sizeof(int));
for (int i = 0; i < N; i++) 
{
A[i] = i; 
B[i] = 2*i;
} 

buffer<int, 1> Ab(A, range<1>{N});
buffer<int, 1> Bb(B, range<1>{N});
buffer<int, 1> Cb(C, range<1>{N});
Q.submit([&] (handler& h) 
{
accessor aA(Ab, h,read_only);
accessor aB(Bb, h,read_only);
accessor aC(Cb, h,write_only);
h.parallel_for(range<1>(N) , [=] (id<1> i) 
{
aC[i] = aA[i] + aB[i];
});
});

    
host_accessor x(Cb, read_only);
for(int i=0; i<N; i++) 
    cout << x[i] << std::endl;

    return 0;
}
