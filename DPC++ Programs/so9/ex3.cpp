#include <CL/sycl.hpp>
#include <iostream>

using namespace cl::sycl;

constexpr std::size_t channel_count{4};

using data_type = std::uint16_t;
using usm_allocator_type = sycl::usm_allocator<data_type, sycl::usm::alloc::shared>;

using image_access_type = unsigned int;
using access_vec_t = sycl::vec<image_access_type, channel_count>;

constexpr auto sycl_image_channel_type = sycl::image_channel_type::unsigned_int16; // added extra


int main() {
  const int width = 256;
  const int height = 256;

  // Create a queue
  sycl::queue q;

  // Define an image
    
    
    sycl::range<2> image_range{height, width};
    sycl::image<2> myImage{sycl::image_channel_order::rgba, sycl_image_channel_type, image_range};
    // sycl::image<2> src_image{src_vector.data(), sycl::image_channel_order::rgba, sycl_image_channel_type, image_range};
    //sycl::image<2> myImage(sycl::range<2>(width, height));

  // Create a host array to store the image data
  float hostData[width * height];

  // Write data to the image using sycl::image_accessor
  q.submit([&](sycl::handler& cgh) {
    auto acc = myImage.get_access<access_vec_t,sycl::access::mode::write>(cgh);
    cgh.parallel_for<class WriteImage>(sycl::range<2>(width, height), [=](sycl::item<2> item) {
      //sycl::detail::image_accessor<float, 2, sycl::access::mode::write, sycl::access::target::image> imageAcc(acc);
        sycl::detail::image_accessor<std::uint16_t, 2, sycl::access::mode::write, sycl::access::target::image> imageAcc(acc);

      imageAcc.write(item.get_id(), item.get_id(0) + item.get_id(1) * width);
    });
  });

  // Read data from the image using sycl::image_accessor
  q.submit([&](sycl::handler& cgh) {
    auto acc = myImage.get_access<access_vec_t,sycl::access::mode::read>(cgh);
    cgh.parallel_for<class ReadImage>(sycl::range<2>(width, height), [=](sycl::item<2> item) {
      sycl::detail::image_accessor<float, 2, sycl::access::mode::read, sycl::access::target::image> imageAcc(acc);
      hostData[item.get_id(0) + item.get_id(1) * width] = imageAcc.read(item.get_id());
    });
  });

  // Wait for the kernel to finish
  q.wait_and_throw();

  // Print the data
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      std::cout << hostData[x + y * width] << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}
