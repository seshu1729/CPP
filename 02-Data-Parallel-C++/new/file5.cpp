#include <CL/sycl.hpp>

using namespace sycl;

void kernel1(queue& q, buffer<int, 1>& buf, int offset, int size) {
  q.submit([&](handler& h) {
    auto accessor = buf.get_access<access::mode::read_write>(h);
    h.parallel_for(range<1>(size), [=](id<1> id) {
      const auto i = id[0] + offset;
      accessor[i] = accessor[i] * 2;
    });
  });
}

void kernel2(queue& q, buffer<int, 1>& buf, int offset, int size) {
  q.submit([&](handler& h) {
    auto accessor = buf.get_access<access::mode::read_write>(h);
    h.parallel_for(range<1>(size), [=](id<1> id) {
      const auto i = id[0] + offset;
      accessor[i] = accessor[i] * 3;
    });
  });
}

int main() {
  constexpr int N = 100;
  buffer<int, 1> buf(range<1>{N});
  
  // Fill buffer with data
  {
    auto accessor = buf.get_access<access::mode::write>();
    for (int i = 0; i < N; i++) {
      accessor[i] = i;
    }
  }
  
  // Launch kernel1 for first half of the array
  queue q1;
  kernel1(q1, buf, 0, N / 2);
  
  // Launch kernel2 for second half of the array
  queue q2;
  kernel2(q2, buf, N / 2, N - N / 2);
  
  // Wait for both tasks to complete
  q1.wait();
  q2.wait();
  
  // Print the results
  auto accessor = buf.get_access<access::mode::read>();
  for (int i = 0; i < N; i++) {
    std::cout << accessor[i] << " ";
  }
  std::cout << std::endl;
  
  return 0;
}
