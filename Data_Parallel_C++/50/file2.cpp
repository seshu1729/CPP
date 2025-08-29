#include<iostream>
#include<CL/sycl.hpp>

using namespace std;
using namespace sycl;

void add(cl::sycl::accessor<int, 1, cl::sycl::access::mode::write> p, int x);

class Add 
{
    public:
    Add(accessor<int> acc) : data_acc(acc) {}
    
    void operator()(id<1> i) {
        data_acc[i] = data_acc[i] + 1;
    }
    
    private:
    accessor<int> data_acc;
};

int main() 
{
    constexpr size_t size = 16;
    std::array<int, size> data;
    for (int i = 0; i < size; i++)
        data[i] = i;
    
    {
        buffer data_buf{data};
        queue Q{ host_selector{} };
        std::cout << "Running on device: "<< Q.get_device().get_info<info::device::name>() << "\n";
        
        Q.submit([&](handler& h) {
            accessor data_acc {data_buf, h};
            h.parallel_for(size, Add(data_acc));
        });
    }
    return 0;
}