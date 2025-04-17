#pragma once

#include "point.h"

constexpr int FIELD_SIZE  = 11;

int FIELD[FIELD_SIZE][FIELD_SIZE];

point START_POSITION = {0,1};
point END_POSITION = {FIELD_SIZE-1,FIELD_SIZE-2};