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

#include "boardlayout.h"

BoardLayout::BoardLayout(BoardModelAdapter *board, 
                         sf::Vector2u       tileSize,
                         sf::Vector2f       screenSize, 
                         sf::Vector2f       screenOffset) :
    _board(board), 
    _tileSize(tileSize),
    _screenSize(screenSize), 
    _screenOffset(screenOffset) {
}

BoardLayout::~BoardLayout() {
}

void BoardLayout::setTileLayout(std::vector<TileView> *tiles) {
    for (unsigned int row = 0; row < _board->rowSize(); row++) {
        for (unsigned int col = 0; col < _board->columnSize(); col++) {
            if (_board->tileIsInBoard(row, col)) {
                TileView *tile = &(*tiles)[(row * _board->columnSize()) + col];
                sf::Vector2f tilePos = tilePositionInScreen(row, col);

                tile->setPosition(tilePos);
            }
        }
    }
}

sf::Vector2f BoardLayout::tilePositionInScreen(int row, int column) {
    // The default board layout will look like this:
    //    XX XX XX .. (_columnSize)
    //    XX XX XX .. (_columnSize)
    //    XX -> (if the tile doesn't fill up the whole column)

    sf::Vector2f tilePos = sf::Vector2f(
        _screenOffset.x + ((0.75f + (column * 1.25f)) * _tileSize.x),
        _screenOffset.y + ((0.75f + (row    * 1.25f)) * _tileSize.y)
    );

    return tilePos;
}

sf::Vector2u BoardLayout::tileSize() const {
    return _tileSize;
}
