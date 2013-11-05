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
 * Interface to bridge the cursor and its observers.
 */

#ifndef __CURSOREVENTOBSERVER_H_
#define __CURSOREVENTOBSERVER_H_

#include <SFML/Graphics.hpp>
#include "abstractcontroller.h"

class CursorEventObserver {
public:
    ///
    /// \brief Tile selected event. Triggered if the cursor has select the tile
    ///
    /// \param controller The controller, the origin of the event
    /// \param tilePos    Tile position in the board
    ///
    virtual void tileSelected(AbstractController *controller, 
                             sf::Vector2i         tilePos) = 0;
};

#endif // __CURSOREVENTOBSERVER_H_
