//
//  grid.hpp
//  sudoku
//
//  Created by Alden Perrine on 1/5/17.
//  Copyright © 2017 cs31. All rights reserved.
//
//  The grid contains both the sudoku and all methods
//  necessary to solve it
//  A 3x3x3x3 grid of locations is kept to represent
//  the sudoku, with the first 2 values giving the
//  square where the location is and the last 2 giving
//  the location within the square
//  3 arrays of numSets of length 9 are kept to represent
//  the 9 rows, columns and squares
//  The grid attempts to solve the sudoku using the union
//  of the complements of all of the row-column-square
//  combinations and then resorts to a depth based backtracking
//  algorithm to find the solution to the sudoku
//  More details in the implementation file

#ifndef grid_hpp
#define grid_hpp

#include "location.hpp"
#include "numSet.hpp"

class grid
{
public:
    grid();
    void solve();
    void print();
private:
    void setInitial();
    bool solveAllOnes();
    bool guess();
    location* smallestList();
    bool isError();
    bool solveOnes();
    bool guessOne();
    void initOne(int num, int row, int col);
    void askUser();
    
    location sudoku[3][3][3][3];
    numSet cols[9];
    numSet rows[9];
    numSet sqrs[9];
    int filled;
};


#endif /* grid_hpp */
