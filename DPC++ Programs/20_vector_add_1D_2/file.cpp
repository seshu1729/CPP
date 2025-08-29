#include <CL/sycl.hpp>
using namespace cl::sycl;
using namespace std;

int main()
{
    const int N = 256;
    vector<int> V1(N, 10);
    cout << "\nInput V1: \n";    
    for (int i = 0; i < N; i++)
    {
        cout << V1[i] << " ";
    }

    vector<int> V2(N, 20);
    cout<<"\nInput V2: \n";    
    for (int i = 0; i < N; i++)
    {
        cout << V2[i] << " ";
    }
    
    buffer v1_buf(V1);
    buffer v2_buf(V2);
    
    queue q;
    q.submit([&](handler &h) {
        accessor v1_acc (v1_buf,h);
        accessor v2_acc (v2_buf,h, read_only);
        h.parallel_for(N, [=](auto i) {
        //h.parallel_for(range<1>(N), [=](id<1> i) {
            v1_acc[i] += v2_acc[i];
        });
    });
    
    host_accessor h_a(v1_buf,read_only); 
    cout<<"\nOutput Values from v1_buf to h_a : \n";
    for (int i = 0; i < N; i++)
    {
        cout<< h_a[i] << " ";
    }
    
    return 0;
}
