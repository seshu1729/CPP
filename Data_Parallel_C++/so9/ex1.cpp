#include <CL/sycl.hpp>
#include <iostream>

using namespace sycl;

int main() {
  constexpr size_t width = 640;
  constexpr size_t height = 480;

  queue q;

  // Create an image object with 8-bit unsigned integer pixels
  image<3> img{ range<3>{width, height, 3} };

  // Write pixel values to the image
  q.submit([&](handler& h) {
    auto acc = img.get_access<access::mode::write>(h);

    for (size_t y = 0; y < height; ++y) {
      for (size_t x = 0; x < width; ++x) {
        acc[x][y][0] = x % 256;  // red
        acc[x][y][1] = y % 256;  // green
        acc[x][y][2] = 0;        // blue
      }
    }
  });

  // Read back pixel values from the image
  q.submit([&](handler& h) {
    auto acc = img.get_access<access::mode::read>(h);

    for (size_t y = 0; y < height; ++y) {
      for (size_t x = 0; x < width; ++x) {
        std::cout << acc[x][y][0] << "," << acc[x][y][1] << "," << acc[x][y][2] << " ";
      }
      std::cout << "\n";
    }
  });

  return 0;
}
