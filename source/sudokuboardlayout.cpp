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

#include "sudokuboardlayout.h"

// Define sub-board column size (because the board is only defining the total 
// column size)
#define SUBBOARD_COLUMN_SIZE_2  4
#define SUBBOARD_COLUMN_SIZE_3  9
#define SUBBOARD_COLUMN_SIZE_4  16

SudokuBoardLayout::SudokuBoardLayout(BoardModelAdapter *board, 
                                     sf::Vector2u       tileSize,
                                     sf::Vector2f       screenSize, 
                                     sf::Vector2f       screenOffset) :
    BoardLayout(board, tileSize, screenSize, screenOffset)
{
}

SudokuBoardLayout::~SudokuBoardLayout() {
}

sf::Vector2f SudokuBoardLayout::tilePositionInScreen(int row, int column) {
    // Init the tile's position in screen. 
    // All of the coordinates are based on tileSize value. 
    // The distance between the tiles is (1/4 * tileSize). The 
    // distance between sub-board is (1/2 * tileSize).
    //
    // Based on this measurement, the center for :
    // 4x4 board = (2.75 tileSize, 2.75 tileSize)
    // 9x9 board = (6    tileSize, 6    tileSize)
    //16x16board = (10.5 tileSize, 10.5 tileSize)
    //
    // Using these formulas:
    //     screenColCenter = n.tileSize + colOffset 
    //     screenRowCenter = n.tileSize + rowOffset 
    // We will always draw the board in the center of the screen
    //
    float screenColCenter = _screenSize.x / 2;
    float screenRowCenter = _screenSize.y / 2;
    
    float colOffset = _screenOffset.x + screenColCenter;
    float rowOffset = _screenOffset.y + screenRowCenter;
    
    int subboardSize;
    switch (_board->columnSize()) {
    case SUBBOARD_COLUMN_SIZE_2:
        colOffset -= (2.75f * _tileSize.x);
        rowOffset -= (2.75f * _tileSize.y);
        subboardSize = 2;
        break;
    case SUBBOARD_COLUMN_SIZE_3:
        colOffset -= (  6.f * _tileSize.x);
        rowOffset -= (  6.f * _tileSize.y);
        subboardSize = 3;
        break;
    case SUBBOARD_COLUMN_SIZE_4:
        colOffset -= (10.5f * _tileSize.x);
        rowOffset -= (10.5f * _tileSize.y);
        subboardSize = 4;
        break;
    }

    float x = 0.75f + (1.25f * column) + (0.25f * (column / subboardSize));
    float y = 0.75f + (1.25f * row)    + (0.25f * (row    / subboardSize));

    x = (x * _tileSize.x) + colOffset;
    y = (y * _tileSize.y) + rowOffset;

    return sf::Vector2f(x, y);
}
