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

#ifndef __TILELOADER_H_
#define __TILELOADER_H_

#include <vector>
#include <SFML/Graphics.hpp>

class TileLoader {
public:
    ///
    /// Create TileLoader based on texture tileset
    ///
    /// \param texturesize  The texture size. The texture must have uniformed 
    ///                     size.
    /// \param tilesize     The size of each tile in the texture
    ///
    explicit TileLoader(sf::Vector2u texturesize, sf::Vector2u tilesize);

    ///
    /// Update the texture tileset
    ///
    /// \param texture  The texture size. The texture must have uniformed 
    ///                     size.
    /// \param tilesize The size of each tile in the texture
    ///
    void setTileset(sf::Vector2u texturesize, sf::Vector2u tilesize);

    ///
    /// Map the level with tiles from tile set
    ///
    /// \param level       The level
    /// \param levelSize   The level size (length x width)
    /// \param levelOffset The offset for the level from window's origin (0px, 0px)
    ///
    void mapTiles(unsigned char *level, 
                  sf::Vector2u   levelSize, 
                  sf::Vector2f   levelOffset = sf::Vector2f(0.f, 0.f));

    ///
    /// Map the level vertex that's pointed by levelPosition array with texture
    /// from tileset. This can be used to load the tile at certain defined 
    /// position. Note that the levelVertex should be in sf::Quad primitives. 
    ///
    /// \param levelPosition The level coordinates
    /// \param levelTile     The tile no from tileset
    ///
    void mapTiles(std::vector<sf::Vertex> levelVertex, 
                  std::vector<int>        levelTile);

    // Iterator interface so the vertex can be joined in the user class. 
    // Declare it in header file so it will be inlined

    typedef std::vector<sf::Vertex>::iterator iterator;
    iterator begin() { return _vertexarray.begin(); }
    iterator end()   { return _vertexarray.end();   }

    typedef std::vector<sf::Vertex>::const_iterator const_iterator;
    const_iterator begin() const { return _vertexarray.begin(); }
    const_iterator end()   const { return _vertexarray.end();   }

    ///
    /// Clear the vertex array
    ///
    void clear() { _vertexarray.clear(); }

private:
    // The texture size
    sf::Vector2u _texturesize;

    // The tile size in the texture
    sf::Vector2u _tilesize;

    // Array to hold the vertex
    std::vector<sf::Vertex> _vertexarray;
};

#endif // __TILELOADER_H_
