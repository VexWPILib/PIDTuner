// Copyright (c) VexWPIApi contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the VexWPIApi BSD license file in the root directory of this project.

#include "PIDTunerUI.h"

namespace vpi {

  namespace ui {

    using namespace vpi;

    PIDFParameters PID_d(1.0,0,0,0);
    PIDFParameters PID_a(1.0,0,0,0);
    PIDFParameters PID_t(1.0,0,0,0);

    const char *btnmMapP[] = {"-.05", "-.01", "-.001", "+.001", "+.01", "+.05", "P", ""};
    const char *btnmMapI[] = {"-.05", "-.01", "-.001", "+.001", "+.01", "+.05", "I", ""};
    const char *btnmMapD[] = {"-.05", "-.01", "-.001", "+.001", "+.01", "+.05", "D", ""};
    const char *btnmMapDAT[] = {"D", "\n", "A", "\n", "T", ""};

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

  } // namespace ui
} // namespace vpi