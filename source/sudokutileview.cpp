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

#include "sudokutileview.h"

SudokuTileView::SudokuTileView(
            int         *tileValue, 
            sf::Texture *tilemap, 
            sf::Vector2u tileSize) :
    _texture  (tilemap), 
    _tileSize (tileSize)
{
    // Each tile requires 4 Vertex points
    _vertex.resize(4);

    _tileValue = tileValue;
    setPosition(sf::Vector2f(0, 0));
}

void SudokuTileView::update(sf::Time elapsedTime) {
    // Get the tile value
    int tileValue = *_tileValue;

    // Adjust the texture to match the value
    sf::Vector2u textureSize = _texture->getSize();

    // Find the _tileValue column in the texture
    float tu = (float) (tileValue % (textureSize.x / _tileSize.x));
    // Find the _tileValue row in the texture
    float tv = (float) (tileValue / (textureSize.x / _tileSize.x));

    _vertex[0].texCoords = sf::Vector2f(
        (tu       * _tileSize.x), (tv       * _tileSize.y)
    );
    _vertex[1].texCoords = sf::Vector2f(
        ((tu + 1) * _tileSize.x), (tv       * _tileSize.y)
    );
    _vertex[2].texCoords = sf::Vector2f(
        ((tu + 1) * _tileSize.x), ((tv + 1) * _tileSize.y)
    );
    _vertex[3].texCoords = sf::Vector2f(
        (tu       * _tileSize.x), ((tv + 1) * _tileSize.y)
    );


    // Adjust the position for the tiles (in the screen)
    float leftColumn  = _tilePos.x - (_tileSize.x / 2);
    float rightColumn = _tilePos.x + _tileSize.x - (_tileSize.x / 2);
    float topRow      = _tilePos.y - (_tileSize.y / 2);
    float bottomRow   = _tilePos.y + _tileSize.y - (_tileSize.y / 2);
    
    _vertex[0].position = sf::Vector2f( leftColumn,    topRow);
    _vertex[1].position = sf::Vector2f(rightColumn,    topRow);
    _vertex[2].position = sf::Vector2f(rightColumn, bottomRow);
    _vertex[3].position = sf::Vector2f( leftColumn, bottomRow);
}
