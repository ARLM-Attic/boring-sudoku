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

CursorController::CursorController(BoardModelAdapter *boardModelAdapter,
                                   BoardLayout       *boardLayout,
                                   sf::Vector2u      *cursorModel,
                                   CursorView        *cursorView) :
    _boardModelAdapter(boardModelAdapter),
    _boardLayout(boardLayout),
    _cursorModel(cursorModel),
    _cursorView(cursorView) 
{
    if (boardModelAdapter == NULL) {
        return;
    }
    
    updateCursorView();
}

void CursorController::processKeypressEvent(enum _keys key) {
    switch (key) {
    case KEY_UP: {
        moveCursorUp();
        break;
    }
    
    case KEY_DOWN: {
        moveCursorDown();
        break;
    }
    
    case KEY_LEFT: {
        moveCursorLeft();
        break;
    }
    
    case KEY_RIGHT: {
        moveCursorRight();
        break;
    }
    
    case KEY_SELECT: {
        break;
    }

    case KEY_PAUSE: {
        break;
    }

    case KEY_DELETE: // fall through
    case KEY_1: // fall through
    case KEY_2: // fall through
    case KEY_3: // fall through
    case KEY_4: // fall through
    case KEY_5: // fall through
    case KEY_6: // fall through
    case KEY_7: // fall through
    case KEY_8: // fall through
    case KEY_9: {
        break;
    }
    
    default:
        break;
    }

    updateCursorView();
}

void CursorController::moveCursorUp() {
    do {
        if (_cursorModel->y > 0) {
            // Move to the upper row
            _cursorModel->y  -= 1;
        } else {
            // The cursor is already at the top of the row, roll to the 
            // last row
            _cursorModel->y = _boardModelAdapter->rowSize() - 1;
        }
    } while (!_boardModelAdapter->tileIsInBoard(_cursorModel->y, 
                                                _cursorModel->x));
}

void CursorController::moveCursorDown() {
    do {
        if (_cursorModel->y < (_boardModelAdapter->rowSize() - 1)) {
            // Move to the lower row
            _cursorModel->y += 1;
        } else {
            // The cursor is already at the bottom of the row, roll to the 
            // first row
            _cursorModel->y = 0;
        }
    } while (!_boardModelAdapter->tileIsInBoard(_cursorModel->y, 
                                                _cursorModel->x));
}

void CursorController::moveCursorLeft() {
    do {
        if (_cursorModel->x > 0) {
            // Move to the left column
            _cursorModel->x  -= 1;
        } else {
            // The cursor is already at the left of the column, roll to the 
            // rightest row
            _cursorModel->x = _boardModelAdapter->columnSize() - 1;
        }
    } while (!_boardModelAdapter->tileIsInBoard(_cursorModel->y, 
                                                _cursorModel->x));
}

void CursorController::moveCursorRight() {
    do {
        if (_cursorModel->x < (_boardModelAdapter->columnSize() - 1)) {
            // Move to the right column
            _cursorModel->x += 1;
        } else {
            // The cursor is already at the rightest of the column, roll to the
            // most left column
            _cursorModel->x = 0;
        }
    } while (!_boardModelAdapter->tileIsInBoard(_cursorModel->y, 
                                                _cursorModel->x));
}

void CursorController::updateCursorView() {
    sf::Vector2f cursorPos = 
        _boardLayout->tilePositionInScreen(_cursorModel->y, _cursorModel->x);
    
    _cursorView->setPosition(cursorPos);
}
