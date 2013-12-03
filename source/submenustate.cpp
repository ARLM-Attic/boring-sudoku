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
#include "submenustate.h"
#include "play9x9sudokustate.h"

//-----------------------------------------------------------------------------
///
/// \brief The column size of the menu display
///
#define MENU_COLUMN_SIZE    1

///
/// \brief The menu tile size
///
#define MENU_TILESIZE       sf::Vector2u(240, 60)

///
/// \brief The menu displayed size
///
#define MENU_SCREENSIZE     sf::Vector2f(480, 320)

//-----------------------------------------------------------------------------
SubMenuState::SubMenuState() : 
    _currentSubMenu(SUBMENU_START) 
{
    _backgroundTexture.loadFromFile("artwork/sudoku-menu-background.png");

        // Set menu item model
    for (unsigned int i = static_cast<int>(SUBMENU_START); 
                      i < static_cast<int>(SUBMENU_END); 
                      i++) {
        // The menu tilemap has 2 different values for each menu
        _submenuModel.push_back(i * 2);
    }

    _submenuModelAdapter = 
        BoardModelAdapter(&_submenuModel, MENU_COLUMN_SIZE);

    _submenuLayout =
        MenuLayout(&_submenuModelAdapter, MENU_TILESIZE, MENU_SCREENSIZE);

    _submenuView =
        BoardView(&_submenuModelAdapter, &_submenuLayout, 
                  "artwork/sudoku-submenu.png"
        );
    _submenuView.show();
}

SubMenuState::~SubMenuState() {
}

void SubMenuState::processKeypressEvent(enum _keys key) {
    int position = static_cast<int> (_currentSubMenu);

    switch(key) {
    case KEY_UP:
    case KEY_LEFT: {
        position--;

        if (position < static_cast<int>(SUBMENU_START)) {
            // _currentMainMenu is outside the main menu. Set it back to the 
            // end of the menu
            position = static_cast<int>(SUBMENU_END) - 1;
        }
        break;
    }

    case KEY_DOWN:
    case KEY_RIGHT: {
        position++;

        if (position == static_cast<int>(SUBMENU_END)) {
            // _currentMainMenu is outside the main menu. Set it back to the 
            // beginning of the menu
            position = static_cast<int>(SUBMENU_START);
        }
        break;
    }

    case KEY_SELECT: {
        GameManager_pushGameState(new Play9x9SudokuState());
        break;
    }
    }

    _currentSubMenu = static_cast<_subMenu>(position);
}

void SubMenuState::update(sf::Time elapsedTime) {
    for (unsigned int i = static_cast<int>(SUBMENU_START); 
                      i < static_cast<int>(SUBMENU_END); 
                      i++) {
        // Each menu item in this tilemap has 2 entry. One for normal, and the
        // other for the highlighted
        if (i != static_cast<int> (_currentSubMenu)) {
            _submenuModel[i] = (i * 2);
        } else {
            _submenuModel[i] = (i * 2) + 1;
        }
    }

    _submenuView.update(elapsedTime);
}

void SubMenuState::draw(sf::RenderWindow *win) {
    sf::Sprite background(_backgroundTexture);
    win->draw(background);

    _submenuView.draw(win);
}
