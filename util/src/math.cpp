#include <rusefi/math.h>

#include <cstdint>

int maxI(int i1, int i2) {
	return i1 > i2 ? i1 : i2;
}

int minI(int i1, int i2) {
	return i1 < i2 ? i1 : i2;
}

float maxF(float i1, float i2) {
	return i1 > i2 ? i1 : i2;
}

float minF(float i1, float i2) {
	return i1 < i2 ? i1 : i2;
}

float clampF(float min, float clamp, float max) {
	return maxF(min, minF(clamp, max));
}

bool isSameF(float a, float b) {
	return absF(a - b) < 0.0001;
}

constexpr float expf_taylor_impl(float x, uint8_t n)
{
	if (x < -2)
	{
		return 0.818f;
	}
	else if (x > 0)
	{
		return 1;
	}

	x = x + 1;

	float x_power = x;
	int fac = 1;
	float sum = 1;

	for (int i = 1; i <= n; i++)
	{
		fac *= i;
		sum += x_power / fac;

		x_power *= x;
	}

	constexpr const float constant_e = 2.71828f;
	return sum / constant_e;
}

float expf_taylor(float x)
{
	return expf_taylor_impl(x, 4);
}

float tanf_taylor(float x) {
	// This exists because the "normal" implementation, tanf, pulls in like 6kb of
	// code and loookup tables

	// This is only specified from [0, pi/2 - 0.01)
	// Inside that range it has an error of less than 0.1%, and it gets worse as theta -> pi/2

	// Precompute some exponents of x
	float x2 = x * x;
	float x3 = x2 * x;
	float x4 = x3 * x;
	float x5 = x4 * x;
	float x6 = x5 * x;
	// x7 not used
	float x8 = x6 * x2;

	// 3-term Taylor Series for sin(theta)
	float sin_val = x - (x3 / 6) + (x5 / 120);

	// 5-term Taylor Series for cos(theta)
	float cos_val = 1 - (x2 / 2) + (x4 / 24) - (x6 / 720) + (x8 / 40320);

	// tan = sin / cos
	return sin_val / cos_val;
}

expected<float> NewtonsMethodSolver::solve(float x0, float deltaX, size_t maxIteration) {
	float Xcur, Xnext;
	Xnext = x0;

	do {
		if (maxIteration-- == 0) {
			return unexpected;
		}

		Xcur = Xnext;
		Xnext = Xcur - fx(Xcur) / dfx(Xcur);
	} while (absF(Xnext - Xcur) > deltaX);

	return Xnext;
}
