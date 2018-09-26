#pragma once
#include <iostream>
#include <iomanip>
#include <cstdarg>

std::vector<double> VariadicFunction(const size_t n, const double d...)
{
	std::vector<double> res;

	va_list args;
	va_start(args, d);
	res.push_back(d);
	for (size_t i = 1; i < n; i++)
	{
		double x = va_arg(args, double);
		res.push_back(x);
	}
	va_end(args);

	return res;
}

void TestVariadicFunction()
{
	size_t num = 5;
	std::vector<double> v = VariadicFunction(num, 1.0, 3.0, 9.0, 5.0, 7.0);
	for (size_t i = 0; i < num; i++)
	{
		std::cout << v[i] << "\t";
	}
	std::cout << "\n";
}