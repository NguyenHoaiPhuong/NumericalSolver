#pragma once
#include "mpi.h"
#include "../Math/echo.h"

using namespace math;

void TestEchoFunc_Dense(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	int rank = 0;
	MPI_Comm_rank(comm, &rank);
	if (rank != __MASTER_RANK)
	{
		std::cout << "rank = " << rank << std::endl;
		return;
	}

	dense_matrix<double, int> akagi;
	{
		int nrows = 5;
		int ncols = 6;
		std::unique_ptr<double[]> mtx = std::make_unique<double[]>(nrows * ncols);
		for (size_t i = 0; i < nrows * ncols; i++)
		{
			mtx[i] = (double)(i + 1);
		}
		akagi = dense_matrix<double, int>(nrows, ncols, mtx.get(), ROW, NONE, comm);
		echo(akagi);
	}
	{
		int nrows = 5;
		int ncols = 6;
		std::unique_ptr<double[]> mtx = std::make_unique<double[]>(nrows * ncols);
		for (size_t i = 0; i < nrows * ncols; i++)
		{
			mtx[i] = (double)(i + 1);
		}
		akagi = dense_matrix<double, int>(nrows, ncols, mtx.get(), COLUMN, NONE, comm);
		echo(akagi);
	}
	{
		int nrows = 5;
		//int ncols = 5;
		int msize = (int)(0.5 * nrows * (nrows - 1)) + nrows;
		std::unique_ptr<double[]> mtx = std::make_unique<double[]>(msize);
		for (size_t i = 0; i < msize; i++)
		{
			mtx[i] = (double)(i + 1);
		}
		akagi = dense_matrix<double, int>(nrows, nrows, mtx.get(), COLUMN, SYMMETRIC, comm);
		echo(akagi);
	}
	{
		int nrows = 5;
		//int ncols = 5;
		int msize = (int)(0.5 * nrows * (nrows - 1)) + nrows;
		std::unique_ptr<double[]> mtx = std::make_unique<double[]>(msize);
		for (size_t i = 0; i < msize; i++)
		{
			mtx[i] = (double)(i + 1);
		}
		akagi = dense_matrix<double, int>(nrows, nrows, mtx.get(), ROW, SYMMETRIC, comm);
		echo(akagi);
	}
	std::cout << std::endl;

	MPI_Finalize();
}

void TestFileEchoFunc_Dense(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	int rank = 0;
	MPI_Comm_rank(comm, &rank);
	if (rank != __MASTER_RANK)
		return;

	{
		dense_matrix<double, int> akagi;
		int nrows = 5;
		int ncols = 6;
		std::unique_ptr<double[]> mtx = std::make_unique<double[]>(nrows * ncols);
		for (size_t i = 0; i < nrows * ncols; i++)
		{
			mtx[i] = (double)(i + 1);
		}
		akagi = dense_matrix<double, int>(nrows, ncols, mtx.get(), ROW, NONE, comm);

		std::ofstream file;
		file.open("Akagi.csv");
		echo(akagi, "Matrix Akagi", file);
		file.close();
	}
	{
		dense_matrix<double, int> yushin;
		int nrows = 5;
		int ncols = 6;
		double mtx[] = {  1,  2,  3,  4,  5,
						  6,  7,  8,  9, 10,
						 11, 12, 13, 14, 15,
						 16, 17, 18, 19, 20,
						 21, 22, 23, 24, 25,
						 26, 27, 28, 29, 30 };
		yushin = dense_matrix<double, int>(nrows, ncols, mtx, COLUMN, NONE, comm);

		std::ofstream file;
		file.open("Yushin.csv");
		echo(yushin, "Matrix Yushin", file);
		file.close();
	}
	{
		dense_matrix<double, int> mogami;
		int nrows = 5;
		double mtx[] = {  1,
						  2,  3,
						  4,  5,  6,
						  7,  8,  9, 10,
						 11, 12, 13, 14, 15 };
		mogami = dense_matrix<double, int>(nrows, nrows, mtx, ROW, SYMMETRIC, comm);

		std::ofstream file;
		file.open("Mogami.csv");
		echo(mogami, "Mogami Matrix", file);
		file.close();
	}
	{
		dense_matrix<double, int> krishima;
		int nrows = 5;
		double mtx[] = {  1,  2,  3,  4,  5,
							  6,  7,  8,  9, 
								 10, 11, 12,
									 13, 14,
										 15 };
		krishima = dense_matrix<double, int>(nrows, nrows, mtx, COLUMN, SYMMETRIC, comm);

		std::ofstream file;
		file.open("Krishima.csv");
		echo(krishima, "Krishima Matrix", file);
		file.close();
	}
	
	MPI_Finalize();
}

void TestEchoFunc_Perm(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	int rank = 0;
	MPI_Comm_rank(comm, &rank);
	if (rank != __MASTER_RANK)
	{
		std::cout << "rank = " << rank << std::endl;
		return;
	}

	permutation_matrix<int> akagi;
	{
		int msize = 5;

		std::vector<std::array<int, 2>> pos = { {0, 1}, {1, 2}, {2, 3}, {3, 0}, {4, 4} };

		akagi = permutation_matrix<int>(msize, pos, ROW, NONE, comm);
		echo(akagi);
	}
	{
		int msize = 5;

		std::vector<std::array<int, 2>> pos = { { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },{ 4, 4 } };

		akagi = permutation_matrix<int>(msize, pos, COLUMN, NONE, comm);
		echo(akagi);
	}
	
	std::cout << std::endl;

	MPI_Finalize();
}

void TestFileEchoFunc_Perm(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	int rank = 0;
	MPI_Comm_rank(comm, &rank);
	if (rank != __MASTER_RANK)
		return;

	{
		int msize = 5;
		std::vector<std::array<int, 2>> pos = { { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },{ 4, 4 } };
		permutation_matrix<int> akagi = permutation_matrix<int>(msize, pos, ROW, NONE, comm);

		std::ofstream file;
		file.open("Akagi.csv");
		echo(akagi, "Matrix Akagi", file);
		file.close();
	}
	{
		int msize = 5;
		std::vector<std::array<int, 2>> pos = { { 0, 1 },{ 1, 2 },{ 2, 3 },{ 3, 0 },{ 4, 4 } };
		permutation_matrix<int> akagi = permutation_matrix<int>(msize, pos, COLUMN, NONE, comm);

		std::ofstream file;
		file.open("Yushin.csv");
		echo(akagi, "Matrix Yushin", file);
		file.close();
	}

	MPI_Finalize();
}