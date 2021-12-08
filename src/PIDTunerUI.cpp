// Copyright (c) VexWPIApi contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the VexWPIApi BSD license file in the root directory of this project.

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

#include "PIDTunerUI.h"
#include "Button.h"

using namespace vpi;

PIDFParameters PID_d(1.0,0,0,0);
PIDFParameters PID_a(1.0,0,0,0);
PIDFParameters PID_t(1.0,0,0,0);

#define PID_BUTTONS_X_START 20
#define PID_BUTTONS_Y_START 20
#define PID_BUTTONS_WIDTH 40
#define PID_BUTTONS_HEIGHT 40

#define DAT_BUTTONS_X_START 20
#define DAT_BUTTONS_Y_START 20
#define DAT_BUTTONS_WIDTH 80
#define DAT_BUTTONS_HEIGHT 40

double CHANGE_AMOUNT[] = {-0.05, -0.01, -0.001, .001, .01, .05 };

button buttonsP[] = {
  {PID_BUTTONS_X_START + 0 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 0 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.05", "-.05", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 1 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 0 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.01", "-.01", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 2 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 0 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.001", "-.001", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 3 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 0 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".001", ".001", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 4 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 0 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".01", ".01", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 5 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 0 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".05", ".05", false, vex::color::blue, vex::color::cyan},
};

button buttonsI[] = {
  {PID_BUTTONS_X_START + 0 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 1 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.05", "-.05", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 1 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 1 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.01", "-.01", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 2 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 1 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.001", "-.001", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 3 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 1 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".001", ".001", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 4 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 1 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".01", ".01", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 5 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 1 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".05", ".05", false, vex::color::blue, vex::color::cyan},
};

button buttonsD[] = {
  {PID_BUTTONS_X_START + 0 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 2 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.05", "-.05", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 1 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 2 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.01", "-.01", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 2 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 2 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, "-.001", "-.001", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 3 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 2 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".001", ".001", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 4 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 2 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".01", ".01", false, vex::color::blue, vex::color::cyan},
  {PID_BUTTONS_X_START + 5 * (PID_BUTTONS_WIDTH + 10), PID_BUTTONS_Y_START + 2 * (PID_BUTTONS_HEIGHT + 10), 
    PID_BUTTONS_WIDTH, PID_BUTTONS_HEIGHT, ".05", ".05", false, vex::color::blue, vex::color::cyan},
};

button buttonsDAT[] = {
  {DAT_BUTTONS_X_START + 0 * (DAT_BUTTONS_WIDTH + 10), DAT_BUTTONS_Y_START + 3 * (DAT_BUTTONS_HEIGHT + 10), 
    DAT_BUTTONS_WIDTH, DAT_BUTTONS_HEIGHT, "Drive", "Drive", false, vex::color::blue, vex::color::cyan},
  {DAT_BUTTONS_X_START + 1 * (DAT_BUTTONS_WIDTH + 10), DAT_BUTTONS_Y_START + 3 * (DAT_BUTTONS_HEIGHT + 10), 
    DAT_BUTTONS_WIDTH, DAT_BUTTONS_HEIGHT, "Angle", "Angle", false, vex::color::blue, vex::color::cyan},
  {DAT_BUTTONS_X_START + 2 * (DAT_BUTTONS_WIDTH + 10), DAT_BUTTONS_Y_START + 3 * (DAT_BUTTONS_HEIGHT + 10), 
    DAT_BUTTONS_WIDTH, DAT_BUTTONS_HEIGHT, "Turn", "Turn", false, vex::color::blue, vex::color::cyan}
};

int datSelected = 0;

int findButton( button *buttons, int nButtons,  int16_t xpos, int16_t ypos ) {
  for( int index=0;index < nButtons;index++) {
    button *pButton = &buttons[ index ];
    if( xpos < pButton->xpos || xpos > (pButton->xpos + pButton->width) )
      continue;

    if( ypos < pButton->ypos || ypos > (pButton->ypos + pButton->height) )
      continue;
    
    return(index);
  }
  return (-1);
}

void setSelected( button *buttons, int nButtons,  int16_t selectedIndex ) {
  for( int index=0;index < nButtons;index++) {
    button *pButton = &buttons[ index ];
    pButton->state = (index == selectedIndex ? true : false);
  }
}

void updatePIDValue(int datId, int pidId, double d) {
  if(datId == 0) {
    // Drive PID
    if(pidId == 0 ){
      PID_d.Kp += d;
    } else if(pidId == 1 ){
      PID_d.Ki += d;
    } else {
      PID_d.Kd += d;
    }
  } else if(datId == 1) {
    // Angle PID
    if(pidId == 0 ){
      PID_a.Kp += d;
    } else if(pidId == 1 ){
      PID_a.Ki += d;
    } else {
      PID_a.Kd += d;
    }
  } else {
    // Turn PID
    if(pidId == 0 ){
      PID_t.Kp += d;
    } else if(pidId == 1 ){
      PID_t.Ki += d;
    } else {
      PID_t.Kd += d;
    }
  }
}

void displayPIDValue(int datId) {
  int px = PID_BUTTONS_X_START + 6 * (PID_BUTTONS_WIDTH + 10);
  int py = PID_BUTTONS_Y_START + 0 * (PID_BUTTONS_HEIGHT + 10) + PID_BUTTONS_HEIGHT / 2;
  int ix = PID_BUTTONS_X_START + 6 * (PID_BUTTONS_WIDTH + 10);
  int iy = PID_BUTTONS_Y_START + 1 * (PID_BUTTONS_HEIGHT + 10) + PID_BUTTONS_HEIGHT / 2;
  int dx = PID_BUTTONS_X_START + 6 * (PID_BUTTONS_WIDTH + 10);
  int dy = PID_BUTTONS_Y_START + 2 * (PID_BUTTONS_HEIGHT + 10) + PID_BUTTONS_HEIGHT / 2;
  Brain.Screen.setPenColor(vex::color::black);
  Brain.Screen.drawRectangle(px, py, 50, 50, vex::color::black);
  Brain.Screen.drawRectangle(ix, iy, 50, 50, vex::color::black);
  Brain.Screen.drawRectangle(dx, dy, 50, 50, vex::color::black);
  Brain.Screen.setPenColor(vex::color::white);
  if(datId == 0) {
    // Drive PID
    printf("DRIVE PID:\n");
    Brain.Screen.printAt(px, py, false, "P=%.3f", PID_d.Kp);
    printf("P=%.3f\n", PID_d.Kp);
    Brain.Screen.printAt(ix, iy, false, "I=%.3f", PID_d.Ki);
    printf("I=%.3f\n", PID_d.Ki);
    Brain.Screen.printAt(dx, dy, false, "D=%.3f", PID_d.Kd);
    printf("D=%.3f\n", PID_d.Kd);
  } else if(datId == 1) {
    // Angle PID
    printf("ANGLE PID:\n");
    Brain.Screen.printAt(px, py, false, "P=%.3f", PID_a.Kp);
    printf("P=%.3f\n", PID_a.Kp);
    Brain.Screen.printAt(ix, iy, false, "I=%.3f", PID_a.Ki);
    printf("I=%.3f\n", PID_a.Ki);
    Brain.Screen.printAt(dx, dy, false, "D=%.3f", PID_a.Kd);
    printf("D=%.3f\n", PID_a.Kd);
  } else {
    // Turn PID
    printf("TURN PID:\n");
    Brain.Screen.printAt(px, py, false, "P=%.3f", PID_t.Kp);
    printf("P=%.3f\n", PID_t.Kp);
    Brain.Screen.printAt(ix, iy, false, "I=%.3f", PID_t.Ki);
    printf("I=%.3f\n", PID_t.Ki);
    Brain.Screen.printAt(dx, dy, false, "D=%.3f", PID_t.Kd);
    printf("D=%.3f\n", PID_t.Kd);
  }
}

void userTouchCallbackReleased() {
  int index;
  int xpos = Brain.Screen.xPosition();
  int ypos = Brain.Screen.yPosition();

  int nPButtons = sizeof(buttonsP) / sizeof(button);
  int nIButtons = sizeof(buttonsI) / sizeof(button);
  int nDButtons = sizeof(buttonsD) / sizeof(button);
  int nDATButtons = sizeof(buttonsDAT) / sizeof(button);

  if( (index = findButton(buttonsP, nPButtons, xpos, ypos )) >= 0 ) {
    printf("Update P by index %d\n",index);
    updatePIDValue(datSelected, 0, CHANGE_AMOUNT[index]); // Update P
  } else if( (index = findButton(buttonsI, nIButtons, xpos, ypos )) >= 0 ) {
    printf("Update I by index %d\n",index);
    updatePIDValue(datSelected, 1, CHANGE_AMOUNT[index]); // Update I
  } else if( (index = findButton(buttonsD, nDButtons, xpos, ypos )) >= 0 ) {
    printf("Update D by index %d\n",index);
    updatePIDValue(datSelected, 2, CHANGE_AMOUNT[index]); // Update D
  } else if( (index = findButton(buttonsDAT, nDATButtons, xpos, ypos )) >= 0 ) {
    datSelected = index;
    setSelected(buttonsDAT, nDATButtons, datSelected);
    printf("Update DAT by index %d\n",index);
  }
  Brain.Screen.clearScreen();
  drawButtons(buttonsP, nPButtons);
  drawButtons(buttonsI, nIButtons);
  drawButtons(buttonsD, nDButtons);
  drawButtons(buttonsDAT, nDATButtons);
  displayPIDValue(datSelected);
}

void drawButtons(button *buttons, int nButtons) {
  for( int index=0;index < nButtons;index++) {
    button *b = &buttons[ index ];
    vex::color c = vex::color::blue;
    c = b->colorUnselected;
    const char *text = b->label;
    if (b->state) {
      c = b->colorSelected;
      text = b->labelSelected;
    }

    Brain.Screen.setFillColor(c);
    Brain.Screen.drawRectangle(b->xpos, b->ypos, b->width, b->height);
    int x = b->xpos + b->width / 2 - Brain.Screen.getStringWidth(text) / 2;
    int y = b->ypos + b->height / 2 + Brain.Screen.getStringHeight(text) / 2;
    Brain.Screen.printAt(x, y, false, text);
  }
}

void initButtons() {
  int nPButtons = sizeof(buttonsP) / sizeof(button);
  int nIButtons = sizeof(buttonsI) / sizeof(button);
  int nDButtons = sizeof(buttonsD) / sizeof(button);
  int nDATButtons = sizeof(buttonsDAT) / sizeof(button);
  drawButtons(buttonsP, nPButtons);
  drawButtons(buttonsI, nIButtons);
  drawButtons(buttonsD, nDButtons);
  setSelected(buttonsDAT, nDATButtons, datSelected);
  drawButtons(buttonsDAT, nDATButtons);
  displayPIDValue(datSelected);

  Brain.Screen.released( userTouchCallbackReleased );
}

#if 0
    lv_obj_t *pBtnm;
    lv_obj_t *pLabel;
    lv_obj_t *iBtnm;
    lv_obj_t *iLabel;
    lv_obj_t *dBtnm;
    lv_obj_t *dLabel;
    lv_obj_t *datBtnm;

    int lastDat = 0;
    
    void btnmPEventHandler(lv_obj_t * obj, lv_event_t e){
      if(e == LV_EVENT_VALUE_CHANGED) {
        int i = lv_btnmatrix_get_active_btn(obj);
        int idat = lastDat;
        if(i == 0) {
          if(idat == 0) {
            PID_d.Kp -= .05;
          } else if (idat == 1) {
            PID_a.Kp -= .05;
          } else if (idat == 2) {
            PID_t.Kp -= .05;
          }
        } else if (i == 1) {
          if(idat == 0) {
            PID_d.Kp -= .01;
          } else if (idat == 1) {
            PID_a.Kp -= .01;
          } else if (idat == 2) {
            PID_t.Kp -= .01;
          }
        } else if (i == 2) {
          if(idat == 0) {
            PID_d.Kp -= .001;
          } else if (idat == 1) {
            PID_a.Kp -= .001;
          } else if (idat == 2) {
            PID_t.Kp -= .001;
          }
        } else if (i == 3) {
          if(idat == 0) {
            PID_d.Kp += .001;
          } else if (idat == 1) {
            PID_a.Kp += .001;
          } else if (idat == 2) {
            PID_t.Kp += .001;
          }
        } else if (i == 4) {
          if(idat == 0) {
            PID_d.Kp += .01;
          } else if (idat == 1) {
            PID_a.Kp += .01;
          } else if (idat == 2) {
            PID_t.Kp += .01;
          }
        } else if (i == 5) {
          if(idat == 0) {
            PID_d.Kp += .05;
          } else if (idat == 1) {
            PID_a.Kp += .05;
          } else if (idat == 2) {
            PID_t.Kp += .05;
          }
        }
        char buffer [50];
        double Kp = 1.0;
        if(idat == 0) {
          Kp = PID_d.Kp;
        } else if (idat == 1) {
          Kp = PID_a.Kp;
        } else if (idat == 2) {
          Kp = PID_t.Kp;
        }
        sprintf (buffer, "P = %.3f", Kp);
        lv_label_set_text(pLabel, buffer);
      }
    }

    void btnmIEventHandler(lv_obj_t * obj, lv_event_t e){
      if(e == LV_EVENT_VALUE_CHANGED) {
        int i = lv_btnmatrix_get_active_btn(obj);
        int idat = lastDat;
        if(i == 0) {
          if(idat == 0) {
            PID_d.Ki -= .05;
          } else if (idat == 1) {
            PID_a.Ki -= .05;
          } else if (idat == 2) {
            PID_t.Ki -= .05;
          }
        } else if (i == 1) {
          if(idat == 0) {
            PID_d.Ki -= .01;
          } else if (idat == 1) {
            PID_a.Ki -= .01;
          } else if (idat == 2) {
            PID_t.Ki -= .01;
          }
        } else if (i == 2) {
          if(idat == 0) {
            PID_d.Ki -= .001;
          } else if (idat == 1) {
            PID_a.Ki -= .001;
          } else if (idat == 2) {
            PID_t.Ki -= .001;
          }
        } else if (i == 3) {
          if(idat == 0) {
            PID_d.Ki += .001;
          } else if (idat == 1) {
            PID_a.Ki += .001;
          } else if (idat == 2) {
            PID_t.Ki += .001;
          }
        } else if (i == 4) {
          if(idat == 0) {
            PID_d.Ki += .01;
          } else if (idat == 1) {
            PID_a.Ki += .01;
          } else if (idat == 2) {
            PID_t.Ki += .01;
          }
        } else if (i == 5) {
          if(idat == 0) {
            PID_d.Ki += .05;
          } else if (idat == 1) {
            PID_a.Ki += .05;
          } else if (idat == 2) {
            PID_t.Ki += .05;
          }
        }
        char buffer [50];
        double Ki = 0.0;
        if(idat == 0) {
          Ki = PID_d.Ki;
        } else if (idat == 1) {
          Ki = PID_a.Ki;
        } else if (idat == 2) {
          Ki = PID_t.Ki;
        }
        sprintf (buffer, "I = %.3f", Ki);
        lv_label_set_text(iLabel, buffer);
      }
    }

    void btnmDEventHandler(lv_obj_t * obj, lv_event_t e){
      if(e == LV_EVENT_VALUE_CHANGED) {
        int i = lv_btnmatrix_get_active_btn(obj);
        int idat = lastDat;
        if(i == 0) {
          if(idat == 0) {
            PID_d.Kd -= .05;
          } else if (idat == 1) {
            PID_a.Kd -= .05;
          } else if (idat == 2) {
            PID_t.Kd -= .05;
          }
        } else if (i == 1) {
          if(idat == 0) {
            PID_d.Kd -= .01;
          } else if (idat == 1) {
            PID_a.Kd -= .01;
          } else if (idat == 2) {
            PID_t.Kd -= .01;
          }
        } else if (i == 2) {
          if(idat == 0) {
            PID_d.Kd -= .001;
          } else if (idat == 1) {
            PID_a.Kd -= .001;
          } else if (idat == 2) {
            PID_t.Kd -= .001;
          }
        } else if (i == 3) {
          if(idat == 0) {
            PID_d.Kd += .001;
          } else if (idat == 1) {
            PID_a.Kd += .001;
          } else if (idat == 2) {
            PID_t.Kd += .001;
          }
        } else if (i == 4) {
          if(idat == 0) {
            PID_d.Kd += .01;
          } else if (idat == 1) {
            PID_a.Kd += .01;
          } else if (idat == 2) {
            PID_t.Kd += .01;
          }
        } else if (i == 5) {
          if(idat == 0) {
            PID_d.Kd += .05;
          } else if (idat == 1) {
            PID_a.Kd += .05;
          } else if (idat == 2) {
            PID_t.Kd += .05;
          }
        }
        char buffer [50];
        double Kd = 0.0;
        if(idat == 0) {
          Kd = PID_d.Kd;
        } else if (idat == 1) {
          Kd = PID_a.Kd;
        } else if (idat == 2) {
          Kd = PID_t.Kd;
        }
        sprintf (buffer, "D = %.3f", Kd);
        lv_label_set_text(dLabel, buffer);
      }
    }

    void btnmDATEventHandler(lv_obj_t * obj, lv_event_t e){
      if(e == LV_EVENT_VALUE_CHANGED) {
        //const char * txt = lv_btnmatrix_get_active_btn_text(obj);
        int i = lv_btnmatrix_get_active_btn(obj);
        lastDat = i;
        printf("btnmDATEventHandler %d\n",i);
        PIDFParameters u(1,0,0,0);
        if(i == 0) {
          u.Kp = PID_d.Kp;
          u.Ki = PID_d.Ki;
          u.Kd = PID_d.Kd;
          u.Kf = PID_d.Kf;
        } else if (i == 1) {
          u.Kp = PID_a.Kp;
          u.Ki = PID_a.Ki;
          u.Kd = PID_a.Kd;
          u.Kf = PID_a.Kf;
        } else if (i == 2) {
          u.Kp = PID_t.Kp;
          u.Ki = PID_t.Ki;
          u.Kd = PID_t.Kd;
          u.Kf = PID_t.Kf;
        }
        char buffer [50];
        sprintf (buffer, "P = %.3f", u.Kp);
        lv_label_set_text(pLabel, buffer);
        sprintf (buffer, "I = %.3f", u.Ki);
        lv_label_set_text(iLabel, buffer);
        sprintf (buffer, "D = %.3f", u.Kd);
        lv_label_set_text(dLabel, buffer);
      }
    }

    void pidTuningInit(){
      // Set the full screen background to Black
      static lv_style_t style_screen;
      // LV_STYLE_BG_COLOR
      lv_style_set_bg_color(&style_screen, LV_STATE_DEFAULT, LV_COLOR_BLACK);
      lv_obj_add_style(lv_scr_act(),LV_OBJ_PART_MAIN, &style_screen);

      static lv_style_t style1;
      static lv_style_t style2;
      static lv_style_t style3;
      lv_style_set_bg_color(&style1, LV_STATE_DEFAULT, LV_COLOR_BLACK);
      lv_style_set_bg_color(&style1, LV_STATE_PRESSED, LV_COLOR_GRAY);
      lv_style_set_bg_color(&style2, LV_STATE_CHECKED | LV_STATE_FOCUSED | LV_STATE_DEFAULT, LV_COLOR_PURPLE);
      lv_style_set_text_color(&style3, LV_STATE_DEFAULT, LV_COLOR_WHITE);

      // Create the P button matrix
      pBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
      lv_btnmatrix_set_map(pBtnm, btnmMapP);
      lv_obj_set_size(pBtnm, 320, 40);
      lv_obj_set_pos(pBtnm, 0, 0);
      lv_obj_align(pBtnm, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 10);
      lv_obj_set_event_cb(pBtnm, btnmPEventHandler);
      lv_obj_add_style(pBtnm,LV_BTNMATRIX_PART_BG, &style1);
      lv_obj_add_style(pBtnm,LV_BTNMATRIX_PART_BTN, &style2);
      
      pLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
      lv_label_set_text(pLabel, "P = 1.000"); //sets label text
      lv_obj_align(pLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 50); //set the position to center
      lv_obj_add_style(pLabel,LV_LABEL_PART_MAIN, &style3);

      // Create the I button matrix
      iBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
      lv_btnmatrix_set_map(iBtnm, btnmMapI);
      lv_obj_set_size(iBtnm, 320, 40);
      lv_obj_set_pos(iBtnm, 0, 0);
      lv_obj_align(iBtnm, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 70);
      lv_obj_set_event_cb(iBtnm, btnmIEventHandler);
      lv_obj_add_style(iBtnm,LV_BTNMATRIX_PART_BG, &style1);
      lv_obj_add_style(iBtnm,LV_BTNMATRIX_PART_BTN, &style2);
      
      iLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
      lv_label_set_text(iLabel, "I = 0.000"); //sets label text
      lv_obj_align(iLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 110); //set the position to center
      lv_obj_add_style(iLabel,LV_LABEL_PART_MAIN, &style3);

      // Create the I button matrix
      dBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
      lv_btnmatrix_set_map(dBtnm, btnmMapD);
      lv_obj_set_size(dBtnm, 320, 40);
      lv_obj_set_pos(dBtnm, 0, 0);
      lv_obj_align(dBtnm, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 130);
      lv_obj_set_event_cb(dBtnm, btnmDEventHandler);
      lv_obj_add_style(dBtnm,LV_BTNMATRIX_PART_BG, &style1);
      lv_obj_add_style(dBtnm,LV_BTNMATRIX_PART_BTN, &style2);
      
      dLabel = lv_label_create(lv_scr_act(), NULL); //create label and puts it on the screen
      lv_label_set_text(dLabel, "D = 0.000"); //sets label text
      lv_obj_align(dLabel, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 170); //set the position to center
      lv_obj_add_style(dLabel,LV_LABEL_PART_MAIN, &style3);

      // Create the DAT button matrix
      datBtnm = lv_btnmatrix_create(lv_scr_act(), NULL);
      lv_btnmatrix_set_map(datBtnm, btnmMapDAT);
      lv_obj_set_size(datBtnm, 100, 200);
      lv_obj_set_pos(datBtnm, 0, 0);
      lv_obj_align(datBtnm, NULL, LV_ALIGN_IN_TOP_LEFT, 340, 10);
      lv_obj_set_event_cb(datBtnm, btnmDATEventHandler);
      lv_obj_add_style(datBtnm,LV_BTNMATRIX_PART_BG, &style1);
      lv_obj_add_style(datBtnm,LV_BTNMATRIX_PART_BTN, &style2);

    }
#endif