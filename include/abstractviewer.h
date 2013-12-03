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
 * Provide base class to draw into the screen
 */

#ifndef __ABSTRACTVIEWER_H_
#define __ABSTRACTVIEWER_H_

#include <SFML/Graphics.hpp>

class AbstractViewer {
public:
    ///
    /// \brief Update the graphic, based on the time elapsed 
    ///
    /// \param elapsedTime The time that has elapsed
    ///
    virtual void update(sf::Time elapsedTime) = 0;

    ///
    /// \brief Draw the game state
    ///
    /// \param win The handler to the window
    ///
    virtual void draw(sf::RenderWindow *win) = 0;

    ///
    /// \brief Show the view
    ///
    void show() {
        _isShowed = true;
    }

    ///
    /// \brief Hide the view
    ///
    void hide() {
        _isShowed = false;
    }

    ///
    /// \brief The viewer's desctructor
    ///
    virtual ~AbstractViewer() { }

protected:
    ///
    /// \brief Flag to indicate that this view should be drawn in the screen
    ///
    /// This flag should be polled in the draw() or update() method
    ///
    bool _isShowed;
};

#endif // __VIEWABLEINTERFACE_H_
