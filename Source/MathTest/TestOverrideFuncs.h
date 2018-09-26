#pragma once

#include <iostream>
#include <vector>

/* If Data Type = int, do sumation */
int Func(std::vector<int> v)
{
	int res = 0;
	for (size_t i = 0; i < v.size(); i++)
	{
		res += v[i];
	}
	return res;
}

/* If Data Type = int, do multiplication */
double Func(std::vector<double> v)
{
	double res = 1;
	for (size_t i = 0; i < v.size(); i++)
	{
		res *= v[i];
	}
	return res;
}

void TestSumFunc()
{
	std::vector<int> iv = { 1,2 };
	std::cout << "Type = int:\n";
	std::cout << Func(iv) << std::endl;

	std::vector<double> dv = { 3,4 };
	std::cout << "Type = double:\n";
	std::cout << Func(dv) << std::endl;

	// Below function will cause error (No overload)
	/*std::vector<long> lv = { 5,6 };
	std::cout << "Type = long:\n";
	std::cout << Func(lv) << std::endl;*/
}