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
#include "gameoverstate.h"
#include "sudokuscore.h"

//-----------------------------------------------------------------------------
///
/// \brief The screen size for the score display
///
#define SCORE_SCREEN_SIZE           sf::Vector2f(160, 160)

///
/// \brief The score display screen offset
///
#define SCORE_SCREEN_OFFSET         sf::Vector2f(200, 145)

///
/// \brief The column size of the score display
///
#define SCORE_COLUMN_SIZE           5

///
/// \brief The score display tilesize
///
#define SCORE_TILESIZE              sf::Vector2u(24, 24)

///
/// \brief The score display length (in digit)
///
#define SCORE_DIGIT_LENGTH          5

//-----------------------------------------------------------------------------
GameOverState::GameOverState(unsigned int lastScore) {
    _backgroundTexture.loadFromFile("artwork/sudoku-gameover-background.png");

    // Init the score widget
    _scoreDigitModel = std::vector<unsigned int> (SCORE_DIGIT_LENGTH, 0);

    _scoreDigitModelAdapter =
        BoardModelAdapter(&this->_scoreDigitModel, 
                          SCORE_COLUMN_SIZE
        );

    _scoreDigitLayout = 
        ScoreLayout(&_scoreDigitModelAdapter,
                    SCORE_TILESIZE,
                    SCORE_SCREEN_SIZE,
                    SCORE_SCREEN_OFFSET
        );

    _scoreDigitView =
        BoardView(&_scoreDigitModelAdapter,
                  &_scoreDigitLayout,
                  "artwork/sudoku-numbertiles-24px.png"
        );
    _scoreDigitView.show();

    // Set the last score into the widget
    SudokuScore::scoreToDigit(&_scoreDigitModel, lastScore);
}

GameOverState::~GameOverState() {
}

void GameOverState::processKeypressEvent(enum _keys key) {
    // No need to do anything. Set the game back to the beginning once user 
    // press any key
    GameManager_popGameState();
    GameManager_popGameState();
    GameManager_popGameState();
}

void GameOverState::update(sf::Time elapsedTime) {
    _scoreDigitView.update(elapsedTime);
}

void GameOverState::draw(sf::RenderWindow *win) {
    sf::Sprite background(_backgroundTexture);
    win->draw(background);

    _scoreDigitView.draw(win);
}
