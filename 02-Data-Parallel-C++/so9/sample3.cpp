#include <CL/sycl.hpp>
#include <iostream>

int main()
{
    // Create a host pointer and initialize it with data
    const int size = 16;
    float* host_ptr = new float[size];
    for (int i = 0; i < size; i++) {
        host_ptr[i] = i;
    }

    try {
        // Create a SYCL buffer from the host pointer
        sycl::buffer<float, 1> buf(host_ptr, sycl::range<1>{size});

        // Submit a command group to copy the buffer to the device
        sycl::queue q;
        q.submit([&](sycl::handler& cgh) {
            auto acc = buf.get_access<sycl::access::mode::read>(cgh);
            cgh.copy(acc, host_ptr);
        });

        // Wait for the command group to finish and check for errors
        q.wait_and_throw();

        // Print the contents of the buffer
        std::cout << "Buffer contents:\n";
        for (int i = 0; i < size; i++) {
            std::cout << host_ptr[i] << " ";
        }
        std::cout << std::endl;

    }
    catch (const sycl::exception& exception) {
        std::cout << "SYCL exception caught: " << exception.what();
        return 1;
    }

    // Free the host pointer
    delete[] host_ptr;

    return 0;
}
