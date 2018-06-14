#include <iostream>
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

int main(int argc, char* argv[])
{
	//TestMPI(argc, argv);
	TestTemplateFunctions();

	getchar();

	return 0;
}