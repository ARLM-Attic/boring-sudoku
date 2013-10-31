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
#if 0
#include "play9x9sudokustate.h"

//-----------------------------------------------------------------------------

// No of tiles that are available in a column
#define SUDOKU_NO_TILE_IN_COLUMN   9

// No of tiles that are available in a row
#define SUDOKU_NO_TILE_IN_ROW      9

// Number of tiles that are available in 9x9 Sudoku game
#define SUDOKU_9X9_TILE_LEN  (SUDOKU_NO_TILE_IN_COLUMN * SUDOKU_NO_TILE_IN_ROW)

// The Sudoku tile size in pixel
#define SUDOKU_TILE_SIZE     sf::Vector2u(24, 24)

// The screen size (in pixel) that's occupied by the sudoku board
#define SUDOKU_SCREEN_SIZE   sf::Vector2f(320.f, 320.f)

// The cursor size in pixel
#define SUDOKU_CURSOR_SIZE   sf::Vector2u(36, 36)

//-----------------------------------------------------------------------------

Play9x9SudokuState::Play9x9SudokuState(GameManager *manager) :
    _manager(manager),

    // Setup the board
    _sudokuBoard(SUDOKU_9X9_TILE_LEN),
    _sudokuBoardTexture(),
    _sudokuBoardView(&_sudokuBoard, 
                     SudokuBoardView::SUDOKUBOARD_SIZE_9X9, 
                     &_sudokuBoardTexture, 
                     SUDOKU_TILE_SIZE,
                     SUDOKU_SCREEN_SIZE),
    
    // Setup the cursor
    _cursorPos(0, 0),
    _cursorTexture(),
    _cursorView(&_cursorTexture, SUDOKU_CURSOR_SIZE)
{
    // Load background texture
    _backgroundTexture.loadFromFile("artwork/sudoku-background.png");

    // Load the Sudoku number tiles
    _sudokuBoardTexture.loadFromFile("artwork/sudoku-numbertiles-24px.png");

    // Load cursor texture
    _cursorTexture.loadFromFile("artwork/sudoku-cursor-36px.png");
}

void Play9x9SudokuState::pause() {
    // TODO: Create paused / option screen
}

void Play9x9SudokuState::up() {
    if (_cursorPos.y > 0) {
        _cursorPos.y--;
    } else {
        _cursorPos.y = (SUDOKU_NO_TILE_IN_ROW - 1);
    }
}

void Play9x9SudokuState::down() {
    if (_cursorPos.y < (SUDOKU_NO_TILE_IN_ROW - 1)) {
        _cursorPos.y++;
    } else {
        _cursorPos.y = 0;
    }
}

void Play9x9SudokuState::left() {
    if (_cursorPos.x > 0) {
        _cursorPos.x--;
    } else {
        _cursorPos.x = (SUDOKU_NO_TILE_IN_COLUMN - 1);
    }
}
 
void Play9x9SudokuState::right() {
    if (_cursorPos.x < (SUDOKU_NO_TILE_IN_COLUMN - 1)) {
        _cursorPos.x++;
    } else {
        _cursorPos.x = 0;
    }
 }

void Play9x9SudokuState::select() {
}
 
void Play9x9SudokuState::mouseMove(int x, int y) {
}

void Play9x9SudokuState::update(sf::Time elapsedTime) {
    // Update the cursor
    sf::Vector2f cursorPositionInScreen = 
        _sudokuBoardView.getTilePosition(_cursorPos.y, _cursorPos.x);
    _cursorView.setPosition(cursorPositionInScreen);
    _cursorView.update(elapsedTime);

    _sudokuBoardView.update(elapsedTime);
}

void Play9x9SudokuState::draw(sf::RenderWindow *win) {
    // Draw background sprite
    sf::Sprite backgroundSprite(_backgroundTexture);
    win->draw(backgroundSprite);

    // Draw cursor sprite
    std::vector<sf::Vertex> cursorSprite(_cursorView.begin(), 
                                         _cursorView.end()
    );
    win->draw(&cursorSprite[0], 
              cursorSprite.size(), 
              sf::Quads, 
              &_cursorTexture);

    // Draw the Sudoku board
    std::vector<sf::Vertex> boardSprite(_sudokuBoardView.begin(),
                                        _sudokuBoardView.end()
    );
    win->draw(&boardSprite[0], 
              boardSprite.size(), 
              sf::Quads, 
              &_sudokuBoardTexture);
}

#endif
