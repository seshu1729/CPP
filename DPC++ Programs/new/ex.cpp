#include <CL/sycl.hpp>
#include <iostream>
using namespace std;
using namespace cl::sycl;

constexpr size_t N = 4;

int main()
{
    queue myQueue1;
    queue myQueue2;
    buffer<int, 3> a { range<3> (N, N, N) };
    myQueue1.submit([&](handler& cgh) {
        accessor acc { a, cgh, read_write };
        //cgh.parallel_for(range<3> (N/2, N, N), [=](id<3> index){
        cgh.parallel_for(range<3> (N/2, N, N),id<3>(0, 0, 0), [=](id<3> index){    
            int i=index[0];
            int j=index[1];
            int k=index[2];
            
            acc[i][j][k] = 2;
        });
    });
    myQueue2.submit([&](handler& cgh) {
        accessor acc2 { a, cgh, read_write };
        cgh.parallel_for(range<3> (N/2, N, N),id<3>(N/2, 0, 0), [=](id<3> index){
            int i=index[0];
            int j=index[1];
            int k=index[2];
            
            acc2[i][j][k] = 4;
        });
    });
    

    host_accessor acc3 { a, read_only };
    std::cout << std::endl << "Result:" << std::endl;
    
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                std::cout << acc3[i][j][k] << " on element " << i << " "<< j <<" "<< k << "\n";
            }
        }
    }

    return 0;
}