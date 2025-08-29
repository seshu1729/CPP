#include<iostream>
#include<CL/sycl.hpp>

using namespace std;
using namespace sycl;

//void add(int *p, int x);
void add(cl::sycl::accessor<int, 1, cl::sycl::access::mode::write> p, int x);

int main()
{
    int a[10],b[10],c[10];
    for(int i=0;i<10;i++)
    {
        a[i]=i+1;
        b[i]=2;
    }
    cpu_selector device_selector;
    queue q(device_selector);
    {
        buffer<int ,1> a_buff(a,range<1> (10));
       // buffer<int ,1> b_buff(b,range<1> (10));
        //buffer<int,1> c_buff(c,range<1> (10));
        cout<<q.get_device().get_info<info::device::name>().c_str() << "\n";
        q.submit([&](handler &h)
        {
            cl::sycl::stream kernelout(512*1024, 512, h);
            auto aa=a_buff.get_access<access::mode::write>(h);
           // auto bb=b_buff.get_access<access::mode::write>(h);
            //auto cc=c_buff.get_access<access::mode::write>(h);
            h.parallel_for(range<1>{10},[=](id<1> item)
            {
                add(aa,3);
                 //add((int *)&aa[0],3);
            });
      });
    }
    for(int i=0;i<10;i++)
    {
        cout<<a[i]<<"\t";
    }
}

void add(cl::sycl::accessor<int, 1, cl::sycl::access::mode::write> p, int x){
        p[x]=10;
}

/*extern SYCL_EXTERNAL void Add();

class Add 
{
    public:
    Add(accessor<int> acc) : data_acc(acc) {}
    
    void operator()(id<1> i) {
        data_acc[i] = data_acc[i] + 1;
    }
    
    private:
    accessor<int> data_acc;
};

int main() 
{
    constexpr size_t size = 16;
    std::array<int, size> data;
    for (int i = 0; i < size; i++)
        data[i] = i;
    
    {
        buffer data_buf{data};
        queue Q{ host_selector{} };
        std::cout << "Running on device: "<< Q.get_device().get_info<info::device::name>() << "\n";
        
        Q.submit([&](handler& h) {
            accessor data_acc {data_buf, h};
            h.parallel_for(size, Add(data_acc));
        });
    }
    return 0;
}*/