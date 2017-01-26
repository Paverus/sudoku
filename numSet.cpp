/** The numSet implementation for sudoku
 @file numSet.cpp
 @author Alden Perrine
 
 Created by Alden Perrine on 1/5/17.
 Copyright © 2017 cs31. All rights reserved.
 */

#include "numSet.hpp"
#include "location.hpp"

/** Constructor for the numSet class
 @post Adds all 9 numbers to the complement of 
       the set and sets the addNext pointer to
       the beginning of the array of location pointers
 */
numSet::numSet()
{
    for(int i = 1; i<= 9; ++i)
        complement.push_back(i);
    addNext = locSet;
}

/** Adds a pointer to the list of corresponding locations
 @param loc A pointer to location to be added to the list
 @return False if list is filled, true if the pointer is added
 @post If room in the list, the pointer is added
 */
bool numSet::addLoc(location* loc)
{
    if(addNext>locSet+8)
    {
        return false;
    }
    *addNext = loc;
    addNext++;
    return true;
}

/** Adds a number to the numSet
 @param n The number to be added to the set
 @return True if the number is added, false otherwise
 @post n is removed from the complement, and every location
       has n removed from its list of possibilities
 */
bool numSet::addNum(int n)
{
    if(n<1||n>9)
        return false;
    for(int i = 0; i < complement.size(); ++i)
    {
        if(complement.at(i)==n)
        {
            complement.erase(complement.begin()+i);
            for(int i = 0; i < 9; ++i)
            {
                locSet[i]->removeNum(n);
            }
            return true;
        }
    }
    return false;
}

/**
 @param n The number to be removed from the set
 @return True if the number is removed, false otherwise
 @post n is added to the complement, and every location
       recalculates its possible numbers
 */
bool numSet::removeNum(int n)
{
    if(n<1||n>9)
        return false;
    for(int i = 0; i < complement.size(); ++i)
        if(complement.at(i)==n)
            return false;
    complement.push_back(n);
    for(int i = 0; i < 9; ++i)
        locSet[i]->findPosib();
    return true;
}

/** Returns a pointer to complement to the numSet
 @return A pointer the the complement held by the set
 */
std::vector<int>* numSet::getComplement()
{
    return &complement;
}