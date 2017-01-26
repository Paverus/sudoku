/** The location class implementation for sudoku
 @file location.cpp
 @author Alden Perrine
 
 Created by Alden Perrine on 1/5/17.
 Copyright © 2017. All rights reserved.
 */

#include "location.hpp"
#include "numSet.hpp"
/** Constructor for the location class that initializes values
 @post all pointers are set to nullptr, the number is set to zero
        and the vector of possible numbers has a max capacity of 9
*/
location::location()
:listPosib(9)
{
    num = 0;
    col = nullptr;
    row = nullptr;
    sqr = nullptr;
}

/** Sets the pointers to the sets the location is part of
 @param c A pointer to the corresponding column numSet
 @param r A pointer to the corresponding row numSet
 @param s A pointer to the corresponding square numSet
 */
void location::setLoc(numSet* c, numSet* r, numSet* s)
{
    col = c;
    row = r;
    sqr = s;
}

/** Gets the number held by the location
 @return the number held by the location
 */
int location::getNum() const
{
    return num;
}

/** Gets whether there is a number set at the location
 @return true if there is a number set, otherwise false
 */
bool location::hasNum() const
{
    return (num!=0);
}

/** Sets the value at the location
 @param n number to set the location to
 @post sets the value of the location to n,
 clears the list of posibilities, and adds the
 number to each of the sets that contain the location
 */
void location::setNum(int n)
{
    num = n;
    listPosib.clear();
    col->addNum(n);
    row->addNum(n);
    sqr->addNum(n);
}

/** Finds all possible numbers the location could be
 @post listPosib is filled with all of the possible
 numbers that the location can hold as determined by
 the complement of the row, column and sqaure sets
 */
void location::findPosib()
{
    if(num!=0)
        return;
    listPosib.clear();
    std::vector<int>& cSet = *(col->getComplement());
    std::vector<int>& rSet = *(row->getComplement());
    std::vector<int>& sSet = *(sqr->getComplement());
    for(int i = 0; i < cSet.size(); ++i)
    {
        for(int x = 0; x < rSet.size(); ++x)
        {
            if(cSet[i]==rSet[x])
            {
                for(int k = 0; k < sSet.size(); ++k)
                {
                    if(cSet[i]==sSet[k])
                        listPosib.push_back(cSet[i]);
                }
            }
        }
    }
}

/** Gets the list of posibilities for the location
 @return a vector<int> holding
 the list of possible numbers
 */
std::vector<int> location::getList()
{
    return listPosib;
}

/** Removes a number from the list of posibilities
 @param num the number to remove from the list
 @post if num is in the list of possible numbers
 it is removed from the list
 */
void location::removeNum(int num)
{
    if(listPosib.size()==0)
        return;
    for(int i = 0; i < listPosib.size(); ++i)
    {
        if(listPosib.at(i)==num)
        {
            listPosib.erase(listPosib.begin()+i);
            return;
        }
    }
}

/** Gets the number of posibilities the location could be
 @return the number of posibilities the location could be
 */
int location::numPosib() const
{
    return (int) listPosib.size();
}

/** Sets the value at the location to the only possible value
 @post if true, sets the value of the locaiton to the only value,
        adds the number to all of the numSets the location is
        part of, and finally clears the list of posibilities
 @return true if the value was set, false otherwise
 */
bool location::setOnlyValue()
{
    if(listPosib.size()!=1)
        return false;
    num = listPosib.at(0);
    col->addNum(num);
    row->addNum(num);
    sqr->addNum(num);
    listPosib.clear();
    return true;
}

/**
 */
bool location::undoSetPosib(std::vector<int> held)
{
    if(num == 0)
        return false;
    col->removeNum(num);
    row->removeNum(num);
    sqr->removeNum(num);
    num = 0;
    listPosib = held;
    return true;
}
