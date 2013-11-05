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

#include "cursorcontroller.h"

CursorController::CursorController(
                    sf::Vector2i *cursorModel,
                    CursorView   *cursorView,
                    BoardView    *boardView) :
        _cursorModel(cursorModel),
        _cursorView(cursorView),
        _boardView(boardView) {
    sf::Vector2f cursorPos = 
        _boardView->tilePosition(_cursorModel->y, _cursorModel->x);
    _cursorView->setPosition(cursorPos);
}

void CursorController::up() {
    if (_cursorModel->y > 0) {
        _cursorModel->y--;
    } else {
        _cursorModel->y = lastRow();
    }

    sf::Vector2f cursorPos = 
        _boardView->tilePosition(_cursorModel->y, _cursorModel->x);
    _cursorView->setPosition(cursorPos);
}

void CursorController::down() {
    if (_cursorModel->y < lastRow()) {
        _cursorModel->y++;
    } else {
        _cursorModel->y = 0;
    }

    sf::Vector2f cursorPos = 
        _boardView->tilePosition(_cursorModel->y, _cursorModel->x);
    _cursorView->setPosition(cursorPos);
}

void CursorController::left() {
    if (_cursorModel->x > 0) {
        _cursorModel->x--;
    } else {
        _cursorModel->x = lastColumn();
    }

    sf::Vector2f cursorPos = 
        _boardView->tilePosition(_cursorModel->y, _cursorModel->x);
    _cursorView->setPosition(cursorPos);
}
 
void CursorController::right() {
   if (_cursorModel->x < lastColumn()) {
       _cursorModel->x++;
   } else {
       _cursorModel->x = 0;
   }

    sf::Vector2f cursorPos = 
        _boardView->tilePosition(_cursorModel->y, _cursorModel->x);
    _cursorView->setPosition(cursorPos);
}

void CursorController::select() {
    
}

int CursorController::lastRow() {
    int lastRow = (_boardView->rowSize() - 1);

    while (!_boardView->tileIsInBoard(lastRow, _cursorModel->x)) {
        lastRow--;
    }

    return lastRow;
}

int CursorController::lastColumn() {
    int lastColumn = (_boardView->columnSize() - 1);

    while (!_boardView->tileIsInBoard(_cursorModel->y, lastColumn)) {
        lastColumn--;
    }

    return lastColumn;
}
