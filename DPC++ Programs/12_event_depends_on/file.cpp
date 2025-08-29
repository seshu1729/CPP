//icpx -fsycl -fsycl-unnamed-lambda usm2.cpp

#include<CL/sycl.hpp>
#include<vector>
#include<iostream>

constexpr auto dp_r = cl::sycl::access::mode::read;
constexpr auto dp_rw = cl::sycl::access::mode::read_write;
constexpr auto dp_w = cl::sycl::access::mode::write;
using namespace cl::sycl;
using namespace std;

int main()
{
int *a, *d_a;
queue q;
auto ctx = q.get_context();
constexpr int N = 100;
a = static_cast<int *>(malloc(sizeof(int)*N));
d_a = static_cast<int *>(malloc_device(sizeof(int)*N, q.get_device(), ctx));
    
for(int i = 0; i < N; i++)
{
    a[i] = i;
}

auto e1 = q.memcpy(d_a, a, sizeof(int)*N);
auto e2 = q.submit([&](handler &h) 
{
h.depends_on(e1);

h.parallel_for(range<1>(N), [=](id<1> i){
d_a[i]++;
});
});

q.submit([&](handler &h)
{
h.depends_on({e1,e2});
h.memcpy(a, d_a, sizeof(int)*N);
}).wait();

for(int i = 0; i < N; i++) 
{
    cout<<a[i]<<"\n";
}

free(a);
free(d_a,ctx);

return 0;
}