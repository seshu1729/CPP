#include <CL/sycl.hpp>
#include <iostream>
#include <limits>
#include <vector>
using namespace cl::sycl;
using namespace std;

int main() 
{
  property_list properties{sycl::property::queue::enable_profiling()};
  auto q = queue(cpu_selector_v, properties);

  cout<< "  Platform: "<< q.get_device().get_platform().get_info<info::platform::name>() <<"\n";

  const int num_ints = 1024 * 1024;
  const size_t num_bytes = num_ints * sizeof(int);
  const int alignment = 8;

  auto src = aligned_alloc(alignment, num_bytes);  // Alloc memory on host
  memset(src, 1, num_bytes);

  auto dst = malloc_device<int>(num_ints, q);      // Alloc memory on device
  q.memset(dst, 0, num_bytes).wait();

  auto event = q.memcpy(dst, src, num_bytes);      // Copy from host to device
  event.wait();

  auto end = event.get_profiling_info<sycl::info::event_profiling::command_end>();
  auto start = event.get_profiling_info<sycl::info::event_profiling::command_start>();

  cout << "Elapsed time: " << (end - start) / 1.0e9 << " seconds\n" ;

  free(dst, q);
}