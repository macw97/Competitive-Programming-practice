/* 
A pangram is a sentence that contains every single letter of the alphabet at least once. For example, the sentence "The quick brown fox jumps over the lazy dog" is a pangram, because it uses the letters A-Z at least once (case is irrelevant).

Given a string, detect whether or not it is a pangram. Return True if it is, False if not. Ignore numbers and punctuation.
*/

using System;
using System.Collections.Generic;
public static class Kata
{
  public static bool IsPangram(string str)
  {
     Dictionary<char, int> alfa = new Dictionary<char, int>();
            for (char c = 'a'; c <= 'z'; c++)
            {
                  alfa.Add(c,0);
            }
            string temporar = str.ToLower();
            foreach (char v in temporar)
            {
                if(v>=97&&v<=122)
                alfa[v]++;
            }
            foreach (KeyValuePair<char, int> entry in alfa)
            {
                if (entry.Value < 1)
                    return false;
                
            }
            return true;
  }
}
