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
 * Store the tile's information (its graphic properties)
 */

#ifndef __SUDOKUTILEVIEW_H_
#define __SUDOKUTILEVIEW_H_

#include <vector>
#include <SFML/Graphics.hpp>

class SudokuTileView {
public:
    ///
    /// \brief Create Sudoku tile, with _tilePos = (0, 0)
    ///
    /// \param tileValue The pointer to the real tile value
    /// \param tilemap  Pointer to the tilemap texture
    /// \param tileSize The size of each tile in pixel
    ///
    SudokuTileView(int         *tileValue, 
                   sf::Texture *tilemap, 
                   sf::Vector2u tileSize);

    ///
    /// \brief Set tile's drawing position in screen
    ///
    /// \param position The tile's new position in screen
    ///
    void setPosition(sf::Vector2f position) {
        _tilePos = position;
    }

    ///
    /// \brief Get the tile's position in the screen
    ///
    /// \return The tile's position in screen
    ///
    sf::Vector2f getPosition() {
        return _tilePos;
    }

    ///
    /// \brief Get the tile's size
    ///
    /// This function is needed to make sure that the tile can be drawn without
    /// overlapped each other
    ///
    /// \return Tile size (in pixel)
    sf::Vector2u getTileSize() {
        return _tileSize;
    }

    //-------------------------------------------------------------------------
    // Interface to get the Vertex of this tile to be drawn in the screen
    
    ///
    /// \brief Adjust tile's texture to match the value, and its 4  corners to 
    ///        fit the new position on the screen
    ///
    void update(sf::Time elapsedTime);

    std::vector<sf::Vertex>::iterator begin() {
        return _vertex.begin();
    }

    std::vector<sf::Vertex>::iterator end() {
        return _vertex.end();
    }

    std::vector<sf::Vertex>::const_iterator begin() const {
        return _vertex.begin();
    }

    std::vector<sf::Vertex>::const_iterator end() const {
        return _vertex.end();
    }

private:
    ///
    /// \brief The pointer to value of the tile
    ///
    int *_tileValue;

    ///
    /// \brief Tile's center position in the screen
    ///
    sf::Vector2f _tilePos;

    ///
    /// \brief The vertex to draw the tile
    ///
    std::vector<sf::Vertex> _vertex;

    ///
    /// \brief The pointer to the texture of the tile
    ///
    sf::Texture *_texture;

    ///
    /// \brief The tile size (in pixel)
    ///
    sf::Vector2u _tileSize;
};

#endif // __SUDOKUTILEVIEW_H_
