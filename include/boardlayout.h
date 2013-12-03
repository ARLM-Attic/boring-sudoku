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
 * The board layout is needed to render the board, and the cursor position.
 */

#ifndef __BOARDLAYOUT_H_
#define __BOARDLAYOUT_H_

#include <SFML/Graphics.hpp>
#include "boardmodeladapter.h"
#include "tileview.h"

class BoardLayout {
public:
    ///
    /// \brief Init the board layout
    ///
    /// \param board        The board model
    /// \param tileSize     The tile size
    /// \param screensize   The drawable screen size
    /// \param screenOffset The offset of the drawable screen from the real
    ///                     screen
    ///
    explicit BoardLayout(BoardModelAdapter *board        = NULL, 
                sf::Vector2u       tileSize     = sf::Vector2u(0, 0),
                sf::Vector2f       screenSize   = sf::Vector2f(0, 0), 
                sf::Vector2f       screenOffset = sf::Vector2f(0, 0)
    );
    
    virtual BoardLayout::~BoardLayout();

    ///
    /// \brief Set the tile layout
    ///
    /// \param tiles The board tiles to be set
    ///
    void setTileLayout(std::vector<TileView> *tiles);

    ///
    /// \brief Get the tile in row, column's screen coordinate
    ///
    /// \param row    The row where the tile's reside
    /// \param column The column where the tile's reside
    ///
    /// \return The tile's position in screen
    ///
    virtual sf::Vector2f tilePositionInScreen(int row, int column);

    ///
    /// \brief Read the tile size 
    ///
    sf::Vector2u tileSize() const;

protected:
    ///
    /// \brief Pointer to the board's model
    ///
    BoardModelAdapter *_board;

    ///
    /// \brief The tilesize (in pixel)
    ///
    sf::Vector2u _tileSize;

    ///
    /// \brief The drawable screen size
    ///
    sf::Vector2f _screenSize;

    ///
    /// \brief The offset of the drawable screen from the real
    ///        screen
    ///
    sf::Vector2f _screenOffset;
};

#endif // __BOARDLAYOUT_H_
