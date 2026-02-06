#include <CL/sycl.hpp>
#include <iostream>
using namespace std;
using namespace cl::sycl;

constexpr size_t N = 20;
constexpr size_t M = 3000;

int main() {
  // Create a queue to work on
    queue myQueue1;
    queue myQueue2;
  // Create some 2D buffers of float for our matrices
    buffer<int, 3> a { range<3> { N, N, N } };
  //buffer<int, 3> a2 {range<3> {N.begin()+10, N.begin()+10, N.begin()+20}};

    auto e1 = myQueue1.submit([&](handler& cgh) {
        accessor acc1 { a, cgh, read_write };
        cgh.parallel_for(range<3>(N/2,N/2,N/2),
                         [=] (id<3> index)
                         {
                             acc1[index] = 1;
                         });
    });
    
    // Launch an asynchronous kernel to initialize a
    myQueue2.submit([&](handler& cgh) {
    // The kernel writes a, so get a write accessor on it
    accessor acc2 { a, cgh, read_write };
    // Enqueue a parallel kernel iterating on a N*M 2D iteration space
    cgh.parallel_for(range<3> { N/2, N, N },id<3>(6, 6, 6),
                     [=](id<3> index) 
                     { 

                         int i=index[0];
                           int j=index[1];
                           int k=index[2];


                         acc2[i][j][k] = 2; 
                     });
    });

    host_accessor acc2 { a, read_only };
    std::cout << std::endl << "Result:" << std::endl;
    
    for (size_t i = 0; i < 20; i++) {
        for (size_t j = 0; j < 20; j++) {
            for (size_t k = 0; k < 20; k++) {
                std::cout << acc2[i][j][k] << " on element " << i << " "<< j <<" "<< k << "\n";
            }
        }
    }
    std::cout << "{ "<< acc2[0][0][0] << " on element " << 0 << " " << 0 << 0 << "} ";
    std::cout << "{ "<< acc2[12][12][12] << " on element " << 12 << " " << 12 << 12 << "} ";
    std::cout << "Good computation!" << std::endl;
    return 0;
}