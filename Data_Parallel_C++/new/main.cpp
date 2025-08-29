#include <CL/sycl.hpp>
#include <iostream>
using namespace std;
using namespace cl::sycl;

constexpr int N = 512;

int main()
{
    device gpu;
    gpu = device(gpu_selector());
    std::cout << "GPU Device: " << gpu.get_info<sycl::info::device::name>() << std::endl;
    
    queue myQueue1(gpu_selector_v);
    queue myQueue2(gpu_selector_v);


    //Creating one buffer and two accessors to independently lauch kernels.
    buffer<int, 3> a { range<3> (N, N, N) };
    myQueue1.submit([&](handler& cgh) {
        accessor acc1 { a, cgh, read_write };
        
        // Creating an offset to traverse for a given range
        cgh.parallel_for(range<3> (N/2, N, N), id<3>(0, 0, 0), [=](id<3> index) {
            int i = index[0];
            int j = index[1];
            int k = index[2];
            acc1[i][j][k] = 2;
        });
    });
    
    
    myQueue2.submit([&](handler& cgh) {
        accessor acc2 { a, cgh, read_write };
        
        // Remaining offset traversal
        cgh.parallel_for(range<3> (N/2, N, N), id<3>(N/2, 0, 0), [=](id<3> index){
            int i = index[0];
            int j = index[1];
            int k = index[2];
            acc2[i][j][k] = 4;
        });
    });
    host_accessor acc3 { a, read_only };
    std::cout << std::endl << "Result:" << std::endl;
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                cout<<"a["<<i<<"]["<<j<<"]["<<k<<"] = "<<acc3[i][j][k]<<"  ";
            }
            std::cout<<"\n";
        }
        std::cout << "\n";
    }
    
    std::cout << ".\n.\n.\n.\n";
    
    for (int i = N-2; i < N; i++) {
        for (int j = N-2; j < N; j++) {
            for (int k = N-2; k < N; k++) {
                cout<<"a["<<i<<"]["<<j<<"]["<<k<<"] = "<<acc3[i][j][k]<<"  ";
            }
            std::cout<<"\n";
        }
        std::cout << "\n";
    }    
    
    return 0;
}