/*
Write a class template that, when instantiated with parameter x, will contain the static value equals to factorial of x. All calculations should be finished at compile time.

Test input: non-negative integers x up to 20.

Your class template will be instantiated this way during tests:

factorial<3>::value
Sample test cases:

static_assert(factorial<3>::value ==  6, "");
static_assert(factorial<4>::value == 24, "");
 and
Assert::That(factorial<3>::value, Equals( 6));
Assert::That(factorial<4>::value, Equals(24));
Factorial of a non-negative integer n (denoted by n!) recursively defined as following (see wiki for more details if necessary)*/
#include <iostream>
using namespace std;
template <int x>
struct factorial 
{ 
  enum fact: unsigned long{ value=x* factorial<x-1>::value };
};
template<>
struct factorial<0>
{
enum fact: unsigned long{ value=1 };
};
