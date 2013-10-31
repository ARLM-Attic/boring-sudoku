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
 * Provide base class to interface the 'view' with user input (controller)
 */

#ifndef __ABSTRACTCONTROLLER_H_
#define __ABSTRACTCONTROLLER_H_

class AbstractController {
public:
    ///
    /// \brief 'Up' key is pressed event
    ///
    virtual void up() { }

    ///
    /// \brief 'Down' key is pressed event
    ///
    virtual void down() { }

    ///
    /// \brief 'Left' key is pressed event
    ///
    virtual void left() { }

    ///
    /// \brief 'Right' key is pressed event
    ///
    virtual void right() { }

    ///
    /// \brief Menu / item selected event
    ///
    virtual void select() { }

    ///
    /// \brief The mouse move event
    ///
    /// \param x The column of the current mouse pointer (measured from most 
    ///          left column of the window)
    /// \param y The row of the current mouse pointer (measured from most up 
    ///          row of the window)
    ///
    virtual void mouseMove(int x, int y) { }

    ///
    /// \brief The controller's destructor
    ///
    virtual ~AbstractController() { }
};

#endif // __ABSTRACTCONTROLLER_H_
