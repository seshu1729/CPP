#include <CL/sycl.hpp>
#include <iostream>
using namespace std;
using namespace cl::sycl;

static const int N = 4;

int main()
{
  queue q;

  int *d1 = malloc_shared<int>(N, q);
  int *d2 = malloc_shared<int>(N, q);  
  for(int i=0; i<N; i++) { d1[i] = 10; d2[i] = 10; }

  auto e1 = q.parallel_for(range<1>(5), [=] (id<1> i){
    d1[i] += 2;
  });

  auto e2 = q.parallel_for(range<1>(5), [=] (id<1> i){
    d1[i+5] += 3;
  });

  q.submit([&] (handler &h){
    
    h.parallel_for(range<1>(N), [=] (id<1> i){
      d1[i] += 5;
    });  
  }).wait();

  for(int i=0; i<N; i++) cout << d1[i] << "\n";
  free(d1, q);
  free(d2, q);

  return 0;
}
