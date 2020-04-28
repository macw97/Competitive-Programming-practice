/*https://www.codewars.com/kata/5dcde0b9fcb0d100349cb5c0*/
#include<iostream>
#include<string>

using namespace std;

string ManachersStringTransform(string s)
{
  string result ="$";
  for (char& c : s)
  {
    result += "#";
    result += c;
  }
  result += "#";
  return result;
}
string longest_palindrome(string input)
{
  if (input.length() == 0)
    return "";

  string result = ManachersStringTransform(input);
  int* P = new int[result.length()];
  for (int i = 0; i < result.length(); i++)
    P[i] = 0;

  int Center = 0, RightBound = 0;
  for (int i = 1; i < result.length() - 1; i++)
  {
    int mirror = 2 * Center - i;
    if (i < RightBound)
      P[i] = (RightBound - i) > P[mirror] ? P[mirror] : (RightBound - i);

    while (result[i + (1 + P[i])] == result[i - (1 + P[i])])
      P[i]++;

    if ((P[i] + i) > RightBound) {
      Center = i;
      RightBound = i + P[i];
    }
  }
  int maxLong = 0,center= 0;
  for (int i = 1; i < result.length() - 1; i++)
  {
    if (P[i] > maxLong) {
      maxLong = P[i];
      center = i;
    }
  }
  return input.substr((center - 1 - maxLong) / 2, maxLong);
}
