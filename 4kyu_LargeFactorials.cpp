/*
In mathematics, the factorial of integer n is written as n!. It is equal to the product of n and every integer preceding it. 
For example: 5! = 1 x 2 x 3 x 4 x 5 = 120
Your mission is simple: write a function that takes an integer n and returns the value of n!.
You are guaranteed an integer argument. For any values outside the non-negative range, return null, nil or None (return an empty string "" in C and C++).
For non-negative numbers a full length number is expected for example, return 25! = "15511210043330985984000000" as a string.

*/
#include <iostream>
#include <string>
using namespace std;
#define MAX 500
int multiply(int x,int res[],int res_size)
{
   int storage=0;
   for(int i=0;i<res_size;i++)
   {
    int product=res[i]*x+storage;
    res[i]=product%10;
    storage=product/10;
    }
    while(storage!=0)
    {
      res[res_size] = storage%10; 
        storage = storage/10; 
        res_size++; 
        }
        return res_size;
}
string factorial(int factorial)
{

 int res[MAX]; 
  string answer="";
      res[0] = 1; 
    int res_size = 1; 
  
  for (int i=2; i<=factorial; i++) 
        res_size = multiply(i, res, res_size); 
        
        for(int i=res_size-1;i>=0;i--)
        {
          int number=res[i];
          answer+=to_string(number);
        }
        return answer;
}
