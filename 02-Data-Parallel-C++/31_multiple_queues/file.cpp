#include <CL/sycl.hpp>

constexpr int num = 16;
using namespace cl::sycl;
using namespace std;

int main()
{
    auto R = num;
    //auto R = range<1>{ num };
    
    //Create Buffers A and B
    buffer<int> a_buf{ R }, b_buf{ R };
    
    
    queue Q;
    Q.submit([&](handler& h) {
        auto out = stream(1024, 512, h);
        cout<<"\n 1st Queue for accessing  a\n";
        accessor acc(a_buf,h,write_only);
        h.parallel_for(R, [=](auto idx) {
        //h.parallel_for(R, [=](id<1> idx) {
            acc[idx] = idx[0]; 
        }); 
    });
    
    Q.submit([&](handler& h) {
        auto out = stream(1024, 512, h);
        cout<<"\n 2nd Queue for accessing and modifying a\n";
        cout<<"\n This task will wait till the first queue is complete\n";
        accessor acc(a_buf,h,write_only);
        h.parallel_for(R, [=](auto idx) {
        //h.parallel_for(R, [=](id<1> idx) {
            acc[idx] += idx[0];
        });
    });
    
    Q.submit([&](handler& h) { 
        auto out = stream(1024, 512, h);
        cout<<"\n 3rd Queue for accessing b\n";
        accessor acc(b_buf,h,write_only);
        h.parallel_for(R, [=](auto idx) {
        //h.parallel_for(R, [=](id<1> idx) {
            acc[idx] = idx[0]; 
        }); 
    });
    
    Q.submit([&](handler& h) {
        auto out = stream(1024, 512, h);
        cout<<"\n 4th Queue for accessing b\n";
        cout<<"\n This task will wait till kernel 2 and 3 are complete\n";
        accessor in (a_buf,h,read_only);
        accessor inout(b_buf,h);
        h.parallel_for(R, [=](auto idx) {
        //h.parallel_for(R, [=](id<1> idx) {
            inout[idx] *= in[idx];
            //out<<"inout["<<idx<<"] = "<<inout[idx]<<"\n" ;
            out<<"inout["<<idx[0]<<"] = "<<inout[idx]<<"\n" ;
            //sometimes the result array from host will be displayed first before the inout array
        });
    }); 
    
    host_accessor result(b_buf,read_only);
    cout <<"\n\nCopying from b_buf to result \n\n";
    for (int i=0; i<num; ++i)
    {
        cout <<"result["<<i<<"] = "<< result[i] << "\n";
    }
    
    return 0;
}