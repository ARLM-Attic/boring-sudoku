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
 * Store the board's view information (its graphic properties)
 */

#ifndef __BOARDVIEW_H_
#define __BOARDVIEW_H_

#include "abstractviewer.h"
#include "boardmodeladapter.h"
#include "boardlayout.h"
#include "tileview.h"

class BoardView : public AbstractViewer {
public:
    ///
    /// \brief The board's view constructor
    ///
    /// \param board           The board's model
    /// \param layout          The board's layout
    /// \param tilemapFilename The board's tilemap texture. 
    /// \param tileSize        The size of each tile in tilemap
    ///
    explicit BoardView(BoardModelAdapter *board           = NULL,
                       BoardLayout       *layout          = NULL,               
                       const std::string &tilemapFilename = ""
    );

    //-------------------------------------------------------------------------
    // Override the AbstractViewer's methods
    virtual void update(sf::Time elapsedTime);
    virtual void draw(sf::RenderWindow *win);

    ///
    /// \brief Virtual destructor so this class can be overridden
    ///
    virtual ~BoardView() { }

private:
    ///
    /// \brief The board model
    ///
    BoardModelAdapter *_board;

    ///
    /// \brief The tile texture for the board
    ///
    sf::Texture _tileTexture;

    ///
    /// \brief The board tiles
    ///
    std::vector<TileView> _boardTiles;
    
    ///
    /// \brief The tiles' vertex to draw
    ///
    std::vector<sf::Vertex> _vertex;
};

#endif // __BOARDVIEW_H_
