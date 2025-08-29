#include <CL/sycl.hpp>
using namespace sycl;

static const int N = 4;

int main(){
  queue q;

  int *d1 = malloc_shared<int>(N, q);
  int *d2 = malloc_shared<int>(N, q);
  int *d3 = malloc_shared<int>(N, q);
  for(int i=0; i<N; i++) { d1[i] = 10; d2[i] = 10; d3[i] = 10; }

  auto e1 = q.parallel_for(range<1>(N), [=] (id<1> i){
    d1[i] += 2;
  });

  auto e2 = q.parallel_for(range<1>(N), [=] (id<1> i){
    d2[i] += 3;
  });
    
  auto e3 = q.parallel_for(range<1>(N), [=] (id<1> i){
    d3[i] += 4;
  });
q.submit([&] (handler &h){
  h.depends_on({e1, e2, e3});
  h.parallel_for<class multi1>(range<1>(N), [=] (id<1> i){
    d1[i] += d2[i];
  });  
      
  h.parallel_for<class multi2>(range<1>(N), [=] (id<1> i){
    d3[i] += 4;
  });  
}).wait();

    
    std::cout<<"d1 = ";

    for(int i=0; i<N; i++) std::cout << d1[i] << std::endl;
        std::cout<<"d2 = ";
    for(int i=0; i<N; i++) std::cout << d2[i] << std::endl;
        std::cout<<"d3 = ";
    for(int i=0; i<N; i++) std::cout << d3[i] << std::endl;
  free(d1, q);
  free(d2, q);
  return 0;
}
