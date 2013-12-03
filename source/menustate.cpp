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
#include "menustate.h"
#include "submenustate.h"

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
MenuState::MenuState() : 
    _currentMainMenu(MENU_START) 
{
    _backgroundTexture.loadFromFile("artwork/sudoku-menu-background.png");

    // Set menu item model
    for (unsigned int i = static_cast<int>(MENU_START); 
                      i < static_cast<int>(MENU_END); 
                      i++) {
        // The menu tilemap has 2 different values for each menu
        _menuModel.push_back(i * 2);
    }

    _menuModelAdapter = 
        BoardModelAdapter(&_menuModel, MENU_COLUMN_SIZE);

    _menuLayout =
        MenuLayout(&_menuModelAdapter, MENU_TILESIZE, MENU_SCREENSIZE);

    _menuView =
        BoardView(&_menuModelAdapter, &_menuLayout, "artwork/sudoku-menu.png");
    _menuView.show();
}

MenuState::~MenuState() {
}

void MenuState::processKeypressEvent(enum _keys key) {
    int position = static_cast<int> (_currentMainMenu);

    switch(key) {
    case KEY_UP:
    case KEY_LEFT: {
        position--;

        if (position < static_cast<int>(MENU_START)) {
            // _currentMainMenu is outside the main menu. Set it back to the 
            // end of the menu
            position = static_cast<int>(MENU_END) - 1;
        }
        break;
    }

    case KEY_DOWN:
    case KEY_RIGHT: {
        position++;

        if (position == static_cast<int>(MENU_END)) {
            // _currentMainMenu is outside the main menu. Set it back to the 
            // beginning of the menu
            position = static_cast<int>(MENU_START);
        }
        break;
    }

    case KEY_SELECT: {
        switch (_currentMainMenu) {
        case MenuState::MENU_PLAY:
            GameManager_pushGameState(new SubMenuState());
            break;
        case MenuState::MENU_HELP:
            break;
        case MenuState::MENU_QUIT:
            GameManager_stop();
            break;
        default:
            break;
        }
        break;
    }
    }

    _currentMainMenu = static_cast<_mainMenu>(position);
}

void MenuState::update(sf::Time elapsedTime) {
    // Update the menu
    for (unsigned int i = static_cast<int>(MENU_START); 
                      i < static_cast<int>(MENU_END); 
                      i++) {
        // Each menu item in this tilemap has 2 entry. One for normal, and the
        // other for the highlighted
        if (i != static_cast<int> (_currentMainMenu)) {
            _menuModel[i] = (i * 2);
        } else {
            _menuModel[i] = (i * 2) + 1;
        }
    }

    _menuView.update(elapsedTime);
}

void MenuState::draw(sf::RenderWindow *win) {
    sf::Sprite background(_backgroundTexture);
    win->draw(background);

    _menuView.draw(win);
}
