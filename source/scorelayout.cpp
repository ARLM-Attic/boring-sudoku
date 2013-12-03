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

#include "scorelayout.h"

ScoreLayout::ScoreLayout(BoardModelAdapter *board, 
                         sf::Vector2u       tileSize,
                         sf::Vector2f       screenSize, 
                         sf::Vector2f       screenOffset) :
    BoardLayout(board, tileSize, screenSize, screenOffset)
{
}

ScoreLayout::~ScoreLayout() {
}

sf::Vector2f ScoreLayout::tilePositionInScreen(int row, int column) {
    sf::Vector2f tilePos = sf::Vector2f(
        _screenOffset.x + ((0.5f + column) * _tileSize.x),
        _screenOffset.y + ((0.5f + row   ) * _tileSize.y)
    );

    return tilePos;
}
