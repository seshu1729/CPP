#include <CL/sycl.hpp>
#include <iostream>

using namespace cl::sycl;

constexpr int N = 64;

int main() {
  float data[N][N][N];
  buffer<float, 3> buf(data, range<3>{N, N, N});

  queue q;

  // run kernel 1 on the first half of the array
  q.submit([&](handler &h) {
    auto range = range<3>{N/2, N, N};
    accessor<float, 3, access::mode::write, access::target::global_buffer> acc(buf, h);
    h.parallel_for(range, [=](id<3> idx) {
      acc[idx] = 1.0f; // example code, replace with your actual kernel code
    });
  });

  // run kernel 2 on the second half of the array
  q.submit([&](handler &h) {
    auto range = range<3>{N/2, N, N};
    accessor<float, 3, access::mode::write, access::target::global_buffer> acc(buf, h);
    h.parallel_for(range, [=](id<3> idx) {
      acc[idx] = 2.0f; // example code, replace with your actual kernel code
    });
  });

  q.wait();

  // print out the first and last elements of the array to verify the results
  std::cout << "data[0][0][0] = " << data[0][0][0] << std::endl;
  std::cout << "data[" << N-1 << "][" << N-1 << "][" << N-1 << "] = " << data[N-1][N-1][N-1] << std::endl;

  return 0;
}
