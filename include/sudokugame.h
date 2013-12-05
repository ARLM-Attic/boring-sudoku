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

/*
 * Sudoku game contains the rules of the Sudoku, including the validation of 
 * the digit and available digit for certain position.
 */

#ifndef __SUDOKUGAME_H_
#define __SUDOKUGAME_H_

#include <vector>

class SudokuGame {
public:
    ///
    /// \brief The type of the Sudoku game
    ///
    enum _sudokuType {
        SUDOKU_TYPE_9X9 = 9,
    };

    ///
    /// \brief Init the Sudoku game
    ///
    /// \param board The sudoku board
    ///
    SudokuGame(std::vector<unsigned int> *board = NULL);

    ///
    /// \brief Check if the digit is valid
    ///
    /// \param digit  The digit to be checked
    /// \param row    The row of the digit
    /// \param column The column of the digit
    ///
    /// \return true if the digit is valid
    ///
    bool isDigitValid(unsigned int digit, int row, int column);

    ///
    /// \brief Check the available digit for the row, column
    ///
    /// \param row    The row of the tile
    /// \param column The column of the tile
    ///
    /// \return Array of available digit for the tile
    ///
    std::vector<unsigned int> availableDigit(int row, int column);

    ///
    /// \brief Check if all tiles has been filled (game over condition)
    ///
    /// \return true if the game is over
    ///
    bool isGameOver();

private:
    ///
    /// \brief Check if the current row is valid
    ///
    /// \param row    The row of the digit
    /// \param column The column of the digit
    ///
    /// \return true if the current row is valid
    ///
    bool isRowValid(int row, int column);

    ///
    /// \brief Check if the current column is valid
    ///
    /// \param row    The row of the digit
    /// \param column The column of the digit
    ///
    /// \return true if the current column is valid
    ///
    bool isColumnValid(int row, int column);

    ///
    /// \brief Check if the subboard is valid
    ///
    /// \param row    The row of the digit
    /// \param column The column of the digit
    ///
    /// \return true if the current subboard is valid
    ///
    bool isSubboardValid(int row, int column);

    ///
    /// \brief Pointer to the sudoku board
    ///
    std::vector<unsigned int> *_sudokuBoard;
};

#endif // __SUDOKUGAME_H_
