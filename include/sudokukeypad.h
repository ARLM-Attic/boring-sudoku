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
 * Display the on-screen keypad to enter the digit into the tiles
 */

#ifndef __SUDOKUKEYPAD_H_
#define __SUDOKUKEYPAD_H_

#include <SFML/Graphics.hpp>
#include "sudokutile.h"

class SudokuKeypad {
public:
    ///
    /// \brief Generate the Sudoku keypad
    ///
    /// \param tilemap      The texture for the tilemap
    /// \param tilesize     The size of the board's tile (in pixel)
    /// \param screenSize   The screen size
    /// \param screenOffset The offset from screen to be added
    ///
    explicit SudokuKeypad(sf::Texture *tilemap,
                          sf::Vector2u tileSize,
                          sf::Vector2f screenSize,
                          sf::Vector2f screenOffset = sf::Vector2f(0, 0));

    ///
    /// \brief Show the keypad
    ///
    void show();

    ///
    /// \brief Hide the keypad
    ///
    void hide();

    //-------------------------------------------------------------------------
    // Interface to get the keypad to be drawn in the screen

    ///
    /// \brief Update the keypad to be displayed
    ///
    /// \param elapsedTime The time that has elapsed since the last update
    ///
    void update(sf::Time elapsedTime);

    std::vector<sf::Vertex>::iterator begin() {
        return _vertex.begin();
    }

    std::vector<sf::Vertex>::iterator end() {
        return _vertex.end();
    }

    std::vector<sf::Vertex>::const_iterator begin() const {
        return _vertex.begin();
    }

    std::vector<sf::Vertex>::const_iterator end() const {
        return _vertex.end();
    }

private:
    ///
    /// \brief The sudoku keypad
    ///
    std::vector<SudokuTile> _sudokukeypad;

    ///
    /// \brief Flag to indicate whether the keypad should be displayed
    ///
    bool _keypadIsShowed;

    ///
    /// \brief The vertex to draw the board
    ///
    std::vector<sf::Vertex> _vertex;
};

#endif // __SUDOKUKEYPAD_H_
