#include <CL/sycl.hpp>
#include <iostream>
using namespace cl::sycl;
using namespace std;

int main() 
{
constexpr int N = 10;
vector<int> v(N, 10);

buffer buf(v);
    
queue q;
q.submit([&](handler& h) 
{
//auto a = buf.get_access<access::mode::read_write>(h);
accessor a(buf, h,read_write); //Will work without read_write access
auto out = stream(1024, 1024*2, h);
h.parallel_for(range(N), [=](auto i)
{
a[i] -= 2;
out<< "a["<<i[0]<<"] = " <<a[i] <<"\n";
});
});
    
host_accessor b(buf, read_only);
    
for (int i = 0; i < N; i++)
{
cout <<"b[i] "<< b[i] <<" ,v[i] "<< v[i] << "\n";
}

return 0;
}