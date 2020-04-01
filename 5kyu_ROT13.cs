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
