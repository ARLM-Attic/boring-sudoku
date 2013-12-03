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

#include "abstractgamestate.h"

///
/// \brief Init the game manager
///
void GameManager_init(void);

///
/// \brief Push game state to be executed
///
/// This function should be executed in the game state class to update
/// the current game state
///
/// \param state The game state to be executed
///
void GameManager_pushGameState(AbstractGameState *state);

///
/// \brief Remove game state from the stack
///
/// This function should be executed in the game state class to update
/// the current game state
///
void GameManager_popGameState();

///
/// \brief Stop the game
///
/// This function should be execued in the game state class to stop the 
/// game
///
void GameManager_stop();

///
/// \brief Run the game
///
void GameManager_run();

#endif // __GAMEMANAGER_H_
