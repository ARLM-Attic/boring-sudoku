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

BoardView::BoardView(const int    columnSize, 
                     std::vector<int> *board,
                     sf::Vector2f screenSize,
                     sf::Vector2f screenOffset) :
        _columnSize(columnSize), 
        _board(board), 
        _tileTexture() 
{
    // Load the tile texture
    _tileTexture.loadFromFile("artwork/sudoku-numbertiles-24px.png");
    
    // Define the size of the tile in the texture
    sf::Vector2u tileSize = sf::Vector2u(24, 24);

    // Create tile view for each of tile
    for (unsigned int i = 0; i < (*_board).size(); i++) {
        TileView tile(&(*_board)[i], 
                      &_tileTexture, 
                      tileSize);
        _boardTiles.push_back(tile);
    }

    // Setup the layout of the board
    setLayout(screenSize, screenOffset);
}

void BoardView::setLayout(sf::Vector2f screenSize, 
                          sf::Vector2f screenOffset) {
    // The default board layout will look like this:
    //    XX XX XX .. (_columnSize)
    //    XX XX XX .. (_columnSize)
    //    XX -> (if the tile doesn't fill up the whole column)
    
    int row = 0, col = 0;
    for (unsigned int i = 0; i < (*_board).size(); i++) {
        TileView *tile = &_boardTiles[i];
        
        sf::Vector2u tileSize = tile->getTileSize();
        sf::Vector2f tilePos = sf::Vector2f(
            screenOffset.x + ((0.75f + (col * 1.25f)) * tileSize.x),
            screenOffset.y + ((0.75f + (row * 1.25f)) * tileSize.y)
        );

        tile->setPosition(tilePos);

        col++;
        if (col == _columnSize) {
            col = 0;
            row++;
        }
    }

    // Keep the last row to be used by the cursor
    // row is index to the row, the size of the row is (row + 1)
    _rowSize = (row + 1);
}

void BoardView::update(sf::Time elapsedTime) {
    _vertex.clear();

    for (unsigned int i = 0; i < _boardTiles.size(); i++) {
        _boardTiles[i].update(elapsedTime);
        _vertex.insert( _vertex.end(), 
                        _boardTiles[i].begin(), 
                        _boardTiles[i].end()
        );
    }
}

void BoardView::draw(sf::RenderWindow *win) {
    win->draw(&_vertex[0], 
              _vertex.size(), 
              sf::Quads, 
              &_tileTexture);
}

bool BoardView::tileIsInBoard(int row, int column) {
    unsigned int tileInBoard = (row * _columnSize) + column;

    if (tileInBoard < _boardTiles.size()) {
        return true;
    } else {
        return false;
    }
}

sf::Vector2f BoardView::tilePosition(int row, int column) {
    int tileInBoard = (row * _columnSize) + column;
    
    return _boardTiles[tileInBoard].getPosition();
}
