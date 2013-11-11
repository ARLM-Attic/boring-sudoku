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

/*
 * Controller class to manage user input to move the cursor
 */
#ifndef __CURSORCONTROLLER_H_
#define __CURSORCONTROLLER_H_

#include <SFML/Graphics.hpp>

#include "abstractcontroller.h"
#include "boardmodel.h"
#include "boardview.h"
#include "cursoreventobserver.h"
#include "cursorview.h"

class CursorController : public AbstractController {
public:
    ///
    /// \brief Register the cursor model and board view to the controller
    ///
    /// \param boardModel  The board model
    /// \param boardView   The board view
    /// \param cursorView  The cursor view
    ///
    CursorController(BoardModel *boardModel,
                     BoardView  *boardView,
                     CursorView *cursorView);

    ///
    /// \brief Register the cursor event observer
    ///
    /// Since the cursor only attach to single board, only single observer 
    /// that's possible. Hence, only 1 observer that can be registered
    ///
    /// \param observer The observer for this event
    ///
    void registerObserver(CursorEventObserver *observer);

    ///
    /// \brief 'Up' key is pressed event
    ///
    virtual void up();

    ///
    /// \brief 'Down' key is pressed event
    ///
    virtual void down();

    ///
    /// \brief 'Left' key is pressed event
    ///
    virtual void left();

    ///
    /// \brief 'Right' key is pressed event
    ///
    virtual void right();

    ///
    /// \brief Menu / item selected event
    ///
    virtual void select();

private:
    ///
    /// \brief Update the cursor view (called after user event is received)
    ///
    void updateCursorView();

    ///
    /// \brief The board model
    ///
    BoardModel  *_boardModel;

    ///
    /// \brief The board view, that represents the board which the cursor 
    ///        attached to
    ///
    BoardView   *_boardView;

    ///
    /// \brief The cursor view, represents the cursor position in the screen
    ///
    CursorView  *_cursorView;

    ///
    /// \brief The cursor model, that represents the cursor position in the 
    ///        board
    ///
    sf::Vector2i _cursorModel;

    ///
    /// \brief The cursor event observer
    ///
    CursorEventObserver *_eventObserver;
};

#endif
