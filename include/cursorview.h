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
 * Implement the cursor view. This is sudokutileview, but with single tile only
 */

#ifndef __CURSORVIEW_H_
#define __CURSORVIEW_H_

#include "abstractviewer.h"
#include "tileview.h"

class CursorView : public AbstractViewer {
public:
    explicit CursorView();
    
    //-------------------------------------------------------------------------
    // Override the AbstractViewer's methods
    virtual void update(sf::Time elapsedTime);
    virtual void draw(sf::RenderWindow *win);

    ///
    /// \brief Set the cursor's position in the screen
    ///
    /// \param position The cursor's new position in screen
    void setPosition(sf::Vector2f position) {
        _cursorView.setPosition(position);
    }

private:
    ///
    /// \brief The tile texture for the board
    ///
    sf::Texture _cursorTexture;

    ///
    /// \brief The cursor representatives
    ///
    TileView _cursorView;

    ///
    /// \brief The tiles' vertex to draw
    ///
    std::vector<sf::Vertex> _vertex;
};

#endif // __CURSORVIEW_H_
