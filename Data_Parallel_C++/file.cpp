
    
#include <CL/sycl.hpp>
using namespace cl::sycl;
using namespace std;

int main()
{
    for (auto dev : device::get_devices())
    {
        if( detail::getSyclObjImpl(dev)->getPlugin().getBackend() == backend::ext_oneapi_level_zero )
        {
            cout << dev.get_info<info::device::name>() << "\n";
        }
    }

    return 0;
}