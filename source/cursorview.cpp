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

#include "cursorview.h"

CursorView::CursorView(sf::Vector2u       cursorSize,
                        const std::string &cursorFilename) {
    // Load cursor texture
    _cursorTexture.loadFromFile(cursorFilename);

    // Setup the cursor tile. Assuming that the tilemap has only single tile
    // for the cursor only.
    _cursorTile = TileView(cursorSize, cursorSize);
}

void CursorView::update(sf::Time elapsedTime) {
    _cursorTile.update(elapsedTime);

    _vertex.clear();
    _vertex.insert( _vertex.end(), 
                    _cursorTile.begin(), 
                    _cursorTile.end()
    );
}

void CursorView::draw(sf::RenderWindow *win) {
    // Don't draw if it's not supposed to be shown
    if (!_isShowed) {
        return;
    }

    win->draw(&_vertex[0], 
              _vertex.size(), 
              sf::Quads, 
              &_cursorTexture);
}

void CursorView::setPosition(sf::Vector2f position) {
    _cursorTile.setPosition(position);
}
