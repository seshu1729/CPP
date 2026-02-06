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
    
    int ha[N][N] = {{1,2},{1,2}};
    int hb[N][N] = {{1,2},{1,2}};
    int hc[N][N];
    //printing ha and{1,2} hb{1,2}a{1,2}rays here
        queue q;
        auto my_buf1 = buffer<int, 2>(*ha, range(N,N));
        auto my_buf2 = buffer<int, 2>(*hb, range(N,N));
        auto my_buf3 = buffer<int, 2>(*hc, range(N,N));
        
        q.submit([&](handler &h) {
            stream out(1024,256,h);
            accessor dev_acs1(my_buf1,h,read_only);
            accessor dev_acs2(my_buf2,h,read_only);
            accessor dev_acs3(my_buf3,h,write_only);
            
            h.parallel_for(range{N,N},[=](id<2> idx){
                int j = idx[0]; //index[0] taking values from 0 to M
                for (int i = 0; i < N; i++)
                {
                    dev_acs3[i][j]=dev_acs1[i][j] + dev_acs2[i][j];
                }
            });
        });
    
        host_accessor host_hc(my_buf3);
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                std::cout<<host_hc[i][j]<<"  " ;
            }
            cout<<"\n";
        }
        return 0;
}
