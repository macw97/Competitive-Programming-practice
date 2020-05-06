//https://www.codewars.com/kata/5a3af5b1ee1aaeabfe000084/cpp

#include <iostream>
#include <math.h>
using namespace std;
bool is_perfect(int number)
{
  if (number == 1)
    return true;
  int root = round(sqrt(number));
  return number == root * root;
}
//Lagrange's Four-square theorem
//if n can be wrriten in form of 4^k*(8*m + 7) result is 4 
int sum_of_squares(int n) {
    if (is_perfect(n))
    return 1;
  int sq = (int)sqrt(n);
  for (int i = 1; i <= sq; i++)
  {
    if (is_perfect(n - i * i))
    {
      return 2;
    }
  }
  
  while (n %4 == 0)
  {
    n/=4;
  }
  if (n%8 == 7)
    return 4;

  
  return 3;
}
