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

#include "sudokuboard.h"

SudokuBoard::SudokuBoard(enum t_sudokuboard_size size, 
                         sf::Texture            *tilemap,
                         sf::Vector2u            tileSize,
                         sf::Vector2f            screenSize) :
    _subboardSize(static_cast<int> (size)) 
{
    for (int i = 0; i < (getBoardSize() * getBoardSize()); i++) {
        _sudokuboard.push_back(SudokuTile(tilemap, tileSize));
    }

    // Init the tile's position in screen. 
    // All of the coordinates are based on tileSize value. 
    // The distance between the tiles is (1/4 * tileSize). The 
    // distance between sub-board is (1/2 * tileSize).
    //
    // Based on this measurement, the center for :
    // 4x4 board = (2.75 tileSize, 2.75 tileSize)
    // 9x9 board = (5.75 tileSize, 5.75 tileSize)
    //16x16board = (9.75 tileSize, 9.75 tileSize)
    //
    // Using these formulas:
    //     screenColCenter = n.tileSize + colOffset 
    //     screenRowCenter = n.tileSize + rowOffset 
    // We will always draw the board in the center of the screen
    //
    float screenColCenter = screenSize.x / 2;
    float screenRowCenter = screenSize.y / 2;
    float rowOffset, colOffset;
    
    switch (size) {
    case SUDOKUBOARD_SIZE_4X4:
        colOffset = screenColCenter - (2.75f * tileSize.x);
        rowOffset = screenRowCenter - (2.75f * tileSize.y);
        break;
    case SUDOKUBOARD_SIZE_9X9:
        colOffset = screenColCenter - ( 6.0f * tileSize.x);
        rowOffset = screenRowCenter - ( 6.0f * tileSize.y);
        break;
    case SUDOKUBOARD_SIZE_16X16:
        colOffset = screenColCenter - (10.5f * tileSize.x);
        rowOffset = screenRowCenter - (10.5f * tileSize.y);
        break;
    }

    // Adjust the position for all of the tiles
    for (int row = 0; row < getBoardSize(); row++) {
        for (int col = 0; col < getBoardSize(); col++) {
            float x = 0.75f + (1.25f * col) + 
                     (0.25f * (col / getSubboardSize()));
            float y = 0.75f + (1.25f * row) + 
                     (0.25f * (row / getSubboardSize()));

            SudokuTile *tile = &_sudokuboard[(row * getBoardSize()) + col];

            x = (x * (tile->getTileSize().x)) + colOffset;
            y = (y * (tile->getTileSize().y)) + rowOffset;
            tile->setPosition(sf::Vector2f(x, y));
        }
    }
}

void SudokuBoard::update(sf::Time elapsedTime) {
    _vertex.clear();

    for (unsigned int i = 0; i < _sudokuboard.size(); i++) {
        _sudokuboard[i].update(elapsedTime);
        _vertex.insert( _vertex.end(), 
                        _sudokuboard[i].begin(), 
                        _sudokuboard[i].end()
        );
    }
}
