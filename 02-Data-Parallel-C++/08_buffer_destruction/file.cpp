//dpcpp -fsycl-unnamed-lambda buffer_destruction.cpp

#include <array>
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
constexpr int N = 10;
vector<int> v(N,6);

queue q;
{
//buffer buf(v.data(), range(N));
buffer<int, 1> buf(v.data(), range(N));
q.submit([&](handler &h) 
{
auto a = buf.get_access<dp_rw>(h);
auto out = stream(1024, 1024*2, h);
h.parallel_for(range(10), [=](auto i) 
{
a[i] -= 2;
out<< "a["<<i[0]<<"] = " <<a[i] <<"\n";
});
});
}//buffer will be destructed here only

for (int i = 0; i < N; i++)
{
    cout << v[i] << "\n";
}

return 0;
}