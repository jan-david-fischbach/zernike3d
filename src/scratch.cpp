#include <iostream>

#include "coefs.hpp"

int main()
{
  const int N = 50;

  // HK_coefs hk(N);
  // for (int m = 0, idx = 0 ; m <= N ; m++)
  //   for (int n = 0 ; n <= m ; n++)
  //     for (int k = 0 ; k <= n ; k++, idx++)
  //       std::cout << m << ", " << n << ", " << k << " = " << 9 * hk.k3_coefs[idx].get_d() / 4 << "\n";

  binomials b(2 * N + 3);
  factorials f(N);
  double_factorials df(N + 1);
  unl3 u(N, b);
  vnl3 v(N, f, df, b);
  compose id(u, v);
  for (int n = 0 ; n <= N ; n++)
    for (int k = 0 ; k <= n ; k++)
      std::cout << n << ", " << k << " = " << id.get(n, k) << "\n"; 

}