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

#include <stack>
#include <SFML/Graphics.hpp>

#include "gamemanager.h"

#define GAMEWINDOW_WIDTH  480
#define GAMEWINDOW_HEIGHT 320

///
/// \brief The handler for the game window
///
static sf::RenderWindow _gameWindow;

///
/// \brief Flag to indicate whether the game is still running
///
static bool _gameIsRunning;

///
/// \brief Game state stack (to store the sequence of the game)
///
static std::stack<AbstractGameState *> _gameStateStack;

///
/// \brief Store the deleted game state, so it can be removed from the memory
///        when it's no longer used
///
static std::stack<AbstractGameState *> _deletedGameState;

///
/// \brief The current game state that's running
///
static AbstractGameState *_currentGameState;

///
/// \brief The flag to dispose the current game state
///
static bool _disposeCurrentGameState;

//-----------------------------------------------------------------------------
static void GameManager_processEvents() {
    sf::Event gameEvent;
    
    // Check if we have some event coming
    while (_gameWindow.pollEvent(gameEvent)) {
        // Update the state for the event. Some of the event is handled 
        // directly by the GameManager, the rest is handled by the Game
        // State
        switch (gameEvent.type) {
        case sf::Event::Closed: {
            // Stop the game
            _gameIsRunning = false;
            break;
        }

        case sf::Event::LostFocus: 
        case sf::Event::GainedFocus: {
            // Send pause event to the game state
            _currentGameState->
                processKeypressEvent(AbstractController::KEY_PAUSE);
            break;
        }

        case sf::Event::KeyPressed: {
            switch (gameEvent.key.code) {
            case sf::Keyboard::Escape: {
                // Toggle pause event to the game state
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_PAUSE);
                break;
            }
            case sf::Keyboard::Up: {
                // Send key up event to the game state
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_UP);
                break;
            }
            case sf::Keyboard::Down: {
                // Send key down event to the game state
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_DOWN);
                break;
            }
            case sf::Keyboard::Left: {
                // Send key left event to the game state
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_LEFT);
                break;
            }
            case sf::Keyboard::Right: {
                // Send key right event to the game state
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_RIGHT);
                break;
            }
            case sf::Keyboard::Space: 
            case sf::Keyboard::Return: {
                // Send key select event to the game state
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_SELECT);
                break;
            }
            case sf::Keyboard::Num1: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_1);
                break;
            }
            case sf::Keyboard::Num2: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_2);
                break;
            }
            case sf::Keyboard::Num3: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_3);
                break;
            }
            case sf::Keyboard::Num4: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_4);
                break;
            }
            case sf::Keyboard::Num5: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_5);
                break;
            }
            case sf::Keyboard::Num6: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_6);
                break;
            }
            case sf::Keyboard::Num7: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_7);
                break;
            }
            case sf::Keyboard::Num8: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_8);
                break;
            }
            case sf::Keyboard::Num9: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_9);
                break;
            }
            case sf::Keyboard::Delete: {
                _currentGameState->
                    processKeypressEvent(AbstractController::KEY_DELETE);
                break;
            }
            default: {
                // Other keyboard input. Ignore it.
                break;
            }
            }
        }

        case sf::Event::MouseMoved: {
            // TODO: Implement mouse mode handler
            break;
        }

        case sf::Event::MouseButtonPressed: {
            // TODO: Implement mouse button pressed handler
            break;
        }

        default: {
            // Ignore the system input
            break;
        }
        }
    }
}

//-----------------------------------------------------------------------------
void GameManager_init(void) {
    _gameWindow.create(sf::VideoMode(GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT),
                "Boring Sudoku",
                sf::Style::None);
    
    _gameIsRunning = true;
    _disposeCurrentGameState = false;

    // Center the game window in the center of the screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    sf::Vector2i  screenCenterPos((desktop.width  - GAMEWINDOW_WIDTH ) / 2,
                                  (desktop.height - GAMEWINDOW_HEIGHT) / 2);
    _gameWindow.setPosition(screenCenterPos);
}

void GameManager_pushGameState(AbstractGameState *state) {
    _gameStateStack.push(state);
}

void GameManager_popGameState() {
    _deletedGameState.push(_gameStateStack.top());
    _gameStateStack.pop();
    
    _disposeCurrentGameState = true;
}

void GameManager_stop() {
    _gameIsRunning = false;
}

void GameManager_run() {
    sf::Clock gameClock;

    while (_gameIsRunning) {
        // Sync the current game state
        _currentGameState = _gameStateStack.top();

        // Get the events from the system, and send it to the game state
        GameManager_processEvents();

        // Update the current game state view with elapsed time
        _currentGameState->update(gameClock.restart());

        // Clear the current window
        _gameWindow.clear();

        // Ask state to redraw
        _currentGameState->draw(&_gameWindow);

        // Re-paint the window
        _gameWindow.display();

        if (_disposeCurrentGameState) {
            while (!_deletedGameState.empty()) {
                AbstractGameState *gameState = _deletedGameState.top();
                delete gameState;
                _deletedGameState.pop();
            }
            
            _disposeCurrentGameState = false;
        }
    }

    // Clean up all the game state that's still left on the stack
    while(!_gameStateStack.empty()) {
        AbstractGameState *gameState = _gameStateStack.top();

        delete gameState;
        _gameStateStack.pop();
    }
}
