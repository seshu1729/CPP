#include <CL/sycl.hpp>
#include <iostream>

using namespace cl::sycl;
using namespace std;

constexpr int N = 3;

int main() {
    queue q;

    int a1[N] = {1, 2, 3};
    int a2[N][N] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    int a3[N][N][N] = {
        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
        {{10, 11, 12}, {13, 14, 15}, {16, 17, 18}},
        {{19, 20, 21}, {22, 23, 24}, {25, 26, 27}}
    };

    cout << "1st case with 1D array:\n";
    q.submit([&](handler& h) {
        auto out = stream(512, 256, h);
        h.parallel_for(range<1>(N), [=](id<1> index) {
            int i = index.get(0);
            out << "a1[" << i << "] = " << a1[i] << "\n";
        });
    }).wait();

    cout << "\n2nd case with 2D array:\n";
    q.submit([&](handler& h) {
        auto out = stream(512, 256, h);
        h.parallel_for(range<2>({N, N}), [=](id<2> index) {
            int i = index.get(0);
            int j = index.get(1);
            out << "a2["<< i <<"]["<< j <<"] = "<< a2[i][j] << "\n";
        });
    }).wait();

    cout << "\n3rd case with 3D array:\n";
    q.submit([&](handler& h) {
        auto out = stream(512, 256, h);
        h.parallel_for(range<3>({N, N, N}), [=](id<3> index) {
            int i = index.get(0);
            int j = index.get(1);
            int k = index.get(2);
            out << "a3["<< i <<"]["<< j <<"]["<< k <<"] = "<< a3[i][j][k] << "\n";
        });
    }).wait();

    return 0;
}
