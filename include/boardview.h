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
 * Store the board's view information (its graphic properties)
 */

#ifndef __BOARDVIEW_H_
#define __BOARDVIEW_H_

#include "abstractviewer.h"
#include "boardmodel.h"
#include "tileview.h"

// Define the size of the tile in the texture
#define TILESIZE_IN_PIXEL   sf::Vector2u(24, 24)

class BoardView : public AbstractViewer {
public:
    ///
    /// \brief The board's view constructor
    ///
    /// \param board           The board's model
    /// \param textureFilename The board's tilemap texture. The tilemap should 
    ///                        be in 24x24pixel size
    /// \param screenSize      The drawable screen size
    /// \param screenOffset    The offset of the drawable screen from the real
    ///                        screen
    ///
    explicit BoardView(BoardModel        *board,
                       const std::string &tilemapFilename,
                       sf::Vector2f       screenSize, 
                       sf::Vector2f       screenOffset = sf::Vector2f(0, 0));

    //-------------------------------------------------------------------------
    // Part of board's view layout. To be used by the cursor view, and board 
    // view

    ///
    /// \brief Get the tile in row, column's screen coordinate
    ///
    /// \param row    The row where the tile's reside
    /// \param column The column where the tile's reside
    ///
    /// \return The tile's position in screen
    ///
    virtual sf::Vector2f tilePositionInScreen(int row, int column);

    //-------------------------------------------------------------------------
    // Override the AbstractViewer's methods
    virtual void update(sf::Time elapsedTime);
    virtual void draw(sf::RenderWindow *win);

    ///
    /// \brief Virtual destructor so this class can be overridden
    ///
    virtual ~BoardView() { }

protected:
    ///
    /// \brief The board tiles
    ///
    std::vector<TileView> _boardTiles;

    ///
    /// \brief Pointer to the board's model
    ///
    BoardModel *_board;

    ///
    /// \brief The drawable screen size
    ///
    sf::Vector2f _screenSize;

    ///
    /// \brief The offset of the drawable screen from the real
    ///        screen
    ///
    sf::Vector2f _screenOffset;

private:
    ///
    /// \brief The tile texture for the board
    ///
    sf::Texture _tileTexture;
    
    ///
    /// \brief The tiles' vertex to draw
    ///
    std::vector<sf::Vertex> _vertex;
};

#endif // __BOARDVIEW_H_
