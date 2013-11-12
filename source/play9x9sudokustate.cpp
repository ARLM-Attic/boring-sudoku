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
/// \brief The tile in tilemap that is transparent (to draw the board mask)
///
#define SUDOKU_BOARD_TRANSPARENT_TILE   11

///
/// \brief No of tiles in the Sudoku board
///
#define SUDOKU_BOARD_TILE_SIZE      81

///
/// \brief No of column in the Sudoku board
///
#define SUDOKU_BOARD_COLUMN_SIZE    9

///
/// \brief The sudoku board screen size
///
#define SUDOKU_BOARD_SCREEN_SIZE    sf::Vector2f(320, 320)

///
/// \brief No of tile in the keypad
///
#define KEYPAD_TILE_SIZE            10 // 9 numbers + 1 delete key
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

///
/// \brief The keypad value for delete button
///
#define KEYPAD_DELETE_TILE          10

//-----------------------------------------------------------------------------

Play9x9SudokuState::Play9x9SudokuState(GameManager *manager) :
        _manager(manager),
        
        // Create Sudoku board, and its views
        _sudokuBoard(SUDOKU_BOARD_TILE_SIZE, SUDOKU_BOARD_COLUMN_SIZE),
        _sudokuUserBoard(&_sudokuBoard, SUDOKU_BOARD_TRANSPARENT_TILE),
        _sudokuPuzzleView(&_sudokuBoard,
                          "artwork/sudoku-numbertiles-24px-faded.png",
                          SUDOKU_BOARD_SCREEN_SIZE),
        _sudokuBoardView(&_sudokuUserBoard,
                          "artwork/sudoku-numbertiles-24px.png",
                          SUDOKU_BOARD_SCREEN_SIZE),

        // Create Sudoku board's cursor
        _sudokuBoardCursorController(&_sudokuUserBoard,
                                     &_sudokuBoardView, 
                                     &_sudokuBoardCursorView),
        
        // Create keypad board, and its view
        _keypad(KEYPAD_TILE_SIZE, KEYPAD_COLUMN_SIZE),
        _keypadView(&_keypad, 
                    "artwork/sudoku-numbertiles-24px.png",
                    KEYPAD_SCREEN_SIZE, 
                    KEYPAD_SCREEN_OFFSET),

        // Create keypad's cursor
        _keypadCursorView(),
        _keypadCursorController(&_keypad, &_keypadView, &_keypadCursorView)
{
    // Load background texture
    _backgroundTexture.loadFromFile("artwork/sudoku-background.png");

    // Show the sudoku board
    _sudokuPuzzleView.show();
    _sudokuBoardView.show();

    // Show the cursor of the board
    _sudokuBoardCursorView.show();
    
    // Register sudoku board's 'select' event handler
    _sudokuBoardCursorController.registerObserver(this);

    // Register keypad's 'select' event handler
    _keypadCursorController.registerObserver(this);

    _controller = &_sudokuBoardCursorController;
    _view       = this;

    createSudokuPuzzle();
}

void Play9x9SudokuState::pause() {
    // TODO: Create paused / option screen
}

void Play9x9SudokuState::tileSelected(AbstractController *controller, 
                                      sf::Vector2i        tilePos) {
    if (controller == &_sudokuBoardCursorController) {
        _sudokuBoardCursorPos = tilePos;

        createKeypad();
        _keypadView.show();
        _keypadCursorView.show();

        _controller = &_keypadCursorController;
    } else {
        _keypadCursorPos = tilePos;

        // Sudoku tile is selected, and the number is selected as well
        int selectedNo = _keypad.value(_keypadCursorPos.y, _keypadCursorPos.x);
        if (selectedNo == KEYPAD_DELETE_TILE) {
            _sudokuUserBoard.setValue(0, 
                _sudokuBoardCursorPos.y, _sudokuBoardCursorPos.x);
        } else {
            _sudokuUserBoard.setValue(selectedNo,
                _sudokuBoardCursorPos.y, _sudokuBoardCursorPos.x);
        }

        _keypadView.hide();
        _keypadCursorView.hide();
        _controller = &_sudokuBoardCursorController;
    }
}

void Play9x9SudokuState::update(sf::Time elapsedTime) {
    _sudokuBoardCursorView.update(elapsedTime);
    _sudokuPuzzleView.update(elapsedTime);
    _sudokuBoardView.update(elapsedTime);

    _keypadView.update(elapsedTime);
    _keypadCursorView.update(elapsedTime);
}

void Play9x9SudokuState::draw(sf::RenderWindow *win) {
    // Draw background sprite
    sf::Sprite backgroundSprite(_backgroundTexture);
    win->draw(backgroundSprite);

    // Draw cursor sprite
    _sudokuBoardCursorView.draw(win);

    // Draw the Sudoku board
    _sudokuPuzzleView.draw(win);
    _sudokuBoardView.draw(win);

    // Draw keypad cursor
    _keypadCursorView.draw(win);
    
    // Draw cursor
    _keypadView.draw(win);
}

void Play9x9SudokuState::createKeypad() {
    _keypad.setValue(1, 0, 0);
    _keypad.setValue(2, 0, 1);
    _keypad.setValue(3, 0, 2);
    _keypad.setValue(4, 1, 0);
    _keypad.setValue(5, 1, 1);
    _keypad.setValue(6, 1, 2);
    _keypad.setValue(7, 2, 0);
    _keypad.setValue(8, 2, 1);
    _keypad.setValue(9, 2, 2);
    _keypad.setValue(KEYPAD_DELETE_TILE, 3, 0);
}

void Play9x9SudokuState::createSudokuPuzzle() {
    // |-----------------|-----------------|-----------------|
    // |  7  |     |  1  |     |     |  2  |     |     |  9  |
    // |     |     |     |  1  |     |     |  2  |     |     |
    // |  3  |     |     |     |  4  |     |     |  5  |     |
    // |-----------------|-----------------|-----------------|
    // |     |  3  |     |     |     |  4  |     |     |  5  |
    // |     |     |     |     |  7  |     |     |     |     |
    // |  5  |     |     |  6  |     |     |     |  7  |     |
    // |-----------------|-----------------|-----------------|
    // |     |  5  |     |     |  6  |     |     |     |  7  |
    // |     |     |  8  |     |     |  9  |     |     |     |
    // |  4  |     |     |  8  |     |     |  9  |     |  3  |
    // |-----------------|-----------------|-----------------|

    _sudokuBoard.setValue( 7, 0, 0);
    _sudokuBoard.setValue( 1, 0, 2);
    _sudokuBoard.setValue( 2, 0, 5);
    _sudokuBoard.setValue( 9, 0, 8);
    _sudokuBoard.setValue( 1, 1, 3);
    _sudokuBoard.setValue( 2, 1, 6);
    _sudokuBoard.setValue( 3, 2, 0);
    _sudokuBoard.setValue( 4, 2, 4);
    _sudokuBoard.setValue( 5, 2, 7);
    _sudokuBoard.setValue( 3, 3, 1);
    _sudokuBoard.setValue( 4, 3, 5);
    _sudokuBoard.setValue( 5, 3, 7);
    _sudokuBoard.setValue( 7, 4, 4);
    _sudokuBoard.setValue( 5, 5, 0);
    _sudokuBoard.setValue( 6, 5, 3);
    _sudokuBoard.setValue( 7, 5, 7);
    _sudokuBoard.setValue( 5, 6, 1);
    _sudokuBoard.setValue( 6, 6, 4);
    _sudokuBoard.setValue( 7, 6, 7);
    _sudokuBoard.setValue( 8, 7, 2);
    _sudokuBoard.setValue( 9, 7, 5);
    _sudokuBoard.setValue( 4, 8, 0);
    _sudokuBoard.setValue( 8, 8, 3);
    _sudokuBoard.setValue( 9, 8, 6);
    _sudokuBoard.setValue( 3, 8, 8);

    std::vector<bool> boardMask;
    for (int row = 0; row < _sudokuBoard.rowSize(); row++) {
        for (int col = 0; col < _sudokuBoard.columnSize(); col++) {
            if (_sudokuBoard.value(row, col) > 0) {
                boardMask.push_back(true);
            } else {
                boardMask.push_back(false);
            }
        }
    }

    _sudokuUserBoard.setModelMask(boardMask);
}
