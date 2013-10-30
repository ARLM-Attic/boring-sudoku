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

#include "gamemanager.h"
#include "play9x9sudokustate.h"
#include "splashscreenstate.h"

#ifdef _WIN32            /* WIN32 platform specific (WinXP, Win7) */
#ifdef _MSC_VER          /* MS Visual Studio specific (including express 
                          * edition) 
                          */
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR, int) {
#endif
#else /* Win32-MinGW / Linux / etc */
int main(int argc,char *argv[]) {
#endif
    GameManager *theGame = GameManager::getInstance();

    // Init the sequence of the game state
    theGame->pushGameState(new Play9x9SudokuState(theGame));
    theGame->pushGameState(new SplashScreenState(theGame));

    theGame->run();

    return 0;
}
