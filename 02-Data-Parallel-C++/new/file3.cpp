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
  buffer<int, 3> b { range<3> { N, N, N } };
    
  auto e1 = myQueue1.submit([&](handler& cgh)
                            {
                                accessor acc1 { a, cgh, read_write };
                                
                                cgh.parallel_for(range<3>(N,N,N), [=] (id<3> index){
        //auto acc1 = b.get_access<access::mode::read_write>(cgh);
      
                                    acc1[index] = 2;
                                    
  });
                            });
  // Launch an asynchronous kernel to initialize a
 /*myQueue2.submit([&](handler& cgh) {
    // The kernel writes a, so get a write accessor on it
    accessor A { a, cgh, read_write };
     accessor B { b, cgh, read_write };
    cgh.depends_on({e1});
    // Enqueue a parallel kernel iterating on a N*M 2D iteration space
    cgh.parallel_for(range<2> { N, M },
                     [=](id<2> index) { A[index] = B[index] + 1; });
  });*/


  // Ask for an accessor to read c from application scope.  The SYCL runtime
  // waits for c to be ready before returning from the constructor
  host_accessor A { a, read_only };
  std::cout << std::endl << "Result:" << std::endl;
  for (size_t i = 0; i < 10; i++) {
    for (size_t j = 0; j < 10; j++) {
        for (size_t k = 0; k < 10; k++) {
      // Compare the result to the analytic value
        std::cout <<A[i][j][k] << " on element " << i << " "
                  << j << k <<std::endl;
        }
    }
  }

  std::cout << "Good computation!" << std::endl;
  return 0;
}