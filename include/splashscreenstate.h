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
 * Display splashscreen for the game
 */

#ifndef __SPLASHSCREENSTATE_H_
#define __SPLASHSCREENSTATE_H_

#include "gamemanager.h"
#include "gamestateinterface.h"

class SplashScreenState : public GameStateInterface {
public:
    explicit SplashScreenState  (GameManager *manager);

    void pause()                 { }
    void resume()                { }
    bool isPaused()              { return false; }
    void up()                    { }
    void down()                  { }
    void left()                  { }
    void right()                 { }
    void select()                { }
    void mouseMove(int x, int y) { }

    void update(sf::Time elapsedTime);
    void draw  (sf::RenderWindow *win);

private:
    ///
    /// \brief The access to the game manager
    ///
    GameManager *_manager;

    ///
    /// \brief The Splashscreen texture
    ///
    sf::Texture _texture;

    ///
    /// \brief Track the running time of this state
    ///
    sf::Time    _runningTime;

    //-------------------------------------------------------------------------
    // Avoid copy and const copy
    SplashScreenState           (SplashScreenState const&) { };
    SplashScreenState& operator=(SplashScreenState const&) { };
};

#endif // __SPLASHSCREENSTATE_H_
