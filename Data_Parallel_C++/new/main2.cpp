#include <CL/sycl.hpp>
#include <iostream>
using namespace std;
using namespace cl::sycl;

constexpr size_t N = 1024;

int main()
{

    
    queue myQueue1(gpu_selector_v);
    queue myQueue2(gpu_selector_v);
    
    std::cout << "Queue Device 1: " << myQueue1.get_device().get_info<info::device::name>() << "\n";
    cout << "Queue Device 1 Max workgroup size "<<myQueue1.get_device().get_info<info::device::max_work_group_size>() << "\n";
    
    std::cout << "Queue Device 1: " << myQueue2.get_device().get_info<info::device::name>() << "\n";
    cout << "Queue Device 1 Max workgroup size "<<myQueue2.get_device().get_info<info::device::max_work_group_size>() << "\n";

    
    

    //Creating one buffer and two accessors to independently lauch kernels.
    buffer<int, 3> a { range<3> (N, N, N) };
    myQueue1.submit([&](handler& cgh) {
        accessor acc1 { a, cgh, read_write };
        
        int N2 = (N-1)/2;
        if(N%2==0)
        {
            N2=N/2 ;
        }
        else
        {
            N2=(N-1)/2 ;
        }
        // Creating an offset to traverse for a given range
        cgh.parallel_for(range<3> (N2, N, N), id<3>(0, 0, 0), [=](id<3> index) {
            int i = index[0];
            int j = index[1];
            int k = index[2];
            acc1[i][j][k] = 2;
        });
    }).wait();
    
    
    myQueue2.submit([&](handler& cgh) {
        accessor acc2 { a, cgh, read_write };
        
        int N2 = (N-1)/2;
        if(N%2==0)
        {
            N2=N/2 ;
        }
        else
        {
            N2=(N-1)/2 ;
        }
        
        // Remaining offset traversal
        cgh.parallel_for(range<3> (N2, N, N), id<3>(N2, 0, 0), [=](id<3> index){
            int i = index[0];
            int j = index[1];
            int k = index[2];
            acc2[i][j][k] = 4;
        });
    }).wait();
    host_accessor acc3 { a, read_only };
    std::cout << std::endl << "Result:" << std::endl;
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                cout<<"a["<<i<<"]["<<j<<"]["<<k<<"] = "<<acc3[i][j][k]<<"  ";
            }
            std::cout<<"\n";
        }
        std::cout << "\n";
    }
    
    std::cout << ".\n.\n.\n.\n";
    
    for (int i = N-3; i < N; i++) {
        for (int j = N-3; j < N; j++) {
            for (int k = N-3; k < N; k++) {
                cout<<"a["<<i<<"]["<<j<<"]["<<k<<"] = "<<acc3[i][j][k]<<"  ";
            }
            std::cout<<"\n";
        }
        std::cout << "\n";
    }    
    
    return 0;
}