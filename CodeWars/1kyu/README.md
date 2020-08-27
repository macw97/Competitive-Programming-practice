# N queen problem with one queen mandatory position

As parameters, we are given queen position and size of the board. Need to return one of the solutions as a string indicating '.' as empty positions and queens as 'Q' ending
each row with '\n'.

**There are 31 tests provided:**

- ***8 for small board (N<=10)***

- ***8 for boards with no solution***

- ***5 for boards (10<N<=50)***

- ***5 for boards (100<N<=500)***

- ***5 for boards (500<N<=1000)***


The main problem is that we have to go through all tests in less than **12 seconds** with a backtracking algorithm there is no way to reach even second test with size N>10. Breach and bound mixed with backtracking end up at the third test for N>10.
My next idea was a heuristic algorithm with minimum conflicts but I didn't use reset after hitting the local minimum in which algorithm get stucked a lot. Finally, optimization which gave the possibility to go through all of those tests under **7 seconds** was

**Heuristic algorithm with minimum conflicts using branch and bound**.

- first, we initialize 2d board vector, Queens vector in which each index is a column and Queens[index] is a row of Queen in that column and rest of vectors from the branch and bound technic where we keep number of Queens in both diagonals and row to count a number of conflicts in O(1).
- next, we randomize row for each queen to have only one queen in each row and column.
- update branch and bound vectors
- set limit of moves and resets because not always we will get a solution
- randomly pick queen
- count number of conflicts in each row for this queen column and pick a row with the lowest conflicts if there is a few randomly pick one and move queen also updating branch and bound vectors
- if all queens are safe to return true and create a string for that solution
- otherwise, if we hit max moves we reset the whole board and start again
