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
 * The board model implementation
 */

#include "boardmodel.h"

BoardModel::BoardModel(unsigned int size, int columnSize) :
    _columnSize(columnSize) {
    _board.resize(size);

    // In good case, the size fits the columnSize
    _rowSize = (size / _columnSize);
    
    // But sometimes, the size doesn't fit the whole columnSize, and therefore
    // it needs some adjustment
    if ((size % _columnSize) > 0) {
        _rowSize += 1;
    }
}

bool BoardModel::tileIsInBoard(int row, int column) {
    if ((row < 0) || ( rowSize() <= row)) {
        // Row is out of bounds
        return false;
    }

    if ((column < 0) || ( columnSize() <= column)) {
        // Column is out of bounds
        return false;
    }

    if ((unsigned int) ((row * columnSize()) + column) >= _board.size()) {
        // Row / column is not available in the board
        return false;
    } else {
        return true;
    }
}

int BoardModel::value(int row, int column) {
    return _board[(row * columnSize()) + column];
}

void BoardModel::setValue(int value, int row, int column) {
    _board[(row * columnSize()) + column] = value;
}
