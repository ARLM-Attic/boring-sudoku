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
#if 0
#include <vector>

#include "cursorview.h"
#include "gamemanager.h"
#include "gamestateinterface.h"
#include "sudokuboardview.h"

class Play9x9SudokuState : public GameStateInterface {
public:
    explicit Play9x9SudokuState  (GameManager *manager);

    //-------------------------------------------------------------------------
    // These functions are needed to control the paused / option / menu screen
    void pause();
    void resume()   {
        // Not used. The paused state will be pushed into the state stack. 
        // Hence this state will always in the running state
    }

    bool isPaused() {
        // This state is always running
        return false; 
    }

    //-------------------------------------------------------------------------
    // These functions are needed to control the cursor on the board
    void up();
    void down();
    void left();
    void right();
    void select();
    void mouseMove(int x, int y);

    //-------------------------------------------------------------------------
    // This function is needed to compute the cursor position on the screen 
    // along with updating the screen background and the board's view
    void update(sf::Time elapsedTime);

    //-------------------------------------------------------------------------
    // This function is needed to draw the game
    void draw(sf::RenderWindow *win);

private:
    ///
    /// \brief The access to the game manager
    ///
    GameManager *_manager;

    //-------------------------------------------------------------------------
    ///
    /// \brief The sudoku board
    ///
    std::vector<int> _sudokuBoard;

    ///
    /// \brief The Sudoku board view
    ///
    SudokuBoardView _sudokuBoardView;

    ///
    /// \brief The Sudoku board texture (tile with numbers 1 - 9)
    ///
    sf::Texture _sudokuBoardTexture;

    //-------------------------------------------------------------------------
    ///
    /// \brief The cursor position (in term of board's row / column, not the 
    ///        screen row / column)
    ///
    sf::Vector2i _cursorPos;

    ///
    /// \brief The cursor view
    ///
    CursorView _cursorView;

    ///
    /// \brief The Sudoku cursor texture
    ///
    sf::Texture _cursorTexture;

    //-------------------------------------------------------------------------
    ///
    /// \brief The Sudoku board background texture
    ///
    sf::Texture _backgroundTexture;
};
#endif
#endif // __PLAY9X9SUDOKUSTATE_H_
