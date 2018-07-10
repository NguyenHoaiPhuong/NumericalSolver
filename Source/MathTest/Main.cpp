#include <iostream>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <vector>
#include <cstdarg>
#include "mpi.h"

void TestMPI(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	int rank;
	MPI_Comm_rank(comm, &rank);
	std::cout << "Hello world from rank #" << rank << "\n";
	MPI_Finalize();
}

#pragma region Template functions
/* Traditional template function*/
template <typename I>
I max(const I& a, const I& b)
{
	return (a > b) ? a : b;
}

/* Parameter pack (variadic) template functions */
template <typename T>
double sum(const T& t)
{
	return t;
}
template<typename T, typename...Args>
double sum(const T& t, const Args&... args)
{
	return t + sum(args...);
}

template <typename T>
double min(const T& t)
{
	return t;
}
template <typename T, typename...Args>
double min(const T& t, const Args&...args)
{
	if (t < min(args...))
		return t;
	else
		return min(args...);
}

/* Testing template functions */
void TestTemplateFunctions()
{
	std::cout << "Test traditional template function:\n";
	std::cout << "max<double>(5, 6) = " << max<double>(5, 6) << "\n";
	std::cout << "Test variadic template function sum:\n";
	std::cout << "sum(1, 2, 3, 4, 5.123) = " << sum(1, 2, 3, 4, 5.123) << "\n";
	std::cout << "Test variadic template function min:\n";
	std::cout << "min(1.123, 2, 3, 4, 5.123) = " << min(1.123, (int)2, (long)3, 4, 5) << "\n";
}
#pragma endregion

#pragma region TestHex2String
std::string to_hex(size_t i)
{
	std::ostringstream oss;
	oss << std::setfill('0') << std::setw(16) << std::hex << i;
	return oss.str();
}
void TestHex2String()
{
	std::string str = to_hex(16);
	std::cout << str << std::endl;
}
#pragma endregion

#pragma region TestTypeInfo
template<typename T>
struct hash_by_type
{
	std::string operator()()
	{
		return to_hex(typeid(T).hash_code());
	}
};
template<typename T>
std::string hash_by_variable(T& t)
{
	return to_hex(typeid(t).hash_code());
}

struct A{};
struct B : public A {};
struct C : public A {};

using TypeInfoRef = std::reference_wrapper<const std::type_info>;
struct Hasher {
	std::size_t operator()(TypeInfoRef code) const
	{
		return code.get().hash_code();
	}
};
struct EqualTo {
	bool operator()(TypeInfoRef lhs, TypeInfoRef rhs) const
	{
		return lhs.get() == rhs.get();
	}
};
void TestTypeInfo()
{	
	std::unordered_map<TypeInfoRef, std::string, Hasher, EqualTo> typenames;
	typenames[typeid(int)] = "int";
	typenames[typeid(double)] = "double";
	typenames[typeid(float)] = "float";
	typenames[typeid(A)] = "A";
	typenames[typeid(B)] = "B";
	typenames[typeid(C)] = "C";

	int i;
	std::cout << typeid(i).name() << std::endl;
	std::cout << "Type of i is " << typenames[typeid(i)] << std::endl;
	std::cout << hash_by_type<int>()() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	double d;
	std::cout << typeid(d).name() << std::endl;
	std::cout << "Type of d is " << typenames[typeid(d)] << std::endl;
	std::cout << hash_by_type<double>()() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	float f;
	std::cout << typeid(f).name() << std::endl;
	std::cout << "Type of f is " << typenames[typeid(f)] << std::endl;
	std::cout << hash_by_type<float>()() << std::endl;
	std::cout << "---------------------------------" << std::endl;

	A a;
	std::cout << typeid(a).name() << std::endl;
	std::cout << "Type of a is " << typenames[typeid(a)] << std::endl;
	std::cout << hash_by_variable<A>(a) << std::endl;
	std::cout << "---------------------------------" << std::endl;

	A* b = new B();
	std::cout << typeid(*b).name() << std::endl;
	std::cout << "Type of b is " << typenames[typeid(*b)] << std::endl;
	std::cout << hash_by_variable<A>(*b) << std::endl;
	std::cout << "---------------------------------" << std::endl;

	A* c = new C();
	std::cout << typeid(*c).name() << std::endl;
	std::cout << "Type of c is " << typenames[typeid(*c)] << std::endl;
	std::cout << hash_by_variable<A>(*c) << std::endl;
	std::cout << "---------------------------------" << std::endl;
}
#pragma endregion

#pragma region TestVariadicFunction
bool IsDoubleDefault(const double& x)
{
	return (x == DBL_MAX || x == DBL_MIN) ? true : false;
}
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
#pragma endregion


int main(int argc, char* argv[])
{
	//TestMPI(argc, argv);
	//TestTemplateFunctions();
	//TestHex2String();
	//TestTypeInfo();
	TestVariadicFunction();

	getchar();

	return 0;
}