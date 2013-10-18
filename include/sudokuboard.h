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

#ifndef __SUDOKUBOARD_H_
#define __SUDOKUBOARD_H_

#include <vector>
#include <SFML/Graphics.hpp>

class SudokuBoard {
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
    /// \param size    The sudoku size
    /// \param tileset The sudoku tileset
    ///
    explicit SudokuBoard(enum t_sudokuboard_size size, 
                         sf::Texture             tileset, 
                         sf::Vector2u            tilesize);
    ~SudokuBoard() { }

    ///
    /// \brief Set new sudoku board
    ///
    /// \param sudokuboard The new sudoku board. The board size must match the
    ///                    current sudoku board.
    ///
    void setBoard(std::vector<int> sudokuboard) {
        _sudokuboard = sudokuboard;
    }

    ///
    /// \brief Get the current sudoku board
    ///
    /// \return Sudoku board array
    ///
    std::vector<int> getBoard() {
        return _sudokuboard;
    }
    
    ///
    /// \brief Get the Sudoku tileset texture
    ///
    /// \return The tileset texture
    ///
    sf::Texture getTileset() {
        return _sudokuTileset;
    }

    ///
    /// \brief Get the board's vertex to draw the board
    ///
    /// \return The board's vertex
    ///
    std::vector<sf::Vertex> getVertex() {
        return _sudokuboardVertex;
    }

    ///
    /// \brief Get the Sudoku sub board size
    ///
    /// \return The sub board size
    ///
    int getSubboardSize() {
        return _subboardSize;
    }

    ///
    /// \brief Get the Sudoku's board size
    ///
    /// \return The board's size
    ///
    int getBoardSize() {
        return (_subboardSize * _subboardSize);
    }

private:
    /// \brief The sudoku sub board's size
    const int               _subboardSize;

    /// \brief The sudoku board values
    std::vector<int>        _sudokuboard;

    /// \brief The sudoku board vertex
    std::vector<sf::Vertex> _sudokuboardVertex;

    /// \brief The sudoku tileset texture
    sf::Texture             _sudokuTileset;

    /// \brief The sudoku tile size
    sf::Vector2u            _sudokuTilesize;

    ///
    /// \brief Create subboard's vertex, along with its gap (so each sub board
    ///        will appear separated)
    ///
    /// \param offsetRow The starting row of the sub board
    /// \param offsetCol The starting column of the sub board
    ///
    void setSuboardVertex(int offsetRow, int offsetCol);
};

#endif // __SUDOKUBOARD_H_
