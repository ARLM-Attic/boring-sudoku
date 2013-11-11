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

CursorController::CursorController(BoardModel *boardModel,
                                   BoardView  *boardView,
                                   CursorView *cursorView) :
    _boardModel(boardModel),
    _boardView(boardView),
    _cursorView(cursorView),
    _cursorModel(sf::Vector2i(0, 0)) {
    
    updateCursorView();
}

void CursorController::registerObserver(CursorEventObserver *observer) {
    _eventObserver = observer;
}

void CursorController::up() {
    int rollCount = _boardModel->rowSize();

    while(rollCount > 0) {
        if (_cursorModel.y > 0) {
            // Move to the upper row
            _cursorModel.y -= 1;
        } else {
            // The cursor is already at the top of the row, roll to the last 
            // row
            _cursorModel.y = _boardModel->rowSize() - 1;
        }

        if (_boardModel->tileIsInBoard(_cursorModel.y, _cursorModel.x)) {
            // The new position is valid. Stop rolling
            break;
        }
    }

    updateCursorView();
}

void CursorController::down() {
    int rollCount = _boardModel->rowSize();

    while(rollCount > 0) {
        if (_cursorModel.y < (_boardModel->rowSize() - 1)) {
            // Move to the lower row
            _cursorModel.y += 1;
        } else {
            // The cursor is already at the bottom of the row, roll to the top
            // row
            _cursorModel.y = 0;
        }

        if (_boardModel->tileIsInBoard(_cursorModel.y, _cursorModel.x)) {
            // The new position is valid. Stop rolling
            break;
        }
    }

    updateCursorView();
}

void CursorController::left() {
    int rollCount = _boardModel->columnSize();

    while(rollCount > 0) {
        if (_cursorModel.x > 0) {
            // Move to the left column
            _cursorModel.x -= 1;
        } else {
            // The cursor is already at the most left of the column, roll to 
            // the last column
            _cursorModel.x = _boardModel->columnSize() - 1;
        }

        if (_boardModel->tileIsInBoard(_cursorModel.y, _cursorModel.x)) {
            // The new position is valid. Stop rolling
            break;
        }
    }

    updateCursorView();
}
 
void CursorController::right() {
    int rollCount = _boardModel->columnSize();

    while(rollCount > 0) {
        if (_cursorModel.x < (_boardModel->columnSize() - 1)) {
            // Move to the rigt column
            _cursorModel.x += 1;
        } else {
            // The cursor is already at the most right of the column, roll to 
            // the first column
            _cursorModel.x = 0;
        }

        if (_boardModel->tileIsInBoard(_cursorModel.y, _cursorModel.x)) {
            // The new position is valid. Stop rolling
            break;
        }
    }

    updateCursorView();
}

void CursorController::select() {
    _eventObserver->tileSelected(this, _cursorModel);
}

void CursorController::updateCursorView() {
    sf::Vector2f cursorPos = 
        _boardView->tilePositionInScreen(_cursorModel.y, _cursorModel.x);
    
    _cursorView->setPosition(cursorPos);
}
