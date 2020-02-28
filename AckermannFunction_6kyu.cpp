/*
Write a class template that, when instantiated with parameters m and n, will contain the static value equals to Ackermann function value A(m,n). All calculations should be finished at compile time.

Test input: non-negative integers m and n up to 3 (matrix 4x4) and some edge cases (when m or n equals to 4).

Your class template will be instantiated this way during tests:

ackermann<2, 2>::value
Sample test cases:

static_assert(ackermann<2, 2>::value == 7, "");
and
Assert::That(ackermann<2, 2>::value, Equals(7)); */


template <int m, int n>
struct ackermann { enum{ value= ackermann<m-1, ackermann<m,n-1>::value >::value};
};
template<int m>
struct ackermann<m,0>
{
enum{ value=ackermann<m-1,1>::value};
};
template<int n>
struct ackermann<0,n>
{
enum{ value=n+1};
};
template<>
struct ackermann<0,0>
{
enum{value=1};
};
