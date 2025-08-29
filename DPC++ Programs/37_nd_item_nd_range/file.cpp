#include <CL/sycl.hpp>
#include <iostream>

using namespace cl::sycl;
using namespace std;

constexpr int N = 4 ;
constexpr int GR = 4, LR = 4;

int main() 
{
    queue q;
    cout << "Device name: " << q.get_device().get_info<info::device::name>() << "\n";
    
    int a1[N] = {1, 2, 3, 4};
    int a2[N][N] = {{1, 2, 3, 4},
                    {5, 6, 7, 8},
                    {9, 10, 11, 12},
                    {13, 14, 15, 16}
                   };
    
    int a3[N][N][N] = {{{1, 2, 3, 4},
                        {5, 6, 7, 8},
                        {9, 10, 11, 12},
                        {13, 14, 15, 16}
                       },
                       {{17, 18, 19, 20},
                        {21, 22, 23, 24},
                        {25, 26, 27, 28},
                        {29, 30, 31, 32}
                       },
                       {{33, 34, 35, 36},
                        {37, 38, 39, 40},
                        {41, 42, 43, 44},
                        {45, 46, 47, 48}
                       },
                       {{49, 50, 51, 52},
                        {53, 54, 55, 56},
                        {57, 58, 59, 60},
                        {61, 62, 63, 64}
                       }
                      };
    
    cout << "1st case with 1D array:\n";
    
    q.submit([&](handler& h) {
        auto out = stream(512, 256, h);
        h.parallel_for(nd_range<1>(GR, LR), [=](nd_item<1> item) {
            int i = item.get_global_id(0);
            out << "Global ID: " << i << "\n";
            
            out << "a1[" << item << "] = " << a1[i] << "\n";
            
            int glid = item.get_global_linear_id();
            out << "Global Linear ID: " << glid << "\n";
            
            int lid = item.get_local_id(0);
            out << "Local ID: " << lid << "\n";
            
            int llid = item.get_local_linear_id();
            out << "Local Linear ID: " << llid << "\n";
            
            int group_id = item.get_group(0);
            out << "Group ID: " << group_id << "\n";
            out << "\n\n";
            
            /* // modifying below code will result in undefined behavior
            //out << "\n****\n"; // try uncommenting and verify the results
            //auto group_linear_id = item.get_group_linear_id();
            //out << "Group Linear ID: " << group_linear_id << "\n"; // Double check while printing
                
            //auto group_range = item.get_group_range();
            //out << "Group Range: " << group_range[0] << "\n";
                
            //auto local_range = item.get_local_range();
            //out << "Local Range: " << local_range[0] << "\n";
                
            //auto ndr = item.get_nd_range();
            //out << "ND Range Global: " << ndr.get_global_range()[0] << "\n";
            //out << "ND Range Local: " << ndr.get_local_range()[0] << "\n";
                
            //int sub_group_id = item.get_sub_group().get_id(0);
            //out << "Sub-Group ID: " << sub_group_id << "\n";
                
            //id<1> offset = item.get_offset();
            //out << "Offset: " << offset[0] << "\n";
            */
        });
    }).wait();
    
    
    cout << "\n2nd case with 2D array:\n";
    q.submit([&](handler& h) {
        auto out = stream(512, 256, h);
        h.parallel_for(nd_range<2>({N, N}, {1, 1}), [=](nd_item<2> item) {
            int i = item.get_global_id(0);
            int j = item.get_global_id(1);
            out << "a2["<< i <<"]["<< j <<"] = "<< a2[i][j] << "\n";
        });
    }).wait();
    
    cout << "\n3rd case with 3D array:\n";
    q.submit([&](handler& h) {
        auto out = stream(512, 512, h);
        h.parallel_for(nd_range<3>({N, N, N}, {1, 1, 1}), [=](nd_item<3> item) {
            int i = item.get_global_id(0);
            int j = item.get_global_id(1);
            int k = item.get_global_id(2);
            out << "a3["<< i <<"]["<< j <<"]["<< k <<"] = "<< a3[i][j][k] << "\n";
        });
    }).wait();

    return 0;
}
