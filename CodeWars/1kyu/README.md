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
