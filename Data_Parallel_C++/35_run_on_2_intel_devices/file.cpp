#include <CL/sycl.hpp>
#include <vector>
#include <iostream>
#include <string>
#include <sycl/ext/intel/fpga_extensions.hpp> 

using namespace cl::sycl;
using namespace std;
static const int N = 4;

class my_selector1 : public device_selector
{
public:
int operator()(const device &dev) const
{
int score = 50;
//if ( (dev.is_gpu()) && (dev.get_info<info::device::name>().find("GPU1")!= std::string::npos) )//Replace GPU1 with your available INTEL GPU
if ( (dev.is_cpu()) && (dev.get_info<info::device::name>().find("Intel")!= std::string::npos) )
{
score += 25;
cout << "my_selector1 = "<< dev.get_info<info::device::name>()<<"\n" ;
}
return score;
}

};

class my_selector2 : public device_selector
{

public:
int operator()(const device &dev) const
{
int score = -1;
if ( (dev.is_accelerator()) && (dev.get_info<info::device::name>().find("Intel")!= std::string::npos) )//Replace GPU2 with your available INTEL GPU
//if ( (dev.is_accelerator()) && (dev.get_info<info::device::name>().find("Intel")!= std::string::npos) )
{
score += 800;
cout << "my_selector2 = "<< dev.get_info<info::device::name>()<<"\n" ;
}
return score;
}

};

int main()
{
    auto Q1 = queue{ my_selector1{} };
    int *a1 = malloc_shared<int>(N, Q1);
    for(int i=0; i<N; i++) a1[i] = i;
    cout << "Selected device 1: " <<Q1.get_device().get_info<info::device::name>() << "\n\n";
    
    Q1.single_task([=](){
        for(int i=0;i<N;i++) a1[i] *= 2;
    }).wait();
    
    auto Q2 = queue{ my_selector2{} };
    int *a2 = malloc_shared<int>(N, Q2);
    for(int i=0; i<N; i++) a2[i] = i;
    cout << "Selected device 2: " <<Q2.get_device().get_info<info::device::name>() << "\n\n";
    
    Q2.single_task([=](){
        for(int i=0;i<N;i++) a2[i] *= 3;
    }).wait();
    
    for(int i=0; i<N; i++) cout << a1[i] << " ";
    cout<<"\n ";
    
    for(int i=0; i<N; i++) cout << a2[i] << " ";
    cout<<"\n ";
    
    free(a1, Q1);
    free(a2, Q2);
    
    return 0;
}
