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
 * The sudoku board consist of two parts: user modifiable tile, and puzzle tile
 * (non user-modifiable tile). This class provide some mask to limit user 
 * changes on the sudoku board.
 */

#ifndef __BOARDMODELMASK_H_
#define __BOARDMODELMASK_H_

#include <vector>
#include "boardmodel.h"

class BoardModelMask : public BoardModel {
public:
    ///
    /// \brief Init the board mask
    ///
    /// \param originalModel The board original model
    /// \param maskValue     The value of the tile if the tile is masked.
    ///                      This value should be drawn as transparent in the 
    ///                      view
    ///
    BoardModelMask(BoardModel       *originalModel, 
                   int               maskValue);
    
    virtual ~BoardModelMask() { }

    ///
    /// \brief Set the model mask
    ///
    /// \param mask The model mask
    ///
    void setModelMask(std::vector<bool> mask);

    virtual unsigned int size();
    
    virtual int columnSize();
    virtual int rowSize();
    
    virtual bool tileIsInBoard(int row, int column);

    virtual int  value(int row, int column);
    virtual void setValue(int value, int row, int column);

private:
    ///
    /// \brief The board original model
    ///
    BoardModel *_originalModel;

    ///
    /// \brief The mask (to determine if the tile is modifiable or not)
    ///
    std::vector<bool> _boardmask;

    ///
    /// \brief The value of the tile if the tile is masked.
    ///
    int _maskValue;
};

#endif
