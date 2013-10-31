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
 * Store the board's information (its graphic properties)
 */

#ifndef __BOARDVIEW_H_
#define __BOARDVIEW_H_

#include "abstractviewer.h"
#include "tileview.h"

class BoardView : public AbstractViewer {
public:
    ///
    /// \brief The board's view constructor
    ///
    /// \param columnSize   The size of the board's column
    /// \param board        The board's model
    /// \param screenSize   The screen size
    /// \param screenOffset The offset from screen to be added
    ///
    explicit BoardView(const int    columnSize, 
                       std::vector<int> *board,
                       sf::Vector2f screenSize,
                       sf::Vector2f screenOffset = sf::Vector2f(0, 0));

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
    /// \brief Set the board's layout
    ///
    /// This function can be overriden to create different board layout
    ///
    virtual void setLayout(sf::Vector2f screenSize, 
                           sf::Vector2f screenOffset);

    ///
    /// \brief The board's column size
    ///
    const int _columnSize;

    ///
    /// \brief The board tiles
    ///
    std::vector<TileView> _boardTiles;

private:
    ///
    /// \brief Pointer to the board's model
    ///
    std::vector<int> *_board;

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
