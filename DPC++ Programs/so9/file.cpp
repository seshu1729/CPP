#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

using namespace cl::sycl;

int main()
{
  sycl::device device(default_selector_v);
  sycl::queue q(device, sycl::property::queue::in_order{});

  // Create a 512x512 image
sycl::image<2> img(sycl::image_channel_order::rgba, sycl::image_channel_type::unorm_int8, sycl::range<2>(512, 512));

  // Write some data to the image using a kernel
  q.submit([&](sycl::handler& cgh) {
//     auto acc = img.get_access<sycl::access::mode::write>(cgh);
       auto acc { img, cgh, write_only };
    cgh.parallel_for<class write_data>(img.get_range(), [=](sycl::item<2> item) {
      acc.write(item, sycl::float4(item[0], item[1], 0.0f, 1.0f));
    });
  });

  // Read the data from the image to a host buffer
  std::vector<sycl::float4> host_buf(512 * 512);
  q.submit([&](sycl::handler& cgh) {
  //  auto acc = img.get_access<sycl::access::mode::read>(cgh);
      auto acc { img, cgh, read_only };
    cgh.parallel_for<class read_data>(img.get_range(), [=](sycl::item<2> item) {
      host_buf[item.get_linear_id()] = acc.read(item);
    });
  });

  // Wait for the kernels to finish and check for errors
  q.wait_and_throw();

  // Print the first few pixels of the host buffer
  for (int i = 0; i < 10; i++) {
    std::cout << "(" << host_buf[i].x() << ", " << host_buf[i].y() << ", "
              << host_buf[i].z() << ", " << host_buf[i].w() << ")" << std::endl;
  }

  return 0;
}
