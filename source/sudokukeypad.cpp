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

#include "sudokukeypad.h"

SudokuKeypad::SudokuKeypad(sf::Texture *tilemap,
                          sf::Vector2u tileSize,
                          sf::Vector2f screenSize,
                          sf::Vector2f screenOffset) :
    _keypadIsShowed(false) 
{
    for (int i = 0; i < 10; i++) {
        _sudokukeypad.push_back(SudokuTile(tilemap, tileSize));

        // Set keypad value. Note that value '0' refers to blank tile texture, 
        // and '11' refers to 'X' tile
        _sudokukeypad[i].setValue(i + 1);
    }

    // Init the tile's position in screen. 
    // All of the coordinates are based on tileSize value. 
    // The distance between the tiles is (1/4 * tileSize). 
    //
    // Based on this measurement, the center for keypad is:
    // (2 tileSize, 2.625 tileSize)
    //
    // Using these formulas:
    //     screenColCenter = n.tileSize + colOffset 
    //     screenRowCenter = n.tileSize + rowOffset 
    // We will always draw the board in the center of the screen
    //
    float screenColCenter = screenSize.x / 2;
    float screenRowCenter = screenSize.y / 2;

    float colOffset = screenOffset.x + screenColCenter - (2.f    * tileSize.x);
    float rowOffset = screenOffset.y + screenRowCenter - (2.625f * tileSize.y);

    // Adjust the position for all of the tiles
    const int COL_SIZE = 3;
    int row = 0;
    int col = 0;

    for (int i_tile = 0; i_tile < _sudokukeypad.size(); i_tile++) {
        float x = 0.75f + (1.25f * col);
        float y = 0.75f + (1.25f * row);

        x = (x * (_sudokukeypad[i_tile].getTileSize().x)) + colOffset;
        y = (y * (_sudokukeypad[i_tile].getTileSize().y)) + rowOffset;

        _sudokukeypad[i_tile].setPosition(sf::Vector2f(x, y));

        col++;
        if (col == COL_SIZE) {
            col = 0; row++;
        }
    }
}

void SudokuKeypad::show() {
    _keypadIsShowed = true;
}

void SudokuKeypad::hide() {
    _keypadIsShowed = false;
}

void SudokuKeypad::update(sf::Time elapsedTime) {
    _vertex.clear();

    if (_keypadIsShowed) {
        for (unsigned int i = 0; i < _sudokukeypad.size(); i++) {
            _sudokukeypad[i].update(elapsedTime);
            _vertex.insert( _vertex.end(), 
                            _sudokukeypad[i].begin(), 
                            _sudokukeypad[i].end()
            );
        }
    }
}
