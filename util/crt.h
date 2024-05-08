#pragma once

#define M_PI       3.14159265358979323846   // pi

namespace crt {
	float c_powf(float base, float exponent) {
		float result = 1;
		for (int i = 0; i < exponent; i++) {
			result *= base;
		}
		return result;
	}

	double c_factorial(int n) {
		double result = 1.0;
		for (int i = 2; i <= n; ++i) {
			result *= i;
		}
		return result;
	}

	double c_power(double base, int exponent) {
		double result = 1.0;
		for (int i = 0; i < exponent; ++i) {
			result *= base;
		}
		return result;
	}

	double c_sin(double angle) {
		double sinValue = 0.0;
		int iterations = 10;

		int sign = 1;
		for (int n = 1; n <= iterations; ++n) {
			double term = c_power(angle, 2 * n - 1) / c_factorial(2 * n - 1);
			sinValue += sign * term;
			sign *= -1;
		}

		return sinValue;
	}

	double c_cos(double angle) {
		double cosValue = 0.0;
		int iterations = 10;

		int sign = 1;
		for (int n = 0; n < iterations; ++n) {
			double term = c_power(angle, 2 * n) / c_factorial(2 * n);
			cosValue += sign * term;
			sign *= -1;
		}

		return cosValue;
	}

	static double 	sin_off_tbl[] = { 0.0, -M_PI / 2., 0, -M_PI / 2. };
	static double 	sin_sign_tbl[] = { 1,-1,-1,1 };

	static double 	cos_off_tbl[] = { 0.0, -M_PI / 2., 0, -M_PI / 2. };
	static double 	cos_sign_tbl[] = { 1,-1,-1,1 };

	double sinddd(double x)
	{
		int quadrant;
		double x2, result;

		/* Calculate the quadrant */
		quadrant = (int)(x * (2. / M_PI));

		/* Get offset inside quadrant */
		x = x - quadrant * (M_PI / 2.);

		/* Normalize quadrant to [0..3] */
		quadrant = (quadrant - 1) & 0x3;

		/* Fixup value for the generic function */
		x += sin_off_tbl[quadrant];

		/* Calculate the negative of the square of x */
		x2 = -(x * x);

		result = 0;

#if (PRECISION >= 10)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18 * 19 * 20);
		result *= x2;
#endif
#if (PRECISION >= 9)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18);
		result *= x2;
#endif
#if (PRECISION >= 8)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16);
		result *= x2;
#endif
#if (PRECISION >= 7)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14);
		result *= x2;
#endif
#if (PRECISION >= 6)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12);
		result *= x2;
#endif
#if (PRECISION >= 5)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
		result *= x2;
#endif
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8);
		result *= x2;

		result += 1. / (1. * 2 * 3 * 4 * 5 * 6);
		result *= x2;

		result += 1. / (1. * 2 * 3 * 4);
		result *= x2;

		result += 1. / (1. * 2);
		result *= x2;

		result += 1;

		/* Apply correct sign */
		result *= sin_sign_tbl[quadrant];

		return result;
	}

	double cosddd(double x)
	{

		int quadrant;
		double x2, result;

		/* Calculate the quadrant */
		quadrant = (int)(x * (2. / M_PI));

		/* Get offset inside quadrant */
		x = x - quadrant * (M_PI / 2.);

		/* Normalize quadrant to [0..3] */
		quadrant = quadrant & 0x3;

		/* Fixup value for the generic function */
		x += cos_off_tbl[quadrant];

		/* Calculate the negative of the square of x */
		x2 = -(x * x);

		result = 0;

#if (PRECISION >= 10)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18 * 19 * 20);
		result *= x2;
#endif
#if (PRECISION >= 9)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16 * 17 * 18);
		result *= x2;
#endif
#if (PRECISION >= 8)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14 * 15 * 16);
		result *= x2;
#endif
#if (PRECISION >= 7)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12 * 13 * 14);
		result *= x2;
#endif
#if (PRECISION >= 6)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11 * 12);
		result *= x2;
#endif
#if (PRECISION >= 5)
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10);
		result *= x2;
#endif
		result += 1. / (1. * 2 * 3 * 4 * 5 * 6 * 7 * 8);
		result *= x2;

		result += 1. / (1. * 2 * 3 * 4 * 5 * 6);
		result *= x2;

		result += 1. / (1. * 2 * 3 * 4);
		result *= x2;

		result += 1. / (1. * 2);
		result *= x2;

		result += 1;

		result *= cos_sign_tbl[quadrant];

		return result;
	}

	float c_sinf(float _X)
	{
		return float(sinddd((double)_X));
	}

	float c_cosf(float _X)
	{
		return float(cosddd((double)_X));
	}

	float c_tanf(float _X)
	{
		return (c_sinf(_X) / c_cosf(_X));
	}

	double c_atan(double x) {
		if (x == 0.0) {
			return 0.0;
		}

		bool isNegative = false;
		if (x < 0.0) {
			x = -x;
			isNegative = true;
		}

		double result = x;
		double term = x;
		double divisor = 1.0;
		double divisorSquared = 1.0;

		for (int i = 1; i < 1000; i++) {
			divisorSquared += 2.0;
			divisor *= divisorSquared;

			term *= -x * x;
			double currentTerm = term / divisor;

			result += currentTerm;

			if (currentTerm == 0.0) {
				break;
			}
		}

		if (isNegative) {
			result = -result;
		}

		return result;
	}

	int c_fabs(int _X)
	{
		int s = _X >> 31;
		return (_X ^ s) - s;
	}

	double c_sqrtf(double Number)
	{
		if (Number < 0)
		{
			return (-(double)(((double)(1e+300 * 1e+300)) * 0.0));
		}

		if (Number <= 1.192092896e-07)
		{
			return 0.0;
		}

		double MySqrt = Number;

		while (c_fabs(MySqrt - Number / MySqrt) > 1.192092896e-07 * MySqrt)
		{
			MySqrt = (MySqrt + Number / MySqrt) / 2.0;
		}

		return MySqrt;
	}

	double c_atan2(double y, double x) {
		if (x == 0.0) {
			if (y > 0.0) {
				return 3.14159265358979323846 / 2.0;
			}
			else if (y < 0.0) {
				return -3.14159265358979323846 / 2.0;
			}
			else {
				return 0.0;
			}
		}

		double result = c_atan(y / x);

		if (x < 0.0) {
			result += (y >= 0.0) ? 3.14159265358979323846 : -3.14159265358979323846;
		}

		return result;
	}

	double c_acos(double x) {
		if (x > 1.0 || x < -1.0) {
			return 0.0;
		}

		double result = c_atan2(c_sqrtf(1 - x * x), x);
		return result;
	}
}

namespace crt {
	__forceinline wchar_t* to_string(int n)
	{
		int m = n;
		wchar_t s[100]; //max
		wchar_t ss[100]; //max
		int i = 0, j = 0;
		if (n < 0)
		{
			m = 0 - m;
			j = 1;
			ss[0] = '-';
		}
		while (m > 0)
		{
			s[i++] = m % 10 + '0';
			m /= 10;
		}
		s[i] = '\0';
		i = i - 1;
		while (i >= 0)
		{
			ss[j++] = s[i--];
		}
		ss[j] = '\0';
		return ss;
	}

	wchar_t* c_wcscpy(wchar_t* dest, const wchar_t* src)
	{
		wchar_t* dest_iter = dest;
		while (*src)
		{
			*dest_iter = *src;
			++dest_iter;
			++src;
		}
		*dest_iter = L'\0';
		return dest;
	}

	wchar_t* c_wcscat(wchar_t* dest, const wchar_t* src)
	{
		wchar_t* dest_iter = dest;
		while (*dest_iter)
		{
			++dest_iter;
		}

		while (*src)
		{
			*dest_iter = *src;
			++dest_iter;
			++src;
		}
		*dest_iter = L'\0';
		return dest;
	}

	int c_strlen(const char* string)
	{
		int cnt = 0;
		if (string)
		{
			for (; *string != 0; ++string) ++cnt;
		}
		return cnt;
	}
}