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

#include "gamemanager.h"
#include "pausemenustate.h"

//-----------------------------------------------------------------------------
///
/// \brief The column size of the pausemenu display
///
#define PAUSEMENU_COLUMN_SIZE    1

///
/// \brief The pausemenu tile size
///
#define PAUSEMENU_TILESIZE       sf::Vector2u(240, 60)

///
/// \brief The pausemenu displayed size
///
#define PAUSEMENU_SCREENSIZE     sf::Vector2f(480, 320)

//-----------------------------------------------------------------------------
PauseMenuState::PauseMenuState() : 
    _currentPauseMenu(PAUSEMENU_START) 
{
    _backgroundTexture.loadFromFile("artwork/sudoku-menu-background.png");

    // Set menu item model
    for (unsigned int i = static_cast<int>(PAUSEMENU_START); 
                      i < static_cast<int>(PAUSEMENU_END); 
                      i++) {
        // The menu tilemap has 2 different values for each menu
        _pausemenuModel.push_back(i * 2);
    }

    _pausemenuModelAdapter = 
        BoardModelAdapter(&_pausemenuModel, PAUSEMENU_COLUMN_SIZE);

    _pausemenuLayout =
        MenuLayout(&_pausemenuModelAdapter, PAUSEMENU_TILESIZE, PAUSEMENU_SCREENSIZE);

    _pausemenuView =
        BoardView(&_pausemenuModelAdapter, &_pausemenuLayout, "artwork/sudoku-pausemenu.png");
    _pausemenuView.show();
}

PauseMenuState::~PauseMenuState() {
}

void PauseMenuState::processKeypressEvent(enum _keys key) {
    int position = static_cast<int> (_currentPauseMenu);

    switch(key) {
    case KEY_UP:
    case KEY_LEFT: {
        position--;

        if (position < static_cast<int>(PAUSEMENU_START)) {
            // _currentPauseMenu is outside the main menu. Set it back to the 
            // end of the menu
            position = static_cast<int>(PAUSEMENU_END) - 1;
        }
        break;
    }

    case KEY_DOWN:
    case KEY_RIGHT: {
        position++;

        if (position == static_cast<int>(PAUSEMENU_END)) {
            // _currentPauseMenu is outside the main menu. Set it back to the 
            // beginning of the menu
            position = static_cast<int>(PAUSEMENU_START);
        }
        break;
    }

    case KEY_SELECT: {
        switch (_currentPauseMenu) {
        case PAUSEMENU_NEWGAME:
            GameManager_popGameState();
            GameManager_popGameState();
            // fall through
        case PAUSEMENU_CONTINUE:
            GameManager_popGameState();
            break;
        case PAUSEMENU_QUIT:
            GameManager_stop();
            break;
        default:
            break;
        }
        break;
    }
    }

    _currentPauseMenu = static_cast<_pauseMenu>(position);
}

void PauseMenuState::update(sf::Time elapsedTime) {
    // Update the menu
    for (unsigned int i = static_cast<int>(PAUSEMENU_START); 
                      i < static_cast<int>(PAUSEMENU_END); 
                      i++) {
        // Each menu item in this tilemap has 2 entry. One for normal, and the
        // other for the highlighted
        if (i != static_cast<int> (_currentPauseMenu)) {
            _pausemenuModel[i] = (i * 2);
        } else {
            _pausemenuModel[i] = (i * 2) + 1;
        }
    }

    _pausemenuView.update(elapsedTime);
}

void PauseMenuState::draw(sf::RenderWindow *win) {
    sf::Sprite background(_backgroundTexture);
    win->draw(background);

    _pausemenuView.draw(win);
}
