#include <CL/sycl.hpp>
#include <iostream>

using namespace cl::sycl;

int main() {
  const int width = 640;
  const int height = 480;
  
  // Create a buffer to store the image data
  std::vector<float> img_data(width * height * 4, 0.0f);
  buffer<float, 2> img_buf(img_data.data(), range<2>(width, height));
  
  // Fill the buffer with a simple gradient pattern
  queue q;
  q.submit([&](handler& cgh) {
    auto img_acc = img_buf.get_access<access::mode::write>(cgh);
    cgh.parallel_for<class gradient>(range<2>(width, height), [=](id<2> i) {
      float intensity = (i[0] + i[1]) / float(width + height);
      img_acc[i] = 1.0f;
    });
  });
  
  // Create an image object from the buffer
  image<2> img(img_buf.get_access<access::mode::read>());
  
  // Perform some basic image processing operations
  q.submit([&](handler& cgh) {
    auto img_acc = img.get_access(cgh);
    cgh.parallel_for<class processing>(range<2>(width, height), [=](id<2> i) {
      if (i[0] < width/2) {
        img_acc[i][0] *= 2.0f; // Double the red channel
      } else {
        img_acc[i][1] *= 2.0f; // Double the green channel
      }
    });
  });
  
  // Display the results
  q.wait();
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      std::cout << img.read(x, y)[0] << " ";
    }
    std::cout << std::endl;
  }
  
  return 0;
}

