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

#define SUDOKU_BOARD_SCREEN_SIZE    sf::Vector2f(320, 320)

//-----------------------------------------------------------------------------

Play9x9SudokuState::Play9x9SudokuState(GameManager *manager) :
        _manager(manager),
        _sudokuBoardCursorPos(sf::Vector2i(0, 0))
{
    // Load background texture
    _backgroundTexture.loadFromFile("artwork/sudoku-background.png");

    // Create the sudoku board model
    _sudokuBoard.resize(81, 0);

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
    delete _sudokuBoardCursorView;
    delete _sudokuBoardView;
}

void Play9x9SudokuState::pause() {
    // TODO: Create paused / option screen
}

void Play9x9SudokuState::up() {
    _sudokuBoardCursorController->up();
}

void Play9x9SudokuState::down() {
    _sudokuBoardCursorController->down();
}

void Play9x9SudokuState::left() {
    _sudokuBoardCursorController->left();
}
 
void Play9x9SudokuState::right() {
    _sudokuBoardCursorController->right();
}

void Play9x9SudokuState::select() {
}
 
void Play9x9SudokuState::mouseMove(int x, int y) {
}

void Play9x9SudokuState::update(sf::Time elapsedTime) {
    _sudokuBoardCursorView->update(elapsedTime);
    _sudokuBoardView->update(elapsedTime);
}

void Play9x9SudokuState::draw(sf::RenderWindow *win) {
    // Draw background sprite
    sf::Sprite backgroundSprite(_backgroundTexture);
    win->draw(backgroundSprite);

    // Draw cursor sprite
    _sudokuBoardCursorView->draw(win);

    // Draw the Sudoku board
    _sudokuBoardView->draw(win);
}
