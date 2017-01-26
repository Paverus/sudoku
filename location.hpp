//
//  location.hpp
//  sudoku
//
//  Created by Alden Perrine on 1/5/17.
//  Copyright © 2017 cs31. All rights reserved.
//
//  Definition of location class
//  Each location keeps track of which row, column and sqaure
//  it is in, what its value is and what possible values it can have
//  The location is allowed to check what values are in each set
//  it is a part of, calculate what possible numbers itself could be,
//  and set its own value
//  For the details of each method, see location implementaion

#ifndef location_hpp
#define location_hpp

#include <vector>

class numSet;

class location
{
public:
    location();
    void setLoc(numSet* c, numSet* r, numSet* s);
    int getNum() const;
    bool hasNum() const;
    void setNum(int n);
    void findPosib();
    std::vector<int> getList();
    void removeNum(int num);
    int numPosib() const;
    bool setOnlyValue();
    bool undoSetPosib(std::vector<int> held);
private:
    int num;
    numSet* col;
    numSet* row;
    numSet* sqr;
    std::vector<int> listPosib;
};


#endif /* location_hpp */
