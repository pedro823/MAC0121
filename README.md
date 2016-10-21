# MAC0121
Directory for subject MAC0121 - Algortithms and data structures - University of São Paulo.
---
## ep3.c
Program number 3 for this subject. 
The challenge made by the professor was to sort a *circular vector* (meaning that v[n-1] is a neighbor of v[0]), using only one move: the **3-swap.**

The 3-swap pivots 3 numbers and swaps them altogether. One example is the vector 

    [0 1 2 3 4]

One valid 3-swap would be on index 0, transforming it into

    [2 1 0 3 4]
    
The program first checks if such sorting is possible in the given vector, and if so, prints the indexes of the 3-swaps so that the vector is sorted.

---
## ep2.c
Program number 2 for this subject.
The challenge made by the professor was to solve the infamous peg solitaire by using backtrack techniques.

The program receives two inputs, the height and lenght *(m x n)* of the matrix, and then a set of **0**'s (walls), **1**'s (pegs) and **-1**'s (holes).

Be careful, though. The condition to stop the program is _not_ of the regular peg-solitaire (having only one peg remaining on the board), but only when there are pegs in every starting hole, and no more than that.
