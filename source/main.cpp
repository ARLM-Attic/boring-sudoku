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
 * The main file for SFML-Sudoku
 *
 * Note that under VC2012, the program is set as Win32 application so it won't
 * spawn console everytime it started. Under GCC (Linux / MingGW), keep it 
 * using standard main as usual
 */
#ifdef _WIN32            /* WIN32 platform specific (WinXP, Win7) */
#ifdef _MSC_VER          /* MS Visual Studio specific (including express 
                          * edition) 
                          */
#include <Windows.h>
#endif
#endif

#include <vector>
#include <SFML/Graphics.hpp>

#include "sudokuboardview.h"

#ifdef _WIN32            /* WIN32 platform specific (WinXP, Win7) */
#ifdef _MSC_VER          /* MS Visual Studio specific (including express 
                          * edition) 
                          */
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
#endif
#else /* Win32-MinGW / Linux / etc */
int main(int argc,char *argv[]) {
#endif
    sf::RenderWindow window(sf::VideoMode(480, 320), "Boring Sudoku Game");
    
    std::vector<int> sudokuboard(81, 3);

    sf::Texture boardTile;
    boardTile.loadFromFile("artwork/sudoku-numbertiles-24px.png");

    SudokuBoardView sudokuBoardView(
        &sudokuboard,
        SudokuBoardView::SUDOKUBOARD_SIZE_9X9, 
        &boardTile,
        sf::Vector2u(24, 24),
        sf::Vector2f(320, 320)
    );

    sudokuBoardView.update(sf::Time());

    std::vector<sf::Vertex> screenVertex(sudokuBoardView.begin(), sudokuBoardView.end());

    sf::Texture background;
    background.loadFromFile("artwork/sudoku-background.png");
    sf::Sprite backgroundSprite(background);

    sf::Texture cursor;
    cursor.loadFromFile("artwork/sudoku-cursor-36px.png");
    sf::Sprite cursorSprite(cursor);
    cursorSprite.setPosition(16.f, 16.f);

    while (window.isOpen()) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed)
                window.close();
        }

        // This will draw 1024 x 768 blank screen
        window.clear();

        window.draw(backgroundSprite);
        window.draw(cursorSprite);
        window.draw(&screenVertex[0], 
                    screenVertex.size(), 
                    sf::Quads, 
                    &boardTile);
        

        window.display();
    }

    return 0;
}
