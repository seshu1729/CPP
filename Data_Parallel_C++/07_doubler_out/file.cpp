#include <CL/sycl.hpp>
#include <iostream>

using namespace cl::sycl;
using namespace std;

static const int N = 65536;

int main()
{
queue q;
cout << "Device: " << q.get_device().get_info<info::device::name>() << std::endl;
int *data = malloc_shared<int>(N, q);

for(int i=0; i<N; i++) 
{
    data[i] = i;
}

q.submit([&](handler& h) {
auto out = stream(1024, 1024*2, h);

//h.parallel_for(range<1>(N), [=] (id<1> i)
//h.parallel_for(range<1>(N), [=] (auto i)
h.parallel_for(range(N), [=] (auto i)
{
data[i] *= 2;
out <<"data["<<i[0]<<"] = "<<data[i]<<"\n" ; 
//out <<"data["<<i<<"] = "<<data[i]<<"\n" ;
});
}).wait();

cout<<"\n" ;

for(int i=0; i<N; i++)
{
    cout << data[i] << "\n";
}
    
return 0;
}
