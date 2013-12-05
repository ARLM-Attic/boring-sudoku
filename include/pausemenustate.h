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
 * Display the pause menu
 */

#ifndef __PAUSEMENUSTATE_H_
#define __PAUSEMENUSTATE_H_

#include <vector>
#include "abstractgamestate.h"
#include "boardmodeladapter.h"
#include "boardview.h"
#include "menulayout.h"

class PauseMenuState : public AbstractGameState {
public:
    explicit PauseMenuState();
    virtual ~PauseMenuState();

    //-------------------------------------------------------------------------
    // Abstractcontroller methods
    virtual void processKeypressEvent(enum _keys key);

    //-------------------------------------------------------------------------
    // AbstractViewer's methods
    virtual void update(sf::Time elapsedTime);
    virtual void draw(sf::RenderWindow *win);

private:
    ///
    /// \brief The background texture
    ///
    sf::Texture _backgroundTexture;

    //-------------------------------------------------------------------------
    ///
    /// \brief The pausemenu model, to hold the pausemenu items
    ///
    std::vector<unsigned int> _pausemenuModel;

    ///
    /// \brief The pausemenu model adapter
    ///
    BoardModelAdapter _pausemenuModelAdapter;

    ///
    /// \brief The pausemenu layout
    ///
    MenuLayout _pausemenuLayout;

    ///
    /// \brief The pausemenu view
    ///
    BoardView _pausemenuView;

    //-------------------------------------------------------------------------
    ///
    /// \brief The pausemenu options
    ///
    enum _pauseMenu {
        PAUSEMENU_NEWGAME,
        PAUSEMENU_CONTINUE,
        PAUSEMENU_QUIT,
        
        PAUSEMENU_END,
        PAUSEMENU_START = PAUSEMENU_NEWGAME,
    } _currentPauseMenu;

    ///
    /// \brief The tiles' vertex to draw
    ///
    std::vector<sf::Vertex> _vertex;
};

#endif // __PAUSEMENUSTATE_H_
