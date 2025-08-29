#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cl::sycl;

int main()
{
    vector<float> dA{ 7, 5, 16, 8 }, dB{ 8, 16, 5, 7 }, dO{ 0, 0, 0, 0 };
    try{
        queue gpuQueue(gpu_selector{}, async_handler{});
        buffer bufA{dA};
        buffer bufB{dB};
        buffer bufO{dO};
        gpuQueue.submit([&](handler &cgh) {
            auto inA = accessor{bufA, cgh, read_only};
            auto inB = accessor{bufB, cgh, read_only};
            auto out = accessor{bufO, cgh, write_only};
            cgh.single_task(bufO.get_range(), [=](id<1> i) {
                out[i] = inA[i] + inB[i];
            });
        }).wait();
        gpuQueue.throw_asynchronous();
    }
    catch (const exception& e)
    {
        cout << "Exception caught: " << e.what() << "\n";
    }
    return 0;
}
    