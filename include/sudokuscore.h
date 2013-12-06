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
 * Manage the sudoku score
 */

#ifndef __SUDOKUSCORE_H_
#define __SUDOKUSCORE_H_

#include <vector>
#include "abstractviewer.h"
#include "boardmodeladapter.h"
#include "boardview.h"
#include "scorelayout.h"

class SudokuScore : public AbstractViewer {
public:
    SudokuScore(std::vector<unsigned int> *board      = NULL,
                unsigned int               columnSize = 0,
                sf::Vector2f               screenSize   = sf::Vector2f(0, 0),
                sf::Vector2f               screenOffset = sf::Vector2f(0, 0)
    );

    ///
    /// \brief Update the score for the tile in row, col. This should be 
    ///        called when user has successfullt inserting new digit to the
    ///        board
    ///
    /// \param row The row of the tile
    /// \param col The column of the tile
    ///
    void updateScore(int row, int col);

    //-------------------------------------------------------------------------
    // AbstractViewer's methods
    virtual void update(sf::Time elapsedTime);
    virtual void draw(sf::RenderWindow *win);

private:
    ///
    /// \brief Count down the _currentScore, based on the time elapsed
    ///
    /// \param elapsedTime The time that has elapsed
    ///
    void countdownScore(sf::Time elapsedTime);

    //-------------------------------------------------------------------------
    ///
    /// \brief The current score. This value will be decreased along the time
    ///
    unsigned int _currentScore;

    ///
    /// \brief Hold the score for each tiles
    ///
    std::vector<unsigned int> _scoreModel;

    ///
    /// \brief The score model adapter
    ///
    BoardModelAdapter _scoreModelAdapter;

    //-------------------------------------------------------------------------
    ///
    /// \brief The score digit model, to hold the score digits
    ///
    std::vector<unsigned int> _scoreDigitModel;

    ///
    /// \brief The score digit model adapter
    ///
    BoardModelAdapter _scoreDigitModelAdapter;

    ///
    /// \brief The score digit layout
    ///
    ScoreLayout _scoreDigitLayout;

    ///
    /// \brief The score digit view adapter
    ///
    BoardView _scoreDigitView;

    //-------------------------------------------------------------------------
    ///
    /// \brief The running time for the current tile selection
    ///
    sf::Time    _runningTime;
};

#endif // __SUDOKUSCORE_H_
