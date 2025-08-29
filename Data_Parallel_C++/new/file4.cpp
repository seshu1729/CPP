#include <CL/sycl.hpp>
#include <iostream>
using namespace std;
using namespace cl::sycl;

constexpr size_t N = 20;
constexpr size_t M = 3000;

int main()
{
    queue myQueue1;
    queue myQueue2;
    queue myQueue3;
    
    
    // Create some 2D buffers of float for our matrices
    
    buffer<int, 3> a { range<3> { N, N, N } };
    
    /*auto e1 = myQueue1.submit([&](handler& cgh){
        accessor acc1 { a, cgh, read_write };
        cgh.parallel_for(range<3>(N,N,N), [=] (id<3> index){
            //auto acc1 = b.get_access<access::mode::read_write>(cgh);
            acc1[index] = 2;
        });
    });*/
    
    
    myQueue2.submit([&](handler& cgh) {
        //cgh.depends_on({e1});
        accessor acc2 { a, cgh, read_write };
        auto out = stream(512,512*2,cgh);
               cgh.parallel_for(range{N/2,N/2,N/2}, [=](id<3> idx){
                   acc2[idx] = 2;
                   out << idx <<"\n";
               });
    });


    
    host_accessor acc2 { a, read_only };
    std::cout << std::endl << "Result:" << std::endl;
    for (size_t i = 0; i < 10; i++) {
        for (size_t j = 0; j < 10; j++) {
            for (size_t k = 0; k < 10; k++) {
                // Compare the result to the analytic value
                std::cout <<acc2[i][j][k] << " on element " << i << " "<< j <<" "<< k <<std::endl;
            }
        }
    }

  std::cout << "Good computation!" << std::endl;
  return 0;
}