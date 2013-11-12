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

#ifndef __PLAY9X9SUDOKUSTATE_H_
#define __PLAY9X9SUDOKUSTATE_H_

#include <vector>

#include "abstractgamestate.h"
#include "abstractviewer.h"

#include "boardmodel.h"
#include "boardmodelmask.h"
#include "boardview.h"

#include "cursorcontroller.h"
#include "cursoreventobserver.h"
#include "cursorview.h"

#include "gamemanager.h"

#include "sudokuboardview.h"

class Play9x9SudokuState : public AbstractGameState, 
                                  AbstractViewer, 
                                  CursorEventObserver {
public:
    explicit Play9x9SudokuState(GameManager *manager);
    virtual ~Play9x9SudokuState() { }

    //-------------------------------------------------------------------------
    // Override the AbstractGameState's methods. These functions are needed to
    // create the paused / option / menu screen
    virtual void pause();

    //-------------------------------------------------------------------------
    // Implementation of CursorEventObserver interface
    virtual void tileSelected(AbstractController *controller, 
                              sf::Vector2i        tilePos);

    //-------------------------------------------------------------------------
    // Override the AbstractViewer's method. This function is needed to compute
    // the cursor position on the screen along with updating the screen 
    // background and the board's view
    virtual void update(sf::Time elapsedTime);

    // This function is needed to draw the game
    virtual void draw(sf::RenderWindow *win);

private:
    ///
    /// \brief Create the keypad
    ///
    void createKeypad();

    ///
    /// \brief Create the Sudoku puzzle
    ///
    void createSudokuPuzzle();

    ///
    /// \brief The access to the game manager
    ///
    GameManager *_manager;

    //-------------------------------------------------------------------------
    ///
    /// \brief The sudoku board
    ///
    BoardModel _sudokuBoard;

    ///
    /// \brief The sudoku board that's editable by user
    ///
    BoardModelMask _sudokuUserBoard;

    ///
    /// \brief The view of the sudoku board puzzle (the tiles that cannot be 
    ///        updated by user)
    ///
    SudokuBoardView _sudokuPuzzleView;

    ///
    /// \brief The view of the sudoku board (the tiles that can be updated by 
    ///        user)
    ///
    SudokuBoardView _sudokuBoardView;
    
    //-------------------------------------------------------------------------
    ///
    /// \brief The cursor position for the Sudoku board
    ///
    sf::Vector2i _sudokuBoardCursorPos;

    ///
    /// \brief The cursor view of the sudoku board
    ///
    CursorView _sudokuBoardCursorView;

    ///
    /// \brief The sudoku board cursor controller
    ///
    CursorController _sudokuBoardCursorController;

    //-------------------------------------------------------------------------
    ///
    /// \brief The background texture of the game
    ///
    sf::Texture  _backgroundTexture;

    //-------------------------------------------------------------------------
    ///
    /// \brief The keypad to insert the number selection
    ///
    BoardModel _keypad;

    ///
    /// \brief The view of the keypad
    ///
    BoardView _keypadView;

    //-------------------------------------------------------------------------
    ///
    /// \brief The cursor position of the keypad
    ///
    sf::Vector2i _keypadCursorPos;

    ///
    /// \brief The cursor view of the keypad
    ///
    CursorView _keypadCursorView;

    ///
    /// \brief The sudoku board cursor controller
    ///
    CursorController _keypadCursorController;
};

#endif // __PLAY9X9SUDOKUSTATE_H_
