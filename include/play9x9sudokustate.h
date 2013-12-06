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

#include <SFML/Graphics.hpp>
#include "abstractgamestate.h"
#include "boardmodeladapter.h"
#include "boardlayout.h"
#include "boardview.h"
#include "cursorcontroller.h"
#include "cursoreventobserver.h"
#include "cursorview.h"
#include "scorelayout.h"
#include "sudokuboardlayout.h"
#include "sudokugame.h"
#include "sudokuscore.h"

class Play9x9SudokuState : public AbstractGameState, public CursorEventObserver
{
public:
    explicit Play9x9SudokuState();
    virtual ~Play9x9SudokuState();

    //-------------------------------------------------------------------------
    // Abstractcontroller methods
    virtual void processKeypressEvent(enum _keys key);

    //-------------------------------------------------------------------------
    // AbstractViewer's methods
    virtual void update(sf::Time elapsedTime);
    virtual void draw(sf::RenderWindow *win);

    //-------------------------------------------------------------------------
    // CursorEventObserver's methods
    virtual void tileSelected(AbstractController       *controller, 
                              sf::Vector2i              tilePos,
                              AbstractController::_keys key);
private:
    ///
    /// \brief Create the keypad
    ///
    void createKeypad();

    ///
    /// \brief Create the Sudoku board
    ///
    void createSudokuBoard();

    //-------------------------------------------------------------------------
    ///
    /// \brief The sudoku game
    ///
    SudokuGame _sudokuGame;

    ///
    /// \brief The sudoku scoring mechanism, and its display
    ///
    SudokuScore *_sudokuScore;

    //-------------------------------------------------------------------------
    ///
    /// \brief The background texture
    ///
    sf::Texture _backgroundTexture;

    //-------------------------------------------------------------------------
    ///
    /// \brief The sudoku model
    ///
    std::vector<unsigned int> _sudokuModel;

    ///
    /// \brief sudoku model mask
    ///
    std::vector<bool> _sudokuModelMask;

    ///
    /// \brief The sudoku model adapter
    ///
    BoardModelAdapter _sudokuModelAdapter;

    ///
    /// \brief The sudoku layout
    ///
    SudokuBoardLayout _sudokuLayout;

    ///
    /// \brief The sudoku view (the puzzle)
    ///
    BoardView _sudokuView;

    ///
    /// \brief The sudoku view (user modifiable tiles)
    ///
    BoardView _sudokuUserView;

    //-------------------------------------------------------------------------
    ///
    /// \brief The sudoku's board cursor model
    ///
    sf::Vector2u    _sudokuCursorModel;

    ///
    /// \brief The sudoku board's cursor controller
    ///
    CursorController _sudokuCursorController;

    ///
    /// \brief The sudoku board's cursor view
    ///
    CursorView _sudokuCursorView;

    //-------------------------------------------------------------------------
    ///
    /// \brief The keypad model
    ///
    std::vector<unsigned int> _keypadModel;

    ///
    /// \brief The keypad model adapter
    ///
    BoardModelAdapter _keypadModelAdapter;

    ///
    /// \brief The keypad layout
    ///
    BoardLayout _keypadLayout;

    ///
    /// \brief The keypad view
    ///
    BoardView _keypadView;

    //-------------------------------------------------------------------------
    ///
    /// \brief The sudoku's keypad cursor model
    ///
    sf::Vector2u    _keypadCursorModel;

    ///
    /// \brief The sudoku keypad's cursor controller
    ///
    CursorController _keypadCursorController;

    ///
    /// \brief The sudoku keypad's cursor view
    ///
    CursorView _keypadCursorView;

    //-------------------------------------------------------------------------
    ///
    /// \brief The current cursor controller points to the cursor controller 
    ///        that will process the current user input
    ///
    CursorController *_currentCursorController;
};

#endif // __PLAY9X9SUDOKUSTATE_H_
