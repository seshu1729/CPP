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
constexpr int N = 100;

vector<int> v(N,10);
int R=50;
queue gpuQ(gpu_selector_v);
queue cpuQ(cpu_selector_v);

buffer<int,1> bufgpu(v.data(), R);
buffer<int,1> bufcpu(v.data()+50, R);

gpuQ.submit([&](handler &h){
auto agpu = bufgpu.get_access<dp_rw>(h);
h.parallel_for (R, [=](auto i){
agpu[i]+=2;
});
});

cpuQ.submit([&](handler &h){
auto out = stream(1024, 1024 * 2, h);
auto acpu = bufcpu.get_access<dp_rw>(h);
h.parallel_for(R, [=](auto i){
acpu[i]-=2;
out <<i[0]<<" = "<<acpu[i[0]]<<"\n" ; 
});
});

auto gpu = bufgpu.get_access<dp_r>() ;
auto cpu = bufcpu.get_access<dp_r>() ;

for(int i = 0; i < N/2; i++)
{
    cout<<"gpu["<<i<<"] = "<<gpu[i]<<"\t";
    cout<<"cpu["<<i<<"] = "<<cpu[i]<<"\n";
}

return 0;

}