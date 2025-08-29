#include <CL/sycl.hpp>

int main() {
  sycl::range<1> my_range(10);
  sycl::id<1> my_id(3);
  sycl::item<1> my_item(my_id, my_range);
  std::cout << "Global id = " << my_item.get_id(0) << std::endl;
  std::cout << "Local id = " << my_item.get_local_id(0) << std::endl;
  return 0;
}
