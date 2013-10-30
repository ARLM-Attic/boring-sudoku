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
 * Provide default interface to connect the game state into the game manager
 */

#ifndef __GAMESTATEINTERFACE_H_
#define __GAMESTATEINTERFACE_H_

#include <SFML/Graphics.hpp>

class GameStateInterface {
public:
    ///
    /// \brief The pause event
    ///
    virtual void pause() = 0;

    ///
    /// \brief The resume event
    ///
    virtual void resume() = 0;

    ///
    /// \brief Check if the state is paused
    ///
    virtual bool isPaused() = 0;

    ///
    /// \brief 'Up' key is pressed event
    ///
    virtual void up() = 0;

    ///
    /// \brief 'Down' key is pressed event
    ///
    virtual void down() = 0;

    ///
    /// \brief 'Left' key is pressed event
    ///
    virtual void left() = 0;

    ///
    /// \brief 'Right' key is pressed event
    ///
    virtual void right() = 0;

    ///
    /// \brief Menu / item selected event
    ///
    virtual void select() = 0;

    ///
    /// \brief The mouse move event
    ///
    /// \param x The column of the current mouse pointer (measured from most 
    ///          left column of the window)
    /// \param y The row of the current mouse pointer (measured from most up 
    ///          row of the window)
    ///
    virtual void mouseMove(int x, int y) = 0;

    ///
    /// \brief Update the state, based on the time elapsed 
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
};

#endif // __GAMESTATEINTERFACE_H_
