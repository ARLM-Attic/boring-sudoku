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

/* Sudoku board layout
 *
 * SUDOKUBOARD_SIZE_4X4:
 * |-----------|-----------|
 * |(0,0)|(0,1)|(0,2)|(0,3)|
 * | subboard_a|subboard_b |
 * |-----------|-----------|
 * | subboard_c|subboard_d |
 * |(3,0)|(3,1)|(3,2)|(3,3)|
 * |-----------|-----------|
 *
 * SUDOKUBOARD_SIZE_9X9: 
 * |-----------------|-----------------|-----------------|
 * |(0,0)|(0,1)|(0,2)|(0,3)|(0,4)|(0,5)|(0,6)|(0,7)|(0,8)|
 * |   subboard_a    |   subboard_b    |   subboard_c    |
 * |(2,0)|     |     |     |     |     |     |     |     |
 * |-----------------|-----------------|-----------------|
 * |(3,0)|     |     |     |     |     |     |     |     |
 * |   subboard_d    |   subboard_e    |   subboard_f    |
 * |(5,0)|     |     |     |     |     |     |     |     |
 * |-----------------|-----------------|-----------------|
 * |(6,0)|     |     |     |     |     |     |     |     |
 * |   subboard_g    |   subboard_h    |   subboard_i    |
 * |(8,0)|     |     |     |     |     |     |     |     |
 * |-----------------|-----------------|-----------------|
 */

#ifndef __SUDOKUBOARDVIEW_H_
#define __SUDOKUBOARDVIEW_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "boardview.h"

class SudokuBoardView : public BoardView {
public:
    ///
    /// \brief Generate sudoku board, with specific size and tileset
    ///
    /// \param board           The board's model
    /// \param textureFilename The board's tilemap texture. The tilemap should 
    ///                        be in 24x24pixel size
    /// \param screenSize      The drawable screen size
    /// \param screenOffset    The offset of the drawable screen from the real
    ///                        screen
    ///
    explicit SudokuBoardView(BoardModel        *board,
                             const std::string &tilemapFilename,
                             sf::Vector2f       screenSize, 
                             sf::Vector2f       screenOffset = sf::Vector2f(0, 0));


    //-------------------------------------------------------------------------
    // Part of board's view layout. To be used by the cursor view, and board 
    // view

    ///
    /// \brief Get the tile in row, column's screen coordinate
    ///
    /// \param row    The row where the tile's reside
    /// \param column The column where the tile's reside
    ///
    /// \return The tile's position in screen
    ///
    virtual sf::Vector2f tilePositionInScreen(int row, int column);
};

#endif // __SUDOKUBOARDVIEW_H_
