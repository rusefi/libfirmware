// Various math utility functions, implemented in microcontroller friendly ways.

#pragma once

#include <rusefi/expected.h>

#include <cstddef>

// absolute value
constexpr int absI(int value) {
                   	return value > 0 ? value : -value;
                   }
constexpr float absF(float value) {
                       	return value > 0 ? value : -value;
                       }

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

struct NewtonsMethodSolver
{
	// Solve for a value of x such that fx(x)=0
	// x0 is the initial guess
	// deltaX controls when to stop - when abs((estimate N) - (estimate N-1)) < deltaX, stop calculation.
	// Returns unexpected if failed to converge
	expected<float> solve(float x0, float deltaX, size_t maxIteration = 20);

	// Function for which we want to find a root 0 = fx(x)
	virtual float fx(float x) = 0;

	// First derivative of fx(x)
	virtual float dfx(float x) = 0;
};
