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

/* Sudoku board layout
 *
 * SUDOKUBOARD_SIZE_4X4:
 * |-----------|-----------|
 * |(0,0)|(0,1)|(0,2)|(0,3)|
 * | subboard_a|subboard_b |
 * |-----------|-----------|
 * | subboard_c|subboard_d |
 * |(3,0)|(3,1)|(3,2)|(3,3)|
 * |-----------|-----------|
 *
 * SUDOKUBOARD_SIZE_9X9: 
 * |-----------------|-----------------|-----------------|
 * |(0,0)|(0,1)|(0,2)|(0,3)|(0,4)|(0,5)|(0,6)|(0,7)|(0,8)|
 * |   subboard_a    |   subboard_b    |   subboard_c    |
 * |(2,0)|     |     |     |     |     |     |     |     |
 * |-----------------|-----------------|-----------------|
 * |(3,0)|     |     |     |     |     |     |     |     |
 * |   subboard_d    |   subboard_e    |   subboard_f    |
 * |(5,0)|     |     |     |     |     |     |     |     |
 * |-----------------|-----------------|-----------------|
 * |(6,0)|     |     |     |     |     |     |     |     |
 * |   subboard_g    |   subboard_h    |   subboard_i    |
 * |(8,0)|     |     |     |     |     |     |     |     |
 * |-----------------|-----------------|-----------------|
 */

#ifndef __SUDOKUBOARDVIEW_H_
#define __SUDOKUBOARDVIEW_H_

#include <vector>
#include <SFML/Graphics.hpp>

#include "sudokutileview.h"

class SudokuBoardView {
public:
    /// 
    /// \brief The type of Sudoku board
    ///
    enum t_sudokuboard_size {
        SUDOKUBOARD_SIZE_4X4   = 2, /* 4 x  4 SudokuBoard */
        SUDOKUBOARD_SIZE_9X9   = 3, /* 9 x  9 SudokuBoard */
        SUDOKUBOARD_SIZE_16X16 = 4, /*16 x 16 SudokuBoard */
    };

    ///
    /// \brief Generate sudoku board, with specific size and tileset
    ///
    /// \param size         The sudoku size
    /// \param tilemap      The texture for the tilemap
    /// \param tilesize     The size of the board's tile (in pixel)
    /// \param screenSize   The screen size
    /// \param screenOffset The offset from screen to be added
    ///
    explicit SudokuBoardView(
            std::vector<int>       *sudokuboard,
            enum t_sudokuboard_size size, 
            sf::Texture            *tilemap,
            sf::Vector2u            tileSize,
            sf::Vector2f            screenSize,
            sf::Vector2f            screenOffset = sf::Vector2f(0, 0));

    ///
    /// \brief Get the tile's position in the screen
    ///
    /// \param row    The row where the tile is located
    /// \param column The column where the tile is located
    ///
    /// \return The tile position in the screen
    ///
    sf::Vector2f getTilePosition(int row, int column);

    //-------------------------------------------------------------------------
    // Interface to get the board to be drawn in the screen

    ///
    /// \brief Update the board to be displayed
    ///
    /// \param elapsedTime The time that has elapsed since the last update
    ///
    void update(sf::Time elapsedTime);

    std::vector<sf::Vertex>::iterator begin() {
        return _vertex.begin();
    }

    std::vector<sf::Vertex>::iterator end() {
        return _vertex.end();
    }

    std::vector<sf::Vertex>::const_iterator begin() const {
        return _vertex.begin();
    }

    std::vector<sf::Vertex>::const_iterator end() const {
        return _vertex.end();
    }

private:
    ///
    /// \brief The sudoku sub board's size
    ///
    const int _subboardSize;

    ///
    /// \brief The sudoku board model
    ///
    const std::vector<int> *_sudokuboard;

    ///
    /// \brief The sudoku board tiles
    ///
    std::vector<SudokuTileView> _sudokuboardview;

    ///
    /// \brief The vertex to draw the board
    ///
    std::vector<sf::Vertex> _vertex;
};

#endif // __SUDOKUBOARDVIEW_H_
