// Copyright (c) VexWPIApi contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the VexWPIApi BSD license file in the root directory of this project.

#pragma once

#include <stdio.h>

#include "v5lvgl.h"
#include "lv_conf.h"
#include "vpi/pid/PIDController.h"

#pragma once

namespace vpi {
  namespace ui {
    extern PIDFParameters PID_d;
    extern PIDFParameters PID_a;
    extern PIDFParameters PID_t;

    void pidTuningInit();
  } // ui
} // vpi
