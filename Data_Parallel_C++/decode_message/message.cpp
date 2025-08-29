#include <CL/sycl.hpp>
#include <iostream>
using namespace sycl;
using namespace std;

const string secret = "Ifmmp-!xpsme\"\012J(n!tpssz-!Ebwf/!" "J(n!bgsbje!J!dbo(u!ep!uibu/!.!IBM\01" ;
const auto sz = secret.size();

int main() 
{
  queue Q;

  char *result = malloc_shared<char>(sz, Q);
  memcpy(result,secret.data(),sz);

  Q.parallel_for(sz,[=](auto& i) {
      result[i] -= 1;
      }).wait();

  cout << result << "\n";
  return 0;
}