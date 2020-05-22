/*
https://www.codewars.com/kata/55b7bb74a0256d4467000070
*/
#include <iostream>
using namespace std;
unsigned long long properFractions(unsigned long long n)
{
  if(n<2)
  return 0;
  unsigned long long totient = n;
  for (long long i = 2; i * i <= n; i++)
  {
    if (n % i == 0)
    {
      
      totient *= (i - 1) / (double long)i;
      while (n % i == 0)
        n /= i;
    }
  }
  if (n > 1)
  {
    totient *= (n - 1) / (double long)n;
  }
  return totient;
}
