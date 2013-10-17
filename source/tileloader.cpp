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

#include "tileloader.h"

TileLoader::TileLoader(sf::Vector2u texturesize, sf::Vector2u tilesize) {
    setTileset(texturesize, tilesize);
}

void TileLoader::setTileset(sf::Vector2u texturesize, sf::Vector2u tilesize) {
    _texturesize = texturesize;
    _tilesize    = tilesize;
}

void TileLoader::mapTiles(unsigned char *level, 
                          sf::Vector2u   levelSize, 
                          sf::Vector2f   levelOffset) {
    // For each tile in the level, we need 4 vertex points
    _vertexarray.resize(levelSize.x * levelSize.y * 4);

    // Scan every tile in the tile for their value, and map it to the correct
    // tile texture
    for (unsigned int i = 0; i < levelSize.x; i++) {
        for (unsigned int j = 0; j < levelSize.y; j++) {
            // Get a pointer to the current tile's quad
            sf::Vertex* quad = &_vertexarray[(i + (j * levelSize.x)) * 4];
            
            // Define its 4 corners
            quad[0].position = sf::Vector2f(
                (i       * _tilesize.x) + levelOffset.x,
                (j       * _tilesize.y) + levelOffset.y
            );
            quad[1].position = sf::Vector2f(
                ((i + 1) * _tilesize.x) + levelOffset.x,
                (j       * _tilesize.y) + levelOffset.y
            );
            quad[2].position = sf::Vector2f(
                ((i + 1) * _tilesize.x) + levelOffset.x,
                ((j + 1) * _tilesize.y) + levelOffset.y
            );
            quad[3].position = sf::Vector2f(
                (i       * _tilesize.x) + levelOffset.x,
                ((j + 1) * _tilesize.y) + levelOffset.y
            );
            
            // Define tile texture
            unsigned char tileNumber = level[i + (j * levelSize.x)];
            // Find the tileNumber column in the tileset
            float tu = (float) (tileNumber % (_texturesize.x / _tilesize.x));
            // Find the tileNumber row in the tileset
            float tv = (float) (tileNumber / (_texturesize.x / _tilesize.x));

            // Define its 4 texture coordinates
            quad[0].texCoords = sf::Vector2f(
                (tu       * _tilesize.x), (tv       * _tilesize.y)
            );
            quad[1].texCoords = sf::Vector2f(
                ((tu + 1) * _tilesize.x), (tv       * _tilesize.y)
            );
            quad[2].texCoords = sf::Vector2f(
                ((tu + 1) * _tilesize.x), ((tv + 1) * _tilesize.y)
            );
            quad[3].texCoords = sf::Vector2f(
                (tu       * _tilesize.x), ((tv + 1) * _tilesize.y)
            );
        }
    }
}

void TileLoader::mapTiles(std::vector<sf::Vertex> levelVertex, 
                          std::vector<int>        levelTile) {
    // No of sf::Quad to be filled must match the numbers of value that are 
    // available
    unsigned int noOfQuadToBeFilled = levelVertex.size() / 4;
    if (noOfQuadToBeFilled != levelTile.size()) {
        return;
    }

    // Copy the levelVertex into the class' vector
    _vertexarray.clear();
    _vertexarray.insert(_vertexarray.end(), 
                        levelVertex.begin(), 
                        levelVertex.end());

    for (unsigned int i = 0; i < levelTile.size(); i++) {
        // Define tile texture
        unsigned char tileNumber = levelTile[i];
        // Find the tileNumber column in the tileset
        float tu = (float) (tileNumber % (_texturesize.x / _tilesize.x));
        // Find the tileNumber row in the tileset
        float tv = (float) (tileNumber / (_texturesize.x / _tilesize.x));
        
        // Define its 4 texture coordinates
        _vertexarray[(i + 0)].texCoords = sf::Vector2f(
            (tu       * _tilesize.x), (tv       * _tilesize.y)
        );
        _vertexarray[(i + 1)].texCoords = sf::Vector2f(
            ((tu + 1) * _tilesize.x), (tv       * _tilesize.y)
        );
        _vertexarray[(i + 2)].texCoords = sf::Vector2f(
            ((tu + 1) * _tilesize.x), ((tv + 1) * _tilesize.y)
        );
        _vertexarray[(i + 3)].texCoords = sf::Vector2f(
            (tu       * _tilesize.x), ((tv + 1) * _tilesize.y)
        );
    }
}
