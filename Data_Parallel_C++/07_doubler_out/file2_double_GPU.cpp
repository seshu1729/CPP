#include <CL/sycl.hpp>
#include <iostream>

using namespace cl::sycl;
using namespace std;

static const int N = 8;

int main()
{
queue q{gpu_selector_v};
cout << "Device: " << q.get_device().get_info<info::device::name>() << std::endl;
float *data = malloc_shared<float>(N, q);

for(int i=0; i<N; i++) 
{
    data[i] = i*2.6;
}

q.submit([&](handler& h) {
auto out = stream(1024, 1024 * 2, h);

h.parallel_for(range(N), [=] (auto i)
{
data[i] *= 2.6666;
out <<"data["<<i[0]<<"] = "<<data[i]<<"\n" ; 
});
}).wait();

cout<<"\n" ;

for(int i=0; i<N; i++)
{
    cout << data[i] << "\n";
}
    
return 0;
}
