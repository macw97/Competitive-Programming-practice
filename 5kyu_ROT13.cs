/*
ROT13 is a simple letter substitution cipher that replaces a letter with the letter 13 letters after it in the alphabet.
ROT13 is an example of the Caesar cipher.
Create a function that takes a string and returns the string ciphered with Rot13. 
If there are numbers or special characters included in the string, they should be returned as they are. 
Only letters from the latin/english alphabet should be shifted, like in the original Rot13 "implementation".
*/
using System;
using System.Linq;
public class Kata
{
  public static string Rot13(string message)
  {
    char[] rot=message.ToCharArray();
    for(int i=0;i<rot.Length;i++)
      {
         if(rot[i]>='a' && rot[i]<='z')
         {
           rot[i]=(char)((rot[i]-'a'+13)%26+'a');
         }
         if(rot[i]>='A' && rot[i]<='Z')
         {
           rot[i]=(char)((rot[i]-'A'+13)%26+'A');
         }
     }
   return new string(rot);
  }
}
