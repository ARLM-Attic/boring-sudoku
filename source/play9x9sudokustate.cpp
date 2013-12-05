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

#include "gamemanager.h"
#include "pausemenustate.h"
#include "play9x9sudokustate.h"

//-----------------------------------------------------------------------------
///
/// \brief No of column in the Sudoku board
///
#define SUDOKU_BOARD_COLUMN_SIZE    9

///
/// \brief The sudoku tile size
///
#define SUDOKU_TILESIZE             sf::Vector2u(24, 24)

///
/// \brief The sudoku board screen size
///
#define SUDOKU_BOARD_SCREEN_SIZE    sf::Vector2f(320, 320)

//-----------------------------------------------------------------------------
///
/// \brief The sudoku board's cursor size
///
#define SUDOKU_CURSOR_SIZE          sf::Vector2u(36, 36)


//-----------------------------------------------------------------------------
///
/// \brief The column size of the keypad (in tiles, not pixel)
///
#define KEYPAD_COLUMN_SIZE          3

///
/// \brief The keypad tile size
///
#define KEYPAD_TILESIZE             sf::Vector2u(24, 24)

///
/// \brief The keypad screen size
///
#define KEYPAD_SCREEN_SIZE          sf::Vector2f(160, 160)

///
/// \brief The keypad screen offset
///
#define KEYPAD_SCREEN_OFFSET        sf::Vector2f(320, 16)

//-----------------------------------------------------------------------------
///
/// \brief The column size of the score display
///
#define SCORE_COLUMN_SIZE           5

///
/// \brief The score display tilesize
///
#define SCORE_TILESIZE              sf::Vector2u(24, 24)

///
/// \brief The screen size for the score display
///
#define SCORE_SCREEN_SIZE           sf::Vector2f(160, 160)

///
/// \brief The score display screen offset
///
#define SCORE_SCREEN_OFFSET         sf::Vector2f(326, 274)

//-----------------------------------------------------------------------------
///
/// \brief The number tilemap that's used in this game store no 0 symbol at pos 
///        #11
///
#define TILEMAP_SYMBOL_0      10

///
/// \brief The number tilemap that's used in this game store delete symbol at 
///        pos #12
///
#define TILEMAP_SYMBOL_DELETE 11

//-----------------------------------------------------------------------------
///
/// \brief The score display length (in digit)
///
#define SCORE_DIGIT_LENGTH    5

//-----------------------------------------------------------------------------
Play9x9SudokuState::Play9x9SudokuState() {
    // Load background texture
    _backgroundTexture.loadFromFile("artwork/sudoku-game-background.png");

    //-------------------------------------------------------------------------
    // Create Sudoku puzzle
    createSudokuBoard();

    _sudokuModelAdapter = 
        BoardModelAdapter(&_sudokuModel, 
                          SUDOKU_BOARD_COLUMN_SIZE
        );
    _sudokuModelAdapter.setModelMask(&_sudokuModelMask);

    _sudokuLayout = 
        SudokuBoardLayout(&_sudokuModelAdapter, 
                          SUDOKU_TILESIZE, 
                          SUDOKU_BOARD_SCREEN_SIZE
        );

    _sudokuView =
        BoardView(&_sudokuModelAdapter, 
                  &_sudokuLayout, 
                  "artwork/sudoku-numbertiles-black-24px.png"
        );
    _sudokuView.show();

    _sudokuUserView = 
        BoardView(&_sudokuModelAdapter, 
                  &_sudokuLayout, 
                  "artwork/sudoku-numbertiles-24px.png"
        );
    _sudokuUserView.show();

    //-------------------------------------------------------------------------
    // Create board's cursor
    _sudokuCursorModel = sf::Vector2u(0, 0);

    _sudokuCursorView  = 
        CursorView(SUDOKU_CURSOR_SIZE, 
                   "artwork/sudoku-cursor-36px.png"
        );
    _sudokuCursorView.show();

    _sudokuCursorController = 
        CursorController(&_sudokuModelAdapter, 
                         &_sudokuLayout, 
                         &_sudokuCursorModel,
                         &_sudokuCursorView
        );

    //-------------------------------------------------------------------------
    // Create keypad
    createKeypad();

    _keypadModelAdapter = 
        BoardModelAdapter(&_keypadModel, 
                          KEYPAD_COLUMN_SIZE
        );
    
    _keypadLayout = 
        BoardLayout(&_keypadModelAdapter, 
                     KEYPAD_TILESIZE, 
                     KEYPAD_SCREEN_SIZE, 
                     KEYPAD_SCREEN_OFFSET
        );

    _keypadView = 
        BoardView(&_keypadModelAdapter, 
                  &_keypadLayout, 
                  "artwork/sudoku-numbertiles-24px.png"
        );
    _keypadView.show();

    //-------------------------------------------------------------------------
    // Create the score display
    setScore(98201);

    _scoreModelAdapter =
        BoardModelAdapter(&_scoreModel, 
                          SCORE_COLUMN_SIZE
        );

    _scoreLayout = 
        ScoreLayout(&_scoreModelAdapter,
                    SCORE_TILESIZE,
                    SCORE_SCREEN_SIZE,
                    SCORE_SCREEN_OFFSET
        );

    _scoreView =
        BoardView(&_scoreModelAdapter,
                  &_scoreLayout,
                  "artwork/sudoku-numbertiles-24px.png"
        );
    _scoreView.show();
}

Play9x9SudokuState::~Play9x9SudokuState() {
}

void Play9x9SudokuState::processKeypressEvent(enum _keys key) {
    // Tap the KEY_PAUSE
    switch (key) {
    case AbstractController::KEY_PAUSE: {
        GameManager_pushGameState(new PauseMenuState());
        break;
    }
    }

    _sudokuCursorController.processKeypressEvent(key);
}

void Play9x9SudokuState::update(sf::Time elapsedTime) {
    _sudokuCursorView.update(elapsedTime);

    _sudokuModelAdapter.disableMask();
    _sudokuView.update(elapsedTime);

    _sudokuModelAdapter.enableMask();
    _sudokuUserView.update(elapsedTime);

    _keypadView.update(elapsedTime);

    _scoreView.update(elapsedTime);
}

void Play9x9SudokuState::draw(sf::RenderWindow *win) {
    // Draw background sprite
    sf::Sprite backgroundSprite(_backgroundTexture);
    win->draw(backgroundSprite);

    _sudokuCursorView.draw(win);
    _sudokuView.draw(win);
    _sudokuUserView.draw(win);

    _keypadView.draw(win);

    _scoreView.draw(win);
}

//-----------------------------------------------------------------------------
void Play9x9SudokuState::createKeypad() {
    // Init keypad model
    for (unsigned int i = 1; i < 10; i++) {
        _keypadModel.push_back(i);
    }

    _keypadModel.push_back(TILEMAP_SYMBOL_DELETE);
}

void Play9x9SudokuState::createSudokuBoard() {
    unsigned int suzokuPuzzle[] = {
        8, 0, 0, 3, 5, 4, 0, 9, 0,
        2, 0, 0, 6, 7, 0, 8, 0, 0,
        0, 6, 0, 8, 1, 0, 0, 3, 0,
        0, 0, 3, 9, 2, 0, 0, 0, 4,
        0, 9, 0, 0, 0, 0, 0, 2, 0,
        6, 0, 0, 0, 3, 8, 1, 0, 0,
        0, 4, 0, 0, 9, 6, 0, 5, 0,
        0, 0, 2, 0, 8, 3, 0, 0, 6,
        0, 5, 0, 7, 4, 1, 0, 0, 3
    };

    _sudokuModel.insert(_sudokuModel.begin(),
                        std::begin(suzokuPuzzle), 
                        std::end  (suzokuPuzzle)
    );

    for (unsigned int i = 0; i < _sudokuModel.size(); i++) {
        if (_sudokuModel[i] > 0) {
            _sudokuModelMask.push_back(true);
        } else {
            _sudokuModelMask.push_back(false);
        }
    }
}



void Play9x9SudokuState::setScore(unsigned int score) {
    unsigned int divider = 10;

    _scoreModel.resize(SCORE_DIGIT_LENGTH);

    for (unsigned int i = 0; i < SCORE_DIGIT_LENGTH; i++) {
        _scoreModel[(SCORE_DIGIT_LENGTH -1) - i] = score % divider;

        if (_scoreModel[(SCORE_DIGIT_LENGTH -1) - i] == 0) {
            _scoreModel[(SCORE_DIGIT_LENGTH -1) - i] = TILEMAP_SYMBOL_0;
        }
        
        score = score / divider;
    }
}
