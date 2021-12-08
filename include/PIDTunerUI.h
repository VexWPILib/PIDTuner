// Copyright (c) VexWPIApi contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the VexWPIApi BSD license file in the root directory of this project.

#pragma once

#include <stdio.h>

#include "vpi/pid/PIDController.h"

#pragma once

using namespace vpi;

extern PIDFParameters PID_d;
extern PIDFParameters PID_a;
extern PIDFParameters PID_t;

void initButtons();
void updatePIDValue(int datId, int pidId, double d);
void displayPIDValue(int datId);