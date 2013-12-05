/*
 * The MIT License (MIT)
 * Copyright (c) 2013 Daniel Widyanto
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to 
 * deal in the Software without restriction, including without limitation the 
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or 
 * sell copies of the Software, and to permit persons to whom the Software is 
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include "sudokugame.h"

//-----------------------------------------------------------------------------
#define SUDOKU_TYPE_9X9_SUBBOARD_SIZE   3

//-----------------------------------------------------------------------------
SudokuGame::SudokuGame(std::vector<unsigned int> *board) :
    _sudokuBoard(board) 
{
}

bool SudokuGame::isDigitValid(unsigned int digit, int row, int column) {
    // Save the old digit 
    unsigned int oldDigit = (*_sudokuBoard)
        [row * static_cast<int> (SUDOKU_TYPE_9X9) + column];

    // Assign the tile with the new digit
    (*_sudokuBoard)[row * static_cast<int> (SUDOKU_TYPE_9X9) + column] = digit;

    bool retVal = isRowValid     (row, column) && \
                  isColumnValid  (row, column) && \
                  isSubboardValid(row, column);

    // Return the old digit into its place
    (*_sudokuBoard)[row * static_cast<int> (SUDOKU_TYPE_9X9) + column] = 
                                                                      oldDigit;

    return retVal;
}

std::vector<unsigned int> SudokuGame::availableDigit(int row, int column) {
    std::vector<unsigned int> availableDigit;

    for (unsigned int i = 1; i <= 9; i++) {
        if (isDigitValid(i, row, column)) {
            availableDigit.push_back(i);
        }
    }

    return availableDigit;
}

bool SudokuGame::isGameOver() {
    for (std::vector<unsigned int>::iterator it = _sudokuBoard->begin(); 
                                             it < _sudokuBoard->end(); 
                                             it++) 
    {
        if (*it == 0) {
            return false;
        }
    }

    return true;
}

bool SudokuGame::isRowValid(int row, int column) {
    // The available digits
    bool validDigits[] = {
        false, // 0
        true,  // 1
        true,  // 2
        true,  // 3
        true,  // 4
        true,  // 5
        true,  // 6
        true,  // 7
        true,  // 8
        true   // 9
    };

    int colNo;
    for (colNo = 0; colNo < static_cast<int> (SUDOKU_TYPE_9X9); colNo++) {
        unsigned int digit = (*_sudokuBoard)
            [row * static_cast<int> (SUDOKU_TYPE_9X9) + colNo];
        
        if (digit == 0) {
            // The tile is not filled yet. Continue with the next tile
            continue;
        } else 
        if (validDigits[digit] == true) {
            validDigits[digit] = false;
        } else {
            break;
        }
    }
    
    if (colNo == static_cast<int> (SUDOKU_TYPE_9X9)) {
        return true;
    } else {
        return false;
    }
}

bool SudokuGame::isColumnValid(int row, int column) {
    // The available digits
    bool validDigits[] = {
        false, // 0
        true,  // 1
        true,  // 2
        true,  // 3
        true,  // 4
        true,  // 5
        true,  // 6
        true,  // 7
        true,  // 8
        true   // 9
    };

    int rowNo;
    for (rowNo = 0; rowNo < static_cast<int> (SUDOKU_TYPE_9X9); rowNo++) {
        unsigned int digit = (*_sudokuBoard)
            [rowNo * static_cast<int> (SUDOKU_TYPE_9X9) + column];
        
        if (digit == 0) {
            // The tile is not filled yet. Continue with the next tile
            continue;
        } else 
        if (validDigits[digit] == true) {
            validDigits[digit] = false;
        } else {
            break;
        }
    }

    if (rowNo == static_cast<int> (SUDOKU_TYPE_9X9)) {
        return true;
    } else {
        return false;
    }
}

bool SudokuGame::isSubboardValid(int row, int column) {
    // The available digits
    bool validDigits[] = {
        false, // 0
        true,  // 1
        true,  // 2
        true,  // 3
        true,  // 4
        true,  // 5
        true,  // 6
        true,  // 7
        true,  // 8
        true   // 9
    };

    int subboardRow = (row / SUDOKU_TYPE_9X9_SUBBOARD_SIZE);
    subboardRow     = subboardRow  * SUDOKU_TYPE_9X9_SUBBOARD_SIZE;

    int subboardColumn = (column / SUDOKU_TYPE_9X9_SUBBOARD_SIZE);
    subboardColumn     = subboardColumn * SUDOKU_TYPE_9X9_SUBBOARD_SIZE;
    
    int rowCount, colCount;
    bool columnDigitValid = true;

    for (rowCount = 0; rowCount < SUDOKU_TYPE_9X9_SUBBOARD_SIZE; rowCount++) {
        for (colCount = 0; colCount < SUDOKU_TYPE_9X9_SUBBOARD_SIZE; colCount++) {
            unsigned int digit = (*_sudokuBoard)[
                ((subboardRow + rowCount) * static_cast<int>(SUDOKU_TYPE_9X9)) + 
                (subboardColumn + colCount)
            ];

           if (digit == 0) {
                // The tile is not filled yet. Continue with the next tile
                continue;
            } else 
            if (validDigits[digit] == true) {
                validDigits[digit] = false;
            } else {
                columnDigitValid = false;
                break;
            }
        }

        if (columnDigitValid == false) {
            break;
        }
    }

    if ((rowCount == SUDOKU_TYPE_9X9_SUBBOARD_SIZE) && 
        (colCount == SUDOKU_TYPE_9X9_SUBBOARD_SIZE)) {
        return true;
    } else {
        return false;
    }
}
