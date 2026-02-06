#include <CL/sycl.hpp>
#include <iostream>
using namespace std;
using namespace cl::sycl;

#define size N 1024
int main()
{
    
std::vector<int> data(N, N);
  queue q;
  buffer<int, 1> buf(data.data(), range<1>(N));

  q.submit([&](handler& cgh) {
    auto acc = buf.get_access<access::mode::read_write>(cgh);

 

    cgh.parallel_for(range<1>(N), [=](id<1> i) {
      acc[i] *= 2;
    });
  });


  q.submit([&](handler& cgh) {
    auto acc = buf.get_access<access::mode::read_write>(cgh);

    cgh.parallel_for(range<1>(N), [=](id<1> i) {
      acc[i] += 1;
    });
  });

 

q.wait();
    
     return 0;
}