// Various math utility functions, implemented in microcontroller friendly ways.

#pragma once

// absolute value
int absI(int value);
float absF(float value);

// Min/max
int maxI(int i1, int i2);
int minI(int i1, int i2);
float maxF(float i1, float i2);
float minF(float i1, float i2);

// Clamping
float clampF(float min, float clamp, float max);

// Returns if two floats are within 0.0001
bool isSameF(float a, float b);

// @brief Compute e^x using a 4th order taylor expansion centered at x=-1.  Provides
// bogus results outside the range -2 < x < 0.
float expf_taylor(float x);

// @brief Compute tan(theta) using a ratio of the Taylor series for sin and cos
// Valid for the range [0, pi/2 - 0.01]
float tanf_taylor(float theta);
