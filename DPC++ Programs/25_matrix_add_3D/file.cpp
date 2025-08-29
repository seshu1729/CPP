#include<CL/sycl.hpp>
#include<stdio.h>
#include<iostream>
#define N 2

using namespace sycl;
using namespace std;

int main()
{
    //int ha[N][N][N][N] = {{{{1,2},{1,2}},{{1,2},{1,2}}},{{{1,2},{1,2}},{{1,2},{1,2}}}};
    //int hb[N][N][N][N] = {{{{1,2},{1,2}},{{1,2},{1,2}}},{{{1,2},{1,2}},{{1,2},{1,2}}}};
    //int hc[N][N][N][N];
    
    int ha[N][N][N] = {{{1,2},{1,2}},{{1,2},{1,2}}};
    int hb[N][N][N] = {{{1,2},{1,2}},{{1,2},{1,2}}};
    int hc[N][N][N];
    //printing ha and{1,2} hb{1,2}a{1,2}rays here
    
    queue q;
    auto my_buf1 = buffer<int, 3>(**ha, range(N,N,N));
    auto my_buf2 = buffer<int, 3>(**hb, range(N,N,N));
    auto my_buf3 = buffer<int, 3>(**hc, range(N,N,N));
    
    q.submit([&](handler &h) {
        
        accessor dev_acs1(my_buf1,h,read_only);
        accessor dev_acs2(my_buf2,h,read_only);
        accessor dev_acs3(my_buf3,h,write_only);
        auto out = stream(1024, 1024 * 2, h);
        
        h.parallel_for(nd_range<3>(range<3>(2,2,2), range<3>(1,1,1)),[=] (nd_item<3> item){
            int i = item.get_global_id(0); 
            int j = item.get_global_id(1);
            int k = item.get_global_id(2);
            
            dev_acs3[i][j][k]=dev_acs1[i][j][k]+dev_acs2[i][j][k];
            out<< item <<"\n";
            out<< dev_acs3[i][j][k] <<"\n";
        
        });
    });
    
    host_accessor host_hc(my_buf3, read_only);
    
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            for(int k=0;k<N;k++)
                cout<<host_hc[i][j][k]<<"\n" ;
    
    return 0;
}
