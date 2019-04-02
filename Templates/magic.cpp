#include <bits/stdc++.h>
using namespace std;
int mian()
{
  cout<<"Hello world!"<<endl;
  return 0;
}

// black_magic #1 swap using bit
void inplace_swap(int* x, int* y)
{
  *y = *x ^ *y;
  *x = *x ^ *y;
  *y = *x ^ *y;
}

//black_magic #2 print int_32&64
void scale()
{
  unsigned long long lu = 1e16;
  int it = 1e8;
  printf(" %"PRId32", %"PRIu64" ",it,lu);
}
