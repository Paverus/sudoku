//
//  main.cpp
//  sudoku
//
//  Created by Alden Perrine on 12/29/16.
//  Copyright © 2016 cs31. All rights reserved.
//
//  Main file that is initially run
//  Creates a grid object that contains all neccessary
//  algorithms and data structures
//  See grid documentation for more details

#include "grid.hpp"

int main() {
    grid g;
    g.solve();
    g.print();
    return 0;
}
