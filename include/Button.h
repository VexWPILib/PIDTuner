// Copyright (C) 2019 by James Pearman
//
// Permission is hereby granted, free of charge, to any person obtaining 
// a copy of this software and associated documentation files (the 
// "Software"), to deal in the Software without restriction, including 
// without l> imitation the rights to use, copy, modify, merge, publish, 
// distribute, sublicense, and/or sell copies of the Software, and to 
// permit persons to whom the Software is furnished to do so, subject 
// to the following conditions:
//
// The above copyright notice and this permission notice shall be included 
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
// SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include "vex.h"

#pragma once

typedef struct _button {
    int    xpos;
    int    ypos;
    int    width;
    int    height;
    const char  *label;
    const char  *labelSelected;
    bool   state;
    const vex::color &colorUnselected;
    const vex::color &colorSelected;
} button;

void drawButtons(button *b, int nButtons);
int findButton( button *buttons, int nButtons,  int16_t xpos, int16_t ypos );
void setSelected( button *buttons, int nButtons,  int16_t selectedIndex );

extern button buttonsP[];
extern button buttonsI[];
extern button buttonsD[];
extern button buttonsDAT[];