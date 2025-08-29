#include <CL/sycl.hpp>
using namespace cl::sycl;
using namespace std;

static constexpr size_t N = 64; // global size
static constexpr size_t B = 64; // work-group size

int main()
{
    queue q;
    cout << "Device Name : " << q.get_device().get_info<info::device::name>() << "\n\n";
    
    
    auto s1 = q.get_device().get_info<info::device::sub_group_sizes>();
    cout << "Supported Sub-Group Sizes : ";
    for (int i=0; i<s1.size(); i++)
    {
        cout << s1[i] << ", ";
    }
    
    auto max = std::max_element(s1.begin(), s1.end());
    cout << "\nMax Sub-Group Size        : " << max[0] << "\n\n";
    
    cout<<"Querying sub_group and printing sub_group info once per sub_group"<<"\n";
    q.submit([&](handler &h) {
        auto out = stream(1024, 512, h);
        h.parallel_for(nd_range<1>(N, B), [=](auto item)[[intel::reqd_sub_group_size(32)]] {
            auto sg = item.get_sub_group();
            if (sg.get_local_id()[0] == 0)
            {
                out << "sub_group id: " << sg.get_group_id() << " of "<< sg.get_group_range() << ", size=" << sg.get_local_range()[0]<< "\n";
            }
        });
    }).wait();
    return 0;
}
