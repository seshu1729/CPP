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
queue cpuQ(cpu_selector_v);

// buffer<int,1> bufgpu(v.data(), R);
buffer<int,1> bufcpu(v.data(), R);

cpuQ.submit([&](handler &h)
{
    auto out = stream(1024, 1024 * 2, h);
    auto acpu = bufcpu.get_access<dp_rw>(h);
    auto agpu = bufcpu.get_access<dp_rw>(h);

    h.parallel_for (R, [=](auto i){
        acpu[i]+=2;
    });
    
    
    h.parallel_for(R, [=](auto i){
        acpu[i]-=2;
    });
});

    ============
    
    h.parallel_for(range<3> { N, N, N },
                     [=](id<3> index){
      int gid = idx.get_global_id(0);
      acpu[gid] = gid;
    });
    h.parallel_for(range<1>(R), [=](id<1> idx) {
      int gid = R + idx.get_global_id(1);
      acpu[gid] = gid;
    });
  });

=========
    
auto cpu = bufcpu.get_access<dp_r>() ;

for(int i = 0; i < N/2; i++)
{
    cout<<"gpu["<<i<<"] = "<<cpu[i]<<"\t";
    cout<<"cpu["<<i<<"] = "<<cpu[i+50]<<"\n";
}

return 0;

}