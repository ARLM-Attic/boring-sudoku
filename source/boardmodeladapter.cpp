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

#include "boardmodeladapter.h"

BoardModelAdapter::BoardModelAdapter(std::vector<unsigned int> *model,
                                     unsigned int               columnSize) :
    _model(model), 
    _modelMask(NULL), 
    _columnSize(columnSize), 
    _rowSize(0), 
    _maskIsEnabled(false)
{
    calculateRowSize();
}

BoardModelAdapter::~BoardModelAdapter() {
}

void BoardModelAdapter::setModel(std::vector<unsigned int> *model) {
    _model = model;
    calculateRowSize();
}

void BoardModelAdapter::setModelMask(std::vector<bool> *modelMask) {
    _modelMask = modelMask;
    enableMask();
}

void BoardModelAdapter::enableMask() {
    _maskIsEnabled = true;
}

void BoardModelAdapter::disableMask() {
    _maskIsEnabled = false;
}

unsigned int BoardModelAdapter::size() {
    return _model->size();
}


unsigned int BoardModelAdapter::columnSize() {
    return _columnSize;
}

unsigned int BoardModelAdapter::rowSize() {
    return _rowSize;
}

unsigned int BoardModelAdapter::value(int row, int column) {
    if (_maskIsEnabled) {
        if ((*_modelMask)[(row * _columnSize) + column] == true) {
            return BOARDMODEL_MASK_VALUE;
        } else {
            return (*_model)[(row * _columnSize) + column];
        }
    } else {
        return (*_model)[(row * _columnSize) + column];
    }
}

void BoardModelAdapter::setValue(unsigned int value, int row, int column) {
    if (_maskIsEnabled) {
        if ((*_modelMask)[(row * _columnSize) + column] == false) {
            (*_model)[(row * _columnSize) + column] = value;
        } else {
            // The tile is masked. Ignore the setValue request
        }
    } else {
        (*_model)[(row * _columnSize) + column] = value;
    }
}

bool BoardModelAdapter::tileIsInBoard(int row, int column) {
    if ( (unsigned int) row >= _rowSize) {
        // Row is out of bounds
        return false;
    }

    if ((unsigned int) column >= _columnSize) {
        // Column is out of bounds
        return false;
    }

    if ( ((row * _columnSize) + column) >= _model->size()) {
        // Row / column is not available in the board
        return false;
    } else {
        return true;
    }
}

bool BoardModelAdapter::tileIsSelectable(int row, int column) {
    if (_maskIsEnabled) {
        if ((*_modelMask)[(row * _columnSize) + column] == true) {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

void BoardModelAdapter::calculateRowSize() {
    if (_model != NULL) {
        // In good case, the size fits the columnSize
        _rowSize = (_model->size() / _columnSize);

        // But sometimes, the size doesn't fit the whole columnSize, and 
        // therefore it needs some adjustment
        if ((_model->size() % _columnSize) > 0) {
            _rowSize += 1;
        }
    }
}
