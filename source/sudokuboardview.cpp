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

SudokuBoardView::SudokuBoardView(
            std::vector<int>       *sudokuboard,
            enum t_sudokuboard_size size, 
            sf::Texture            *tilemap,
            sf::Vector2u            tileSize,
            sf::Vector2f            screenSize,
            sf::Vector2f            screenOffset) :

    _subboardSize(static_cast<int> (size)), _sudokuboard(sudokuboard)
{

    // Create tile view for each of the Sudoku tile
    int tileNo = _subboardSize * _subboardSize * _subboardSize * _subboardSize;

    for (int i = 0; i < tileNo; i++) {
        SudokuTileView tile(&(*sudokuboard)[i], tilemap, tileSize);
        _sudokuboardview.push_back(tile);
    }

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
    float screenColCenter = screenSize.x / 2;
    float screenRowCenter = screenSize.y / 2;
    
    float colOffset = screenOffset.x + screenColCenter;
    float rowOffset = screenOffset.y + screenRowCenter;
    
    switch (size) {
    case SUDOKUBOARD_SIZE_4X4:
        colOffset -= (2.75f * tileSize.x);
        rowOffset -= (2.75f * tileSize.y);
        break;
    case SUDOKUBOARD_SIZE_9X9:
        colOffset -= (  6.f * tileSize.x);
        rowOffset -= (  6.f * tileSize.y);
        break;
    case SUDOKUBOARD_SIZE_16X16:
        colOffset -= (10.5f * tileSize.x);
        rowOffset -= (10.5f * tileSize.y);
        break;
    }

    // Adjust the position for all of the tiles
    int boardSize = (_subboardSize * _subboardSize);
    for (int row = 0; row < boardSize; row++) {
        for (int col = 0; col < boardSize; col++) {
            float x = 0.75f + (1.25f * col) + (0.25f * (col / _subboardSize));
            float y = 0.75f + (1.25f * row) + (0.25f * (row / _subboardSize));

            SudokuTileView *tile = &_sudokuboardview[(row * boardSize) + col];

            x = (x * (tile->getTileSize().x)) + colOffset;
            y = (y * (tile->getTileSize().y)) + rowOffset;
            tile->setPosition(sf::Vector2f(x, y));
        }
    }
}

void SudokuBoardView::update(sf::Time elapsedTime) {
    _vertex.clear();

    for (unsigned int i = 0; i < _sudokuboardview.size(); i++) {
        _sudokuboardview[i].update(elapsedTime);
        _vertex.insert( _vertex.end(), 
                        _sudokuboardview[i].begin(), 
                        _sudokuboardview[i].end()
        );
    }
}
