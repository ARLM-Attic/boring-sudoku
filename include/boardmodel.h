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
 * The board model. This is the generic board model that can be used for the 
 * keypad and the sudoku board
 */

#ifndef __BOARDMODEL_H_
#define __BOARDMODEL_H_

#include <vector>

class BoardModel {
public:
    ///
    /// \brief Create board model
    ///
    /// \param size       The size of the board (in term of item size)
    /// \param columnSize The size of the column. The row size is
    ///                   automatically calculated
    ///
    BoardModel(unsigned int size = 0, int columnSize = 1);

    virtual ~BoardModel() { }
    
    ///
    /// \brief Check the board's size
    ///
    /// \return the board size (in no of tiles that are available)
    ///
    virtual unsigned int size() {
        return _board.size();
    }

    ///
    /// \brief Check the column size
    ///
    /// This function is needed to interface the cursor with the board
    ///
    /// \return the column size
    ///
    virtual int columnSize() {
        return _columnSize;
    }

    ///
    /// \brief Check the row size
    ///
    /// This function is needed to interface the cursor with the board
    ///
    /// \return the row size
    ///
    virtual int rowSize() {
        return _rowSize;
    }

    ///
    /// \brief Check whether the tile (pointed by its row / column in the 
    ///        board) is available
    ///
    /// This function is needed to interface the cursor with the board
    ///
    /// \param row    The row where the tile lies
    /// \param column The column where the tile lies
    ///
    /// \return true if the tile lies within the board
    ///
    virtual bool tileIsInBoard(int row, int column);

    ///
    /// \brief Get the tile value at row / column
    ///
    /// Check whether the tile is within the board before issuing this query
    ///
    /// \param row    The row where the tile lies
    /// \param column The column where the tile lies
    ///
    /// \return the tile value
    ///
    virtual int value(int row, int column);

    ///
    /// \brief Set the tile value at row / column
    ///
    /// Check whether the tile is within the board before issuing this query
    ///
    /// \param row    The row where the tile lies
    /// \param column The column where the tile lies
    ///
    virtual void setValue(int value, int row, int column);

protected:
    ///
    /// \brief The board, with its value
    ///
    std::vector<int> _board;

    ///
    /// \brief The board's column size
    ///
    int _columnSize;

    ///
    /// \brief The board's row size
    ///
    int _rowSize;
};

#endif
