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

#include "sudokuscore.h"

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
/// \brief The score display length (in digit)
///
#define SCORE_DIGIT_LENGTH    5

//-----------------------------------------------------------------------------
///
/// \brief The number tilemap that's used in this game store no 0 symbol at pos 
///        #11
///
#define TILEMAP_SYMBOL_0      10

//-----------------------------------------------------------------------------
///
/// \brief The maximum score per tile
///
#define MAXIMUM_SCORE_PER_TILE 300

//-----------------------------------------------------------------------------
///
/// \brief The maximum time allowed for filling a tile
///
#define MAXIMUM_TIME_PER_TILE   sf::seconds(60.f)

//-----------------------------------------------------------------------------
SudokuScore::SudokuScore(std::vector<unsigned int> *board,
                         unsigned int               columnSize,
                         sf::Vector2f               screenSize,
                         sf::Vector2f               screenOffset) {
    if (board == NULL) { 
        return; 
    }

    _currentScore = MAXIMUM_SCORE_PER_TILE;

    // Init score for each tiles to 0
    _scoreModel = std::vector<unsigned int> (board->size(), 0);

    _scoreModelAdapter = 
        BoardModelAdapter(&_scoreModel, 
                          columnSize
        );

    // Set display digit to 0
    _scoreDigitModel = std::vector<unsigned int> (SCORE_DIGIT_LENGTH, 0);

    _scoreDigitModelAdapter =
        BoardModelAdapter(&this->_scoreDigitModel, 
                          SCORE_COLUMN_SIZE
        );

    _scoreDigitLayout = 
        ScoreLayout(&_scoreDigitModelAdapter,
                    SCORE_TILESIZE,
                    screenSize,
                    screenOffset
        );

    _scoreDigitView =
        BoardView(&_scoreDigitModelAdapter,
                  &_scoreDigitLayout,
                  "artwork/sudoku-numbertiles-24px.png"
        );
    _scoreDigitView.show();
}

void SudokuScore::updateScore(int row, int col) {
    // Only update the score for that tile, if it is not set before
    if (_scoreModelAdapter.value(row, col) == 0) {
        
        _scoreModelAdapter.setValue(_currentScore, row, col);
        
        // After the _currentScore is used, reset it to max again, also reset 
        // the score timer
        _currentScore = MAXIMUM_SCORE_PER_TILE;
        _runningTime = sf::seconds(0.f);

        // Convert the total score into display digit
        scoreToDigit(&_scoreDigitModel, totalScore());
    }
}

void SudokuScore::update(sf::Time elapsedTime) {
    countdownScore(elapsedTime);
    _scoreDigitView.update(elapsedTime);
}

void SudokuScore::draw(sf::RenderWindow *win) {
    _scoreDigitView.draw(win);
}

unsigned int SudokuScore::totalScore() {
    unsigned int totalScore = 0;
    for (unsigned int i = 0; i < _scoreModel.size(); i++) {
        totalScore += _scoreModel[i];
    }

    return totalScore;
}

void SudokuScore::countdownScore(sf::Time elapsedTime) {
    _runningTime += elapsedTime;

    if (_runningTime > MAXIMUM_TIME_PER_TILE) {
        _runningTime = MAXIMUM_TIME_PER_TILE;
    }

    _currentScore = (unsigned int) (MAXIMUM_SCORE_PER_TILE * 
        (1 - (_runningTime.asSeconds() / MAXIMUM_TIME_PER_TILE.asSeconds())));
}

void SudokuScore::scoreToDigit(std::vector<unsigned int> *digitModel, 
                               unsigned int               score) {
    unsigned int divider = 10;
    for (unsigned int i = 0; i < SCORE_DIGIT_LENGTH; i++) {
        (*digitModel)[(SCORE_DIGIT_LENGTH -1) - i] = (score % divider);

        if ((*digitModel)[(SCORE_DIGIT_LENGTH -1) - i] == 0) {
            (*digitModel)[(SCORE_DIGIT_LENGTH -1) - i] = TILEMAP_SYMBOL_0;
        }
        
        score = score / divider;
    }
}
