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
#include "boardmodeladapter.h"
#include "boardlayout.h"
#include "cursorview.h"
#include "cursoreventobserver.h"

class CursorController : public AbstractController {
public:
    ///
    /// \brief Register the cursor model and board view to the controller
    ///
    /// \param boardModelAdapter  The board model
    /// \param boardLayout        The board layout
    /// \param cursorModel        The cursor model
    /// \param cursorView         The cursor view
    ///
    CursorController(BoardModelAdapter *boardModelAdapter = NULL,
                     BoardLayout       *boardLayout       = NULL,
                     sf::Vector2u      *cursorModel       = NULL,
                     CursorView        *cursorView        = NULL
    );

    //-------------------------------------------------------------------------
    ///
    /// \brief Process the keypress events
    ///
    virtual void processKeypressEvent(enum _keys key);

    ///
    /// \brief Register the cursor event observer
    ///
    void registerEventObserver(CursorEventObserver *observer);

    ///
    /// \brief Reset the cursor position to row #0, column #0
    ///
    void resetCursorPosition();

private:
    ///
    /// \brief Move the cursor up into the valid tile position
    ///
    void moveCursorUp();

    ///
    /// \brief Move the cursor down into the valid tile position
    ///
    void moveCursorDown();

    ///
    /// \brief Move the cursor left into the valid tile position
    ///
    void moveCursorLeft();

    ///
    /// \brief Move the cursor right into the valid tile position
    ///
    void moveCursorRight();

    ///
    /// \brief Update the cursor view (called after keypress event is received)
    ///
    void updateCursorView();

    ///
    /// \brief The board model
    ///
    BoardModelAdapter *_boardModelAdapter;

    ///
    /// \brief The board layout
    ///
    BoardLayout *_boardLayout;

    ///
    /// \brief The cursor model
    ///
    sf::Vector2u *_cursorModel;

    ///
    /// \brief The cursor view, represents the cursor position in the screen
    ///
    CursorView  *_cursorView;

    ///
    /// \brief The cursor event observer
    ///
    CursorEventObserver *_cursorEventObserver;
};

#endif
