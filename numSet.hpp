//
//  numSet.hpp
//  sudoku
//
//  Created by Alden Perrine on 1/5/17.
//  Copyright © 2017 cs31. All rights reserved.
//
//  Definition of the numSet class
//  Each numSet keeps a vector of numbers that
//  are not in the set of locations contained in
//  the set, and an array of pointers to the
//  locations of the numSet.
//  Because the possibilities for each square in
//  sudoku is calculated from the union of the
//  complement of the corresponding row, column and
//  square sets, it is simpler for the numSet class
//  to hold the complement of the set instead of
//  holding the set itself
//  As in all calculations the actual set will not
//  be needed, it is never apparent in the interface
//  that the set only knows its complement

#ifndef numSet_hpp
#define numSet_hpp

#include <vector>
class location;

class numSet
{
public:
    numSet();
    bool addLoc(location* loc);
    bool addNum(int n);
    bool removeNum(int n);
    std::vector<int>* getComplement();
private:
    std::vector<int> complement;
    location* locSet[9];
    location** addNext;
};

#endif /* numSet_hpp */
