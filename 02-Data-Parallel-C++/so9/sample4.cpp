#include <CL/sycl.hpp>
#include <iostream>
#include <fstream>
#include <array>
#include <string>

namespace sycl = cl::sycl;

int main(int argc, char **argv) {
    sycl::default_selector_v device_selector;
    sycl::device_queue q(device_selector);
    
    constexpr std::size_t size = 32;
    std::array<float, size> data;
    std::fill(data.begin(), data.end(), 0.5f);
    
    sycl::range<2> img_range{size, size};
    sycl::image<float, 2> img(sycl::image_allocator(q.get_context(), q.get_device()), sycl::image_channel_order::rgba, sycl::image_channel_type::fp32, img_range);
    sycl::range<1> range{size};
    sycl::buffer<float, 1> buf(data.data(), range);
    sycl::accessor<float, 1, sycl::access::mode::read_write, sycl::access::target::global_buffer> acc(buf);
    
    q.submit([&](sycl::handler &cgh) {
        auto write = img.get_access<sycl::access::mode::write>(cgh);
        auto read = acc.get_access<sycl::access::mode::read>(cgh);
        cgh.parallel_for<class ImageKernel>(img_range, [=](sycl::id<2> idx) {
            float val = read[idx[0]];
            write.write(sycl::int2(idx), sycl::float4(val, val, val, 1.0f));
        });
    });
    
    auto read = img.get_access<sycl::access::mode::read>();
    std::ofstream file("output.ppm");
    file << "P3\n" << size << " " << size << "\n255\n";
    for (std::size_t j = 0; j < size; ++j) {
        for (std::size_t i = 0; i < size; ++i) {
            sycl::float4 color = read.read(sycl::int2(i, j));
            file << static_cast<int>(color.x() * 255) << " "
                 << static_cast<int>(color.y() * 255) << " "
                 << static_cast<int>(color.z() * 255) << " ";
        }
        file << "\n";
    }
    
    return 0;
}
