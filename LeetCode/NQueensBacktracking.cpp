/*
Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space respectively.
*/
class Solution {
public:
    vector<vector<string>> result;
    vector<vector<int>> board;
    bool safeRows(int row,int n)
    {
        for(int i=0;i<n;i++)
        {
            if(board[row][i]==1)
                return false;
        }
        return true;
    }
    bool up_diagonals(int row,int col,int n)
    {
        int i,j;
       for(i=row,j=col; i>=0 && j>=0;i--,j--)
       {
           if(board[i][j]==1)
               return false;
       }
        return true;
    }
    bool down_diagonals(int row,int col, int n)
    {
        int i,j;
        for(i=row,j=col;i<n && j>=0;i++,j--)
        {
            if(board[i][j]==1)
                return false;
        }
        return true;
    }
    vector<string> convert(vector<vector<int>> board,int n)
    {
        vector<string> result1;
        for(int i=0;i<n;i++)
        {
            string result0="";
            for(int j=0;j<n;j++)
            {
                if(board[i][j]==1)
                    result0+='Q';
                else
                    result0+='.';
            }
            result1.push_back(result0);
        }
        return result1;
    }
    void solvable(int col,int n)
    {
        if(col==n)
        {
            result.push_back(convert(board,n));
        }
        for(int row=0;row<n;row++)
        {
            if(safeRows(row,n) && up_diagonals(row,col,n) && down_diagonals(row,col,n))
            {
                
                board[row][col]=1;
                solvable(col+1,n);
                
                board[row][col]=0;
                
            }
        }
    }
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<int>> b(n,vector<int>(n,0));
        board=b;
        solvable(0,n);
            
        return result;
    }
};
