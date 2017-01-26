/** The implementation for grid in sudoku
 @file grid.cpp
 @author Alden Perrine

 Created by Alden Perrine on 1/5/17.
 Copyright © 2017 cs31. All rights reserved.
 */

#include "grid.hpp"
#include "location.hpp"
#include "numSet.hpp"
#include <vector>
#include <iostream>

/** Constructor for the grid class
 @post Each location is assigned pointers corresponding
       to its sets, and each set is assigned pointers
       corresponding to its locations, and setInitial is
       called to set the sudoku
 */
grid::grid()
{
    filled = 0;
    for(int w = 0; w < 3; ++w)
    {
        for(int x = 0; x < 3; ++x)
        {
            for(int y = 0; y < 3; ++y)
            {
                for(int z = 0; z < 3; ++z)
                {
                    sudoku[w][x][y][z].setLoc((cols+x*3+z), (rows+w*3+y), (sqrs+w*3+x));
                    cols[x*3+z].addLoc(&sudoku[w][x][y][z]);
                    rows[w*3+y].addLoc(&sudoku[w][x][y][z]);
                    sqrs[w*3+x].addLoc(&sudoku[w][x][y][z]);
                }
            }
        }
    }
    setInitial();
}

/** Places the initial numbers in the sudoku and
    has each location find what possibilities it could be
 @post askUser is called to place the numbers in locations
       and each location has a list of posibilities
 */
void grid::setInitial()
{
    askUser();
    
    for(int w = 0; w < 3; ++w)
    {
        for(int x = 0; x < 3; ++x)
        {
            for(int y = 0; y < 3; ++y)
            {
                for(int z = 0; z < 3; ++z)
                {
                    sudoku[w][x][y][z].findPosib();
                }
            }
        }
    }
}

/** Calls methodds to solve the sudoku
 @post If the program is unable to complete the sudoku
       soley by filling in locations with only one 
       possibility, recursion is called on guessing numbers
 */
void grid::solve()
{
    if(!solveAllOnes())
        guess();
}

/** Solves every single location with only one possibility
 @return True if the sudoku is completely solved, false otherwise
 @post Every location that has only one posibility is
       filled in, including those that have only one
       after a location is filled in
 */
bool grid::solveAllOnes()
{
    while (solveOnes()) {
        continue;
    }
    return (filled==81);
}

/** Prints the sudoku
 @post The sudoku is printed to the output window with
    any unfound number being 0
 */
void grid::print()
{
    for(int w = 0; w < 3; ++w)
    {
        for(int y = 0; y < 3; ++y)
        {
            for(int x = 0; x < 3; ++x)
            {
                for(int z = 0; z < 3; ++z)
                {
                    std::cout << sudoku[w][x][y][z].getNum() << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

/** Find the location with the smallest 
    number of posibilities
 @return A pointer to the location with
         the smallest number of posibilities
 */
location* grid::smallestList()
{
    location* smallest = nullptr;
    int small = 10;
    for(int w = 0; w < 3; ++w)
        for(int x = 0; x < 3; ++x)
            for(int y = 0; y < 3; ++y)
                for(int z = 0; z < 3; ++z)
                    if(!(sudoku[w][x][y][z].hasNum())&&sudoku[w][x][y][z].numPosib()<small)
                    {
                        smallest=&sudoku[w][x][y][z];
                        small = sudoku[w][x][y][z].numPosib();
                    }
    return smallest;
}

/** Guesses a number in a location on the grid
 @return True a solution is found, false otherwise
 @post Begins a recursive depth based backtracking algorithm
       that will eventually find the solution to the sudoku.
       The method begins by choosing the location with the lowest
       amount of possible numbers and iterates through all the 
       possibilities for that location. If a solution is found,
       the program breaks out of the loop and returns true. Otherwise
       if no number is valid, possibly because the function was called
       after another guess and guesOne and there was an error earlier on.
       The function does not call itself, instead calls guessOne, which
       in turn can call guess.
 */
bool grid::guess()
{
    if(filled == 81)
        return true;
    location* locPos = smallestList();
    std::vector<int> posib = locPos->getList();
    bool worked = false;
    for(int i = 0; i < posib.size(); ++i)
    {
        locPos->setNum(posib[i]);
        ++filled;
        if(guessOne())
        {
            worked = true;
            break;
        }
        locPos->undoSetPosib(posib);
        --filled;
    }
    return worked;
}

/** Sees if there is an error in the sudoku solution
 @return True if there is an error, false otherwise
 */
bool grid::isError()
{
    for(int w = 0; w < 3; ++w)
    {
        for(int x = 0; x < 3; ++x)
        {
            for(int y = 0; y < 3; ++y)
            {
                for(int z = 0; z < 3; ++z)
                {
                    if(sudoku[w][x][y][z].getNum()==0&&sudoku[w][x][y][z].numPosib()==0)
                        return true;
                }
            }
        }
    }
    return false;
}

/** Sets every location with only one possibility to that number
 @return True if at least one location was set, false if none were set
 */
bool grid::solveOnes()
{
    bool did = false;
    for(int w = 0; w < 3; ++w)
    {
        for(int x = 0; x < 3; ++x)
        {
            for(int y = 0; y < 3; ++y)
            {
                for(int z = 0; z < 3; ++z)
                {
                    if(sudoku[w][x][y][z].setOnlyValue())
                    {
                        did = true;
                        ++filled;
                    }
                }
            }
        }
    }
    return did;
}

/** Finds a location with only one possibility and fills it in
 @return True if the sudoku is completed, false if there is an error
 @post After a location is found and filled in, the vector for the 
       location is held on incase of failure and guessOne is called
       again. If guessOne cannot fill anything in, it first checks
       if the sudoku is solved, and if so returns true. Next it checks
       for whether there is an error in the sudoku and returns false
       if so. Finally if neither of these conditions are true the 
       function calls guess to fill in another number.
 */
bool grid::guessOne()
{
    if(filled == 81)
        return true;
    bool breakout = false;
    for(int w = 0; w < 3; ++w)
    {
        for(int x = 0; x < 3; ++x)
        {
            for(int y = 0; y < 3; ++y)
            {
                for(int z = 0; z < 3; ++z)
                {
                    if(sudoku[w][x][y][z].numPosib()==1&&sudoku[w][x][y][z].hasNum()==false)
                    {
                        breakout = true;
                        std::vector<int> hold = sudoku[w][x][y][z].getList();
                        sudoku[w][x][y][z].setOnlyValue();
                        ++filled;
                        if(!guessOne())
                        {
                            sudoku[w][x][y][z].undoSetPosib(hold);
                            --filled;
                            return false;
                        }
                    }
                    if(breakout)
                        break;
                }
                if(breakout)
                    break;
            }
            if(breakout)
                break;
        }
        if(breakout)
            break;
    }
    if(filled==81)
        return true;
    if(isError())
        return false;
    return guess();
}

/** Initializes one location on the board
 @param num The number (1-9) to be placed on the board
 @param row The row number (1-9) of the location on the board
 @param col The column number (1-9) of the location on the board
 @post The specified location on the board is filled with the
       number passed in and the filled counter is increased
 */
void grid::initOne(int num, int row, int col)
{
    --row;
    --col;
    sudoku[row/3][col/3][row%3][col%3].setNum(num);
    ++filled;
}

/** Asks the user to input a sudoku and initializes it
 @post Through the i/o window the user can choose
       to use a prewritten sudoku or input their own
 */
void grid::askUser()
{
    char resp;
    std::cout << "Input sudoku (y/n) :: ";
    std:: cin >> resp;
    if(resp!='y')
    {
        initOne(1, 1, 1);
        initOne(8, 2, 2);
        initOne(9, 3, 3);
        initOne(9, 1, 4);
        initOne(7, 1, 6);
        initOne(3, 1, 9);
        initOne(7, 2, 8);
        initOne(6, 3, 7);
        initOne(7, 4, 3);
        initOne(4, 5, 1);
        initOne(1, 5, 2);
        initOne(8, 6, 3);
        initOne(2, 4, 4);
        initOne(9, 4, 6);
        initOne(5, 6, 4);
        initOne(4, 6, 6);
        initOne(4, 4, 7);
        initOne(9, 5, 8);
        initOne(5, 5, 9);
        initOne(3, 6, 7);
        initOne(3, 7, 3);
        initOne(5, 8, 2);
        initOne(2, 9, 1);
        initOne(8, 9, 4);
        initOne(6, 9, 6);
        initOne(7, 7, 7);
        initOne(4, 8, 8);
        initOne(9, 9, 9);
        std::cout << "Prewritten sudoku chosen, here is what it looks like ::" << std::endl << std::endl;
        print();
        std::cout << std::endl<< "Here is the solution :: " << std::endl << std::endl;
        return;
    }
    std::cout << "You have chosen to input your own sudoku" << std::endl;
    while(resp=='y')
    {
        int n, r, c;
        std::cout << "Input a number (1-9) :: ";
        std::cin >> n;
        std::cout << "Input a row (1-9) :: ";
        std::cin >> r;
        std::cout << "Input a column (1-9) :: ";
        std::cin >> c;
        initOne(n, r, c);
        std::cout << "Add another (y/n) :: ";
        std::cin >> resp;
    }
    std::cout << "Here is what the sudoku you entered looks like ::" << std::endl << std::endl;
    print();
    std::cout << std::endl<< "Here is the solution :: " << std::endl << std::endl;
}