#include <CL/sycl.hpp>
using namespace std;
using namespace cl::sycl;

int main()
{
    constexpr int N=1024;
    constexpr int WG=256;
    
    vector<int> v(N,10);
    auto R = range<1>(N);
    buffer<int, 1> buf(v.data(), R);
    queue q(gpu_selector{}, async_handler{});
    q.submit([&](handler &h){
        auto a = buf.get_access(h, read_write);
        h.parallel_for(nd_range<1>(R, range<1>(WG)), [=](nd_item<1> it){
            auto i = it.get_global_id();
            a[i] = i[0];
        });
    }).wait_and_throw();
    auto b = buf.get_access(read_only);
    for(int i = 0; i < N; i++)
    {
        cout<<b[i]<<"\n";
    }
    return 0;
}