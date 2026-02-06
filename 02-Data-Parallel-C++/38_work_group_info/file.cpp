#include <CL/sycl.hpp>
#include <iostream>
using namespace cl::sycl;
using namespace std;

static constexpr size_t G = 64; // global size
static constexpr size_t W = 32; // work-group size

int main()
{
    queue q;
    cout << "Device Name: " << q.get_device().get_info<info::device::name>() << "\n\n";
    
    q.submit([&](handler &h) {
        auto out = stream(1024, 512, h);
        h.parallel_for(nd_range<1>(G, W), [=](nd_item<1> item) {
            auto sg = item.get_sub_group();
            
            //# querying sub_group and printing the information once per sub_group
            //if (sg.get_local_id()[0] == 15)                                                     // item.get_sub_group().get_local_id();
            if (item.get_global_id()[0] == 31)
            {
                out << " Thread infomation : " << item << "\n";
                 
                out << "  Global ID : " << item.get_global_id() << "\n";                     // item.get_global_linear_id()
                out << "  Local ID in Current Work group : " << item.get_local_id() << "\n"; // item.get_group().get_local_id() //item.get_local_linear_id()
                out << "  Local ID in Current sub group : "  << item.get_sub_group().get_local_id()  << "\n\n";
                        
                out << " Group info: " << item.get_group() << "\n";
                out << "  ID of Current Work group : "        <<  item.get_group_linear_id()<< "\n";               //item.get_group().get_group_id()
                out << "  Total Number of threads present : " << item.get_global_range() << "\n";                  // item.get_group().get_global_range()
                out << "  Number of threads present in current work group : " << item.get_local_range() << "\n";   // item.get_group().get_local_range()
                out << "  Number of work groups present : "   << item.get_group_range() << "\n\n";                 //item.get_group().get_group_range()
                
                out << "  ID of Current sub_group : "                            << item.get_sub_group().get_group_id() <<"\n";
                out << "  Number of threads present in current sub group : "     << item.get_sub_group().get_local_range() << "\n";
                out << "  Number of sub groups present in current work group : " << item.get_sub_group().get_group_range() << "\n";

                
                out << "\n====================================\n";
               

            }
                    
        });
    }).wait();
    
    return 0;
}
