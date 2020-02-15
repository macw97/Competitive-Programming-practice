/*
Write a function validSolution/ValidateSolution/valid_solution() that accepts a 2D array representing a Sudoku board, and returns true if it is a valid solution, or false otherwise. 
The cells of the sudoku board may also contain 0's, which will represent empty cells.
Boards containing one or more zeroes are considered to be invalid solutions.
The board is always 9 cells by 9 cells, and every cell only contains integers from 0 to 9.


*/
#include <iostream>
using namespace std;
bool CheckRows(unsigned int tab[9][9])
  {
  int sum_rows=0,sum_cols=0;
   for(int i=0;i<9;i++)
   {
   sum_rows=0;
   sum_cols=0;
      for(int j=0;j<9;j++)
      {
       sum_rows+=tab[i][j];
       sum_cols+=tab[j][i]; 
      }
      if((sum_rows!=45)||(sum_cols!=45))
      {
      return false;
      
      }
      
   }   
   return true;
   }
   
   bool LookForZero(unsigned int tab[9][9])
{
  for(int i=0;i<9;i++)
  {
      for(int j=0;j<9;j++)
      {
      if(tab[i][j]==0)
        { 
        return true;
         }
      }
  }
  return false;
  }
  bool check_matrix(unsigned int tab[9][9],int k,int m)
  {
  int sums=0;
     for(int i=k;i<k+3;i++)
     {
     
      for(int j=m;j<m+3;j++)
      {  
      sums+=tab[i][j];
      }
      
    }
    if(sums!=45)
    return false;
    
    
    return true;
}
bool validSolution(unsigned int board[9][9]){
 int counter=0;
   if(LookForZero(board)==true)
   { return false; }
   for(int i=0;i<3;i++)
   {
       
          if(check_matrix(board,i*3,0)==true)
          { counter++; }
          if(check_matrix(board,i*3,3)==true)
          { counter++; }
          if(check_matrix(board,i*3,6)==true)
          { counter++; }
   }
   if((counter==9)&&(CheckRows(board)==true))
  {   return true; }

 return false;
}
