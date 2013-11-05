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
        _keypadCursorPos(sf::Vector2i(0, 0))
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
    // Show the sudoku board
    _sudokuBoardView->show();

    // Show the cursor of the board
    _sudokuBoardCursorView = new CursorView();
    _sudokuBoardCursorView->show();
    
    // Connect the sudoku board cursor to the board's view
    _sudokuBoardCursorController = 
        new CursorController(&_sudokuBoardCursorPos, 
                             _sudokuBoardCursorView, 
                             _sudokuBoardView
        );
    // Register its 'select' event handler
    _sudokuBoardCursorController->registerObserver(this);

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
    _keypadCursorView = new CursorView();
    _keypadCursorController = 
        new CursorController(&_keypadCursorPos, 
                             _keypadCursorView, 
                             _keypadView
        );
    // Register its 'select' event handler
    _keypadCursorController->registerObserver(this);

    _controller = _sudokuBoardCursorController;
    _view       = this;
}

Play9x9SudokuState::~Play9x9SudokuState() {
    delete _keypadCursorController;
    delete _keypadCursorView;
    delete _keypadView;
 
    delete _sudokuBoardCursorController;
    delete _sudokuBoardCursorView;
    delete _sudokuBoardView;
}

void Play9x9SudokuState::pause() {
    // TODO: Create paused / option screen
}

void Play9x9SudokuState::tileSelected(AbstractController *controller, 
                                      sf::Vector2i        tilePos) {
    if (controller == _sudokuBoardCursorController) {
        _keypadView->show();
        _keypadCursorView->show();
        _controller = _keypadCursorController;
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

        _keypadView->hide();
        _keypadCursorView->hide();
        _controller = _sudokuBoardCursorController;
    }
}

void Play9x9SudokuState::update(sf::Time elapsedTime) {
    _sudokuBoardCursorView->update(elapsedTime);
    _sudokuBoardView->update(elapsedTime);

    _keypadView->update(elapsedTime);
    _keypadCursorView->update(elapsedTime);
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
    _keypadCursorView->draw(win);
    
    // Draw cursor
    _keypadView->draw(win);
}
