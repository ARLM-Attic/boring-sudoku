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

#define GAMEWINDOW_WIDTH  480
#define GAMEWINDOW_HEIGHT 320

GameManager *GameManager::_instance = NULL;

GameManager::GameManager() :
    _gameWindow(sf::VideoMode(GAMEWINDOW_WIDTH, GAMEWINDOW_HEIGHT),
                "Boring Sudoku",
                sf::Style::None),
    _gameIsRunning(true),
    _deleteCurrentGameState(false)
{
    // Center the game window in the center of the screen
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

    sf::Vector2i  screenCenterPos((desktop.width  - GAMEWINDOW_WIDTH ) / 2,
                                  (desktop.height - GAMEWINDOW_HEIGHT) / 2);
    _gameWindow.setPosition(screenCenterPos);
}

GameManager *GameManager::getInstance() {
    if (_instance == NULL) {
        _instance = new GameManager();
    }

    return _instance;
}

void GameManager::pushGameState(GameStateInterface *state) {
    _gameStateStack.push(state);
}

void GameManager::popGameState() {
    _gameStateStack.pop();

    _deleteCurrentGameState = true;
}

void GameManager::stop() {
    _gameIsRunning = false;
}

void GameManager::run() {
    sf::Clock gameClock;

    while (_gameIsRunning) {
        // If user ask to delete the current state, delete it here
        if (_deleteCurrentGameState) {
            delete _currentGameState;
            _deleteCurrentGameState = false;
        }

        // Sync the current game state
        _currentGameState = _gameStateStack.top();

        // Get the events from the system, and send it to the game state
        processEvents();

        // Update the current game state with elapsed time
        _currentGameState->update(gameClock.restart());

        // Clear the current window
        _gameWindow.clear();

        // Ask state to redraw
        _currentGameState->draw(&_gameWindow);

        // Re-paint the window
        _gameWindow.display();
    }

    // Clean up all the game state that's still left on the stack
    while(!_gameStateStack.empty()) {
        GameStateInterface *gameState = _gameStateStack.top();

        delete gameState;
        _gameStateStack.pop();
    }
}

void GameManager::processEvents() {
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

        case sf::Event::LostFocus: {
            // Send pause event to the game state
            _currentGameState->pause();
            break;
        }

        case sf::Event::GainedFocus: {
            // Send resume event to the game state
            _currentGameState->resume();
            break;
        }

        case sf::Event::KeyPressed: {
            switch (gameEvent.key.code) {
            case sf::Keyboard::Escape: {
                // Toggle pause event to the game state
                if (_currentGameState->isPaused()) {
                    _currentGameState->resume();
                } else {
                    _currentGameState->pause();
                }
                break;
            }
            case sf::Keyboard::Up: {
                // Send key up event to the game state
                _currentGameState->up();
                break;
            }
            case sf::Keyboard::Down: {
                // Send key down event to the game state
                _currentGameState->down();
                break;
            }
            case sf::Keyboard::Left: {
                // Send key left event to the game state
                _currentGameState->left();
                break;
            }
            case sf::Keyboard::Right: {
                // Send key right event to the game state
                _currentGameState->right();
                break;
            }
            case sf::Keyboard::Space: 
            case sf::Keyboard::Return: {
                // Send key select event to the game state
                _currentGameState->select();
                break;
            }
            default: {
                // Other keyboard input. Ignore it.
                break;
            }
            }
        }

        case sf::Event::MouseMoved: {
            _currentGameState->mouseMove(gameEvent.mouseMove.x, 
                                        gameEvent.mouseMove.y);
            break;
        }

        case sf::Event::MouseButtonPressed: {
            _currentGameState->mouseMove(gameEvent.mouseButton.x, 
                                        gameEvent.mouseButton.y);
            _currentGameState->select();
            break;
        }

        default: {
            // Ignore the system input
            break;
        }
        }
    }
}
