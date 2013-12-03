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

/*
 * Render the board layout into Sudoku board
 */

#ifndef __SUDOKUBOARDLAYOUT_H_
#define __SUDOKUBOARDLAYOUT_H_

#include "boardlayout.h"

class SudokuBoardLayout : public BoardLayout {
public:
    SudokuBoardLayout(BoardModelAdapter *board        = NULL, 
                      sf::Vector2u       tileSize     = sf::Vector2u(0, 0),
                      sf::Vector2f       screenSize   = sf::Vector2f(0, 0), 
                      sf::Vector2f       screenOffset = sf::Vector2f(0, 0)
    );
    
    virtual SudokuBoardLayout::~SudokuBoardLayout();

    virtual sf::Vector2f tilePositionInScreen(int row, int column);
};

#endif // __SUDOKUBOARDLAYOUT_H_
