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

#include "boardview.h"

BoardView::BoardView(BoardModel        *board,
                     const std::string &tilemapFilename,
                     sf::Vector2f       screenSize, 
                     sf::Vector2f       screenOffset) :
        _board(board), 
        _tileTexture(),
        _screenSize(screenSize),
        _screenOffset(screenOffset)
{
    // Make sure the view is closed when init'd
    _isShowed = false;

    // Load the tile texture
    _tileTexture.loadFromFile(tilemapFilename);
    
    // Create tile view for each of tile
    for (unsigned int i = 0; i < _board->size(); i++) {
        TileView tile(&_tileTexture, 
                      TILESIZE_IN_PIXEL);
        _boardTiles.push_back(tile);
    }

    // Setup the layout of the board
    for (int row = 0; row < _board->rowSize(); row++) {
        for (int col = 0; col < _board->columnSize(); col++) {
            if (_board->tileIsInBoard(row, col)) {
                TileView *tile = &_boardTiles[(row * _board->columnSize()) + col];
                sf::Vector2f tilePos = tilePositionInScreen(row, col);

                tile->setPosition(tilePos);
            }
        }
    }
}

sf::Vector2f BoardView::tilePositionInScreen(int row, int column) {
    // The default board layout will look like this:
    //    XX XX XX .. (_columnSize)
    //    XX XX XX .. (_columnSize)
    //    XX -> (if the tile doesn't fill up the whole column)

    sf::Vector2u tileSize = TILESIZE_IN_PIXEL;
    sf::Vector2f tilePos = sf::Vector2f(
        _screenOffset.x + ((0.75f + (column * 1.25f)) * tileSize.x),
        _screenOffset.y + ((0.75f + (row    * 1.25f)) * tileSize.y)
    );

    return tilePos;
}

void BoardView::update(sf::Time elapsedTime) {
    _vertex.clear();

    for (int row = 0; row < _board->rowSize(); row++) {
        for (int col = 0; col < _board->columnSize(); col++) {
            if (_board->tileIsInBoard(row, col)) {
                TileView *tile = &_boardTiles[(row * _board->columnSize()) + col];

                tile->setFace(_board->value(row, col));
                tile->update(elapsedTime);
                _vertex.insert( _vertex.end(), tile->begin(), tile->end());
            }
        }
    }
}

void BoardView::draw(sf::RenderWindow *win) {
    // Don't draw if it's not supposed to be shown
    if (!_isShowed) {
        return;
    }

    win->draw(&_vertex[0], 
              _vertex.size(), 
              sf::Quads, 
              &_tileTexture);
}
