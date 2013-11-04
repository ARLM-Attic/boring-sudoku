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

#include "play9x9sudokustate.h"

///
/// \brief No of tiles in the Sudoku board
///
#define SUDOKU_BOARD_TILE_SIZE      81

///
/// \brief The sudoku board screen size
///
#define SUDOKU_BOARD_SCREEN_SIZE    sf::Vector2f(320, 320)

///
/// \brief The column size of the keypad (in tiles, not pixel)
///
#define KEYPAD_COLUMN_SIZE          3

///
/// \brief The keypad screen size
///
#define KEYPAD_SCREEN_SIZE          sf::Vector2f(160, 160)

///
/// \brief The keypad screen offset
///
#define KEYPAD_SCREEN_OFFSET        sf::Vector2f(320, 16)

//-----------------------------------------------------------------------------

Play9x9SudokuState::Play9x9SudokuState(GameManager *manager) :
        _manager(manager),
        _sudokuBoardCursorPos(sf::Vector2i(0, 0)),
        _keypadView(NULL),
        _keypadCursorView(NULL),
        _keypadCursorController(NULL)
{
    // Load background texture
    _backgroundTexture.loadFromFile("artwork/sudoku-background.png");

    // Create the sudoku board model
    _sudokuBoard.resize(SUDOKU_BOARD_TILE_SIZE, 0);

    // Connect the sudoku board model into the view
    _sudokuBoardView = 
        new SudokuBoardView(SudokuBoardView::SUDOKUBOARD_SIZE_9X9, 
                            &_sudokuBoard, 
                            SUDOKU_BOARD_SCREEN_SIZE
        );

    // Connect the sudoku board cursor to the board's view
    _sudokuBoardCursorView = new CursorView();
    _sudokuBoardCursorController = 
        new CursorController(&_sudokuBoardCursorPos, 
                             _sudokuBoardCursorView, 
                             _sudokuBoardView
        );


    _controller = this;
    _view       = this;
}

Play9x9SudokuState::~Play9x9SudokuState() {
    // In case of emergency shutdown, release the resources for keypad
    if (_keypadCursorController != NULL) {
        delete _keypadCursorController;
    }

    if (_keypadCursorView != NULL) {
        delete _keypadCursorView;
    }

    if (_keypadView != NULL) {
        delete _keypadView;
    }

    delete _sudokuBoardCursorController;
    delete _sudokuBoardCursorView;
    delete _sudokuBoardView;
}

void Play9x9SudokuState::pause() {
    // TODO: Create paused / option screen
}

void Play9x9SudokuState::up() {
    if (_keypadCursorController == NULL) {
        _sudokuBoardCursorController->up();
    } else {
        _keypadCursorController->up();
    }
}

void Play9x9SudokuState::down() {
    if (_keypadCursorController == NULL) {
        _sudokuBoardCursorController->down();
    } else {
        _keypadCursorController->down();
    }
}

void Play9x9SudokuState::left() {
    if (_keypadCursorController == NULL) {
        _sudokuBoardCursorController->left();
    } else {
        _keypadCursorController->left();
    }
}
 
void Play9x9SudokuState::right() {
    if (_keypadCursorController == NULL) {
        _sudokuBoardCursorController->right();
    } else {
        _keypadCursorController->right();
    }
}

void Play9x9SudokuState::select() {
    if (_keypadCursorController == NULL) {
        // Sudoku tile is selected but the no haven't selected yet
        // Create the keypad model
        _keypad.resize(10);
        for (unsigned int i = 0; i < _keypad.size(); i++) {
            _keypad[i] = (i + 1);
        }

        // Connect the keypad model into the view
        _keypadView = new BoardView(KEYPAD_COLUMN_SIZE, 
                                    &_keypad, 
                                    KEYPAD_SCREEN_SIZE,
                                    KEYPAD_SCREEN_OFFSET);

        // Connect the keypad cursor to the keypad's view
        _keypadCursorPos = sf::Vector2i(0, 0);
        _keypadCursorView = new CursorView();
        _keypadCursorController = new CursorController(&_keypadCursorPos, 
                                                       _keypadCursorView, 
                                                       _keypadView);
    } else {
        // Sudoku tile is selected, and the number is selected as well
        int *selectedTile = &_sudokuBoard[
            (_sudokuBoardCursorPos.y * _sudokuBoardView->columnSize()) + 
            _sudokuBoardCursorPos.x
        ];

        int *selectedNo = &_keypad[
            (_keypadCursorPos.y * _keypadView->columnSize()) + 
            _keypadCursorPos.x
        ];

        // Copy the selected no into the selected tile
        if (*selectedNo == _keypad.back()) {
            // If user select the 'delete' key (which always be inserted as the
            // last tile of keypad), replace the sudoku board value with 0
            *selectedTile = 0;
        } else {
            *selectedTile = *selectedNo;
        }

        // Remove the keypad resources
        _keypad.clear();
        delete _keypadCursorController; _keypadCursorController = NULL;
        delete _keypadCursorView;       _keypadCursorView = NULL;
        delete _keypadView;             _keypadView = NULL;
    }
}
 
void Play9x9SudokuState::mouseMove(int x, int y) {
}

void Play9x9SudokuState::update(sf::Time elapsedTime) {
    _sudokuBoardCursorView->update(elapsedTime);
    _sudokuBoardView->update(elapsedTime);

    if (_keypadView != NULL) {
        _keypadView->update(elapsedTime);
    }

    if (_keypadCursorView != NULL) {
        _keypadCursorView->update(elapsedTime);
    }
}

void Play9x9SudokuState::draw(sf::RenderWindow *win) {
    // Draw background sprite
    sf::Sprite backgroundSprite(_backgroundTexture);
    win->draw(backgroundSprite);

    // Draw cursor sprite
    _sudokuBoardCursorView->draw(win);

    // Draw the Sudoku board
    _sudokuBoardView->draw(win);

    // Draw keypad cursor
    if (_keypadCursorView != NULL) {
        _keypadCursorView->draw(win);
    }

    // Draw cursor
    if (_keypadView != NULL) {
        _keypadView->draw(win);
    }
}
