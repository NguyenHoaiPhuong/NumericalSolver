#pragma once
#include <iostream>
#include <vector>

#pragma region template function
/* Traditional template function 
Find max value between 2 inputs */
template <typename T>
T max(const T& a, const T& b)
{
	return (a > b) ? a : b;
}

/* Variadic Template function 
Find the sumation of the inputs */
template <typename T>
T sum(const T& a)
{
	return a;
}

template <typename T, typename...Args>
T sum(const T& a, const Args&...args)
{
	return a + (T)sum(args...);
}

template <typename...Args>
std::vector<size_t> sumation(const Args&...args)
{
	std::vector<size_t> res;
	for (auto h : { typeid(Args).hash_code()... })
	{
		res.push_back(h);
	}
	return res;
}

void TestVariadicTemplateFunction()
{
	std::cout << "Test Variadic Template Function:\n";
	std::cout << "sum(1, 2.3, 4) = " << sum(1, 2.3, 4) << std::endl;
	std::vector<size_t> res = sumation(1, 2.3, 4);
	std::cout << "sumation(1, 2.3, 4) = ";
	for (size_t i = 0; i < res.size(); i++)
	{
		std::cout << res[i] << " ";
	}
	std::cout << std::endl;
	getchar();
}
#pragma endregion





#pragma region Draw
class rectangle
{
public:
	void operator()()
	{
		std::cout << "RECTANGLE\n";
	}
};

class circle
{
public:
	void operator()()
	{
		std::cout << "CIRCLE\n";
	}
};

template <class I>
class Draw : public I
{
};

void TestDrawClass()
{
	Draw<rectangle>()();
	Draw<circle>()();
}
#pragma endregion


