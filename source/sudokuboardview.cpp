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

#include "sudokuboardview.h"

// Define sub-board column size (because the board is only defining the total 
// column size)
#define SUBBOARD_COLUMN_SIZE_2  4
#define SUBBOARD_COLUMN_SIZE_3  9
#define SUBBOARD_COLUMN_SIZE_4  16

SudokuBoardView::SudokuBoardView(
            BoardModel        *board,
            const std::string &tilemapFilename,
            sf::Vector2f       screenSize, 
            sf::Vector2f       screenOffset) :
    BoardView(board, tilemapFilename, screenSize, screenOffset)
{
    // Setup the layout of the board
    for (int row = 0; row < _board->rowSize(); row++) {
        for (int col = 0; col < _board->columnSize(); col++) {
            if (_board->tileIsInBoard(row, col)) {
                TileView *tile = 
                    &_boardTiles[(row * _board->columnSize()) + col];
                sf::Vector2f tilePos = tilePositionInScreen(row, col);

                tile->setPosition(tilePos);
            }
        }
    }
}

sf::Vector2f SudokuBoardView::tilePositionInScreen(int row, int column) {
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
    sf::Vector2u tileSize = TILESIZE_IN_PIXEL;
    switch (_board->columnSize()) {
    case SUBBOARD_COLUMN_SIZE_2:
        colOffset -= (2.75f * tileSize.x);
        rowOffset -= (2.75f * tileSize.y);
        subboardSize = 2;
        break;
    case SUBBOARD_COLUMN_SIZE_3:
        colOffset -= (  6.f * tileSize.x);
        rowOffset -= (  6.f * tileSize.y);
        subboardSize = 3;
        break;
    case SUBBOARD_COLUMN_SIZE_4:
        colOffset -= (10.5f * tileSize.x);
        rowOffset -= (10.5f * tileSize.y);
        subboardSize = 4;
        break;
    }

    float x = 0.75f + (1.25f * column) + (0.25f * (column / subboardSize));
    float y = 0.75f + (1.25f * row)    + (0.25f * (row    / subboardSize));

    x = (x * tileSize.x) + colOffset;
    y = (y * tileSize.y) + rowOffset;

    return sf::Vector2f(x, y);
}
