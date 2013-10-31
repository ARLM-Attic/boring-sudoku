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

#ifndef __GAMEMANAGER_H_
#define __GAMEMANAGER_H_

#include <stack>
#include <SFML/Graphics.hpp>
#include "abstractgamestate.h"

class GameManager {
public:
    ///
    /// \brief Get the game manager instance
    ///
    static GameManager *getInstance();

    ///
    /// \brief Push game state to be executed
    ///
    /// This function should be executed in the game state class to update
    /// the current game state
    ///
    /// \param state The game state to be executed
    ///
    void pushGameState(AbstractGameState *state);

    ///
    /// \brief Remove game state from the stack
    ///
    /// This function should be executed in the game state class to update
    /// the current game state
    ///
    void popGameState();

    /// \brief Stop the game
    ///
    /// This function should be execued in the game state class to stop the 
    /// game
    ///
    void stop();

    ///
    /// \brief Run the game
    ///
    void run();

private:
    ///
    /// \brief Process / filter the events and distribute it to the game state
    ///
    void processEvents();

    ///
    /// \brief The current game state.
    ///
    /// This member is needed to avoid the game state popped / pushed in the 
    /// middle of screen update
    ///
    AbstractGameState *_currentGameState;

    ///
    /// \brief The stack of game state
    ///
    std::stack<AbstractGameState *> _gameStateStack;

    ///
    /// \brief The main view to render the animation / games
    ///
    sf::RenderWindow _gameWindow;

    ///
    /// \brief Flag to indicate if game should be run
    ///
    bool _gameIsRunning;

    ///
    /// \brief Flag to delete the current game state
    ///
    bool _deleteCurrentGameState;

    //-------------------------------------------------------------------------
    // The singleton class pattern
    explicit GameManager  ();
    GameManager           (GameManager const&) { };
    GameManager& operator=(GameManager const&) { };
    static GameManager    *_instance;
};

#endif // __GAMEMANAGER_H_
