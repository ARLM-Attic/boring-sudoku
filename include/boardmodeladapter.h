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
 * The game logic just need regular array to hold the board. However the game's
 * UI needs more than just an array to display the board in the screen and 
 * controlling the cursor. Hence, this class is needed to bridge both sides
 */

#ifndef __BOARDMODELADAPTER_H_
#define __BOARDMODELADAPTER_H_

#include <vector>

// The mask value must match the transparent tile in tileset. Anything that 
// uses this value will not be drawn in the view
#define BOARDMODEL_MASK_VALUE   12

class BoardModelAdapter {
public:
    ///
    /// \brief Init the board model adapter
    ///
    /// \param model      The board model
    /// \param columnSize The board column size
    ///
    BoardModelAdapter(std::vector<unsigned int> *model      = NULL,
                      unsigned int               columnSize = 0
    );

    ///
    /// \brief The standard destructor for this class
    ///
    ~BoardModelAdapter();

    //-------------------------------------------------------------------------
    // These functions are needed to interface the game logic to the GUI

    ///
    /// \brief Set the model
    ///
    /// \param model The pointer to the board model
    ///
    void setModel(std::vector<unsigned int> *model);

    ///
    /// \brief Set the model mask
    ///
    /// \param modelMask The pointer to the board model mask
    ///
    void setModelMask(std::vector<bool> *modelMask);

    ///
    /// \brief Enable the model mask
    ///
    void enableMask();

    ///
    /// \brief Disable the model mask
    ///
    void disableMask();

    //-------------------------------------------------------------------------
    // These functions are needed to interface the board view with the model

    ///
    /// \brief Get the size of the board
    ///
    /// \return The board size (no of tiles in the board)
    ///
    unsigned int size();

    ///
    /// \brief Check the column size
    ///
    /// This function is needed to interface the cursor with the board
    ///
    /// \return the column size
    ///
    unsigned int columnSize();

    ///
    /// \brief Check the row size
    ///
    /// This function is needed to interface the cursor with the board
    ///
    /// \return the row size
    ///
    unsigned int rowSize();

    ///
    /// \brief Get the tile value at row / column
    ///
    /// Check whether the tile is within the board before issuing this query
    ///
    /// \param row    The row where the tile lies
    /// \param column The column where the tile lies
    ///
    /// \return the tile value
    ///
    unsigned int value(int row, int column);

    ///
    /// \brief Set the tile value at row / column
    ///
    /// Check whether the tile is within the board before issuing this query
    ///
    /// \param row    The row where the tile lies
    /// \param column The column where the tile lies
    ///
    void setValue(unsigned int value, int row, int column);

    ///
    /// \brief Check whether the tile (pointed by its row / column in the 
    ///        board) is available
    ///
    /// \param row    The row where the tile lies
    /// \param column The column where the tile lies
    ///
    /// \return true if the tile lies within the board
    ///
    bool tileIsInBoard(int row, int column);

    //-------------------------------------------------------------------------
    // These functions are needed to interface the board cursor with the model

    ///
    /// \brief Check whether the tile (pointed by its row / column in the 
    ///        board) can be selected 
    ///
    /// If the board mask on that tile is true, the tile is not selectable
    ///
    /// \param row    The row where the tile lies
    /// \param column The column where the tile lies
    ///
    /// \return true if the tile can be selected
    ///
    bool tileIsSelectable(int row, int column);

private:
    ///
    /// \brief Calculate the row size, everytime the board model is updated
    ///
    void calculateRowSize();

    ///
    /// \brief The pointer to the real board model
    ///
    std::vector<unsigned int>  *_model;
    
    ///
    /// \brief The pointer to the board model mask
    ///
    std::vector<bool> *_modelMask;
    
    ///
    /// \brief The board column size
    ///
    unsigned int _columnSize;

    ///
    /// \brief The board row size
    ///
    unsigned int _rowSize;

    ///
    /// \brief Flag to indicate whether the mask is enabled / disabled
    ///
    bool _maskIsEnabled;
};

#endif // __BOARDMODELADAPTER_H_
