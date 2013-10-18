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

#include "sudokuboard.h"

#define OFFSET_BETWEEN_THE_BOARD_AND_SCREEN_COLUMN_IN_PIXEL  80.f
#define OFFSET_BETWEEN_THE_BOARD_AND_SCREEN_ROW_IN_PIXEL     10.f
#define OFFSET_BETWEEN_TILES_IN_PIXEL                         4.f
#define OFFSET_BETWEEN_SUBBOARDS_IN_PIXEL                     8.f

SudokuBoard::SudokuBoard(enum t_sudokuboard_size size, 
                         sf::Texture             tileset, 
                         sf::Vector2u            tilesize) :
        _subboardSize(size), 
        _sudokuTileset(tileset), 
        _sudokuTilesize (tilesize) 
{
    
    // For each tile in the sudoku board, we'll need 4 vertex
    _sudokuboardVertex.resize(getBoardSize() * getBoardSize() * 4);

    // Create all the subboard's vertex
    for (int row = 0; row < getBoardSize(); row += getSubboardSize()) {
        for (int col = 0; col < getBoardSize(); col += getSubboardSize()) {
            setSuboardVertex(row, col);
        }
    }
}

void SudokuBoard::setSuboardVertex(int offsetRow, int offsetCol)
{
    float gapRow   = (offsetRow / getSubboardSize()) * 
                                             OFFSET_BETWEEN_SUBBOARDS_IN_PIXEL;
    float gapColumn = (offsetCol / getSubboardSize()) * 
                                             OFFSET_BETWEEN_SUBBOARDS_IN_PIXEL;

    for (int j = offsetRow; j < (getSubboardSize() + offsetRow); j++) {
        for (int i = offsetCol; i < (getSubboardSize() + offsetCol); i++) {

            // Get a pointer to the current tile's quad
            sf::Vertex* quad = &_sudokuboardVertex[(i + (j * getBoardSize())) * 4];
            
            // Define its 4 corners
            quad[0].position = sf::Vector2f(
                (i       * (_sudokuTilesize.x + OFFSET_BETWEEN_TILES_IN_PIXEL)
                                              + OFFSET_BETWEEN_TILES_IN_PIXEL),
                (j       * (_sudokuTilesize.y + OFFSET_BETWEEN_TILES_IN_PIXEL)
                                              + OFFSET_BETWEEN_TILES_IN_PIXEL)
            );
            quad[1].position = sf::Vector2f(
                (i + 1) *  (_sudokuTilesize.x + OFFSET_BETWEEN_TILES_IN_PIXEL),
                (j       * (_sudokuTilesize.y + OFFSET_BETWEEN_TILES_IN_PIXEL)
                                              + OFFSET_BETWEEN_TILES_IN_PIXEL)
            );
            quad[2].position = sf::Vector2f(
                (i + 1) * (_sudokuTilesize.x + OFFSET_BETWEEN_TILES_IN_PIXEL),
                (j + 1) * (_sudokuTilesize.y + OFFSET_BETWEEN_TILES_IN_PIXEL)
            );
            quad[3].position = sf::Vector2f(
                (i       * (_sudokuTilesize.x + OFFSET_BETWEEN_TILES_IN_PIXEL)
                                              + OFFSET_BETWEEN_TILES_IN_PIXEL),
                (j + 1) * (_sudokuTilesize.y + OFFSET_BETWEEN_TILES_IN_PIXEL)
            );

            // Add some gaps (and screen offset) between subboards
            for (int k = 0; k < 4; k++) {
                quad[k].position.x += gapColumn;
                quad[k].position.x += OFFSET_BETWEEN_THE_BOARD_AND_SCREEN_COLUMN_IN_PIXEL;
                quad[k].position.y += gapRow;
                quad[k].position.y += OFFSET_BETWEEN_THE_BOARD_AND_SCREEN_ROW_IN_PIXEL;
            }
        }
    }
}
