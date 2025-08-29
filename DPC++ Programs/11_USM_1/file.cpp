#include <CL/sycl.hpp>
#include <iostream>
using namespace cl::sycl;
using namespace std;

int main() 
{
queue q;

int *A = malloc_shared<int>(10, q);
int *B = malloc_shared<int>(10, q);
int *C = malloc_shared<int>(10, q);

for (int i = 0; i < 10; i++) 
{
A[i] = i; 
B[i] = 2*i;
}
    
q.submit([&](handler &h) 
{
h.parallel_for (10,[=](auto i)
{
C[i] = A[i] + B[i];
});
});
q.wait();

for (int i = 0; i < 10; i++)
{
    cout << C[i] <<"\n" ;
}

free(A, q);
free(B, q);
free(C, q);

return 0;
}