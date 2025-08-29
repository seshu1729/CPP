#include <CL/sycl.hpp>
using namespace sycl;
using namespace std;

int main()
{
    for (auto dev : device::get_devices())
        cout << dev.get_info<info::device::name>() << "\n";

    return 0;
}