#include "mpi.h"
#include "../Math/echo.h"

void TestAddFuncAB_nosymm_nosymm_row_row(const MPI_Comm& comm, std::ofstream& file)
{
	file << "NOSYMM - NOSYMM, ROW - ROW:\n";
	
	int nrows = 6;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25,
						26, 27, 28, 29, 30 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25,
						26, 27, 28, 29, 30 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, ROW, NONE, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, ROW, NONE, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);
	
	file << "\n\n\n";
}

void TestAddFuncAB_nosymm_nosymm_row_col(const MPI_Comm& comm, std::ofstream& file)
{
	file << "NOSYMM - NOSYMM, ROW - COL:\n";

	int nrows = 6;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25,
						26, 27, 28, 29, 30 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25,
						26, 27, 28, 29, 30 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, ROW, NONE, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, COLUMN, NONE, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_nosymm_nosymm_col_row(const MPI_Comm& comm, std::ofstream& file)
{
	file << "NOSYMM - NOSYMM, COL - ROW:\n";
	
	int nrows = 6;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25,
						26, 27, 28, 29, 30 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25,
						26, 27, 28, 29, 30 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, COLUMN, NONE, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, ROW, NONE, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_nosymm_nosymm_col_col(const MPI_Comm& comm, std::ofstream& file)
{
	file << "NOSYMM - NOSYMM, COL - COL:\n";

	int nrows = 6;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25,
						26, 27, 28, 29, 30 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25,
						26, 27, 28, 29, 30 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, COLUMN, NONE, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, COLUMN, NONE, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_nosymm_symm_row_row(const MPI_Comm& comm, std::ofstream& file)
{
	file << "NOSYMM - SYMM, ROW - ROW:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, ROW, NONE, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, ROW, SYMMETRIC, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_nosymm_symm_col_col(const MPI_Comm& comm, std::ofstream& file)
{
	file << "NOSYMM - SYMM, COL - COL:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, COLUMN, NONE, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, COLUMN, SYMMETRIC, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_nosymm_symm_row_col(const MPI_Comm& comm, std::ofstream& file)
{
	file << "NOSYMM - SYMM, ROW - COL:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, ROW, NONE, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, COLUMN, SYMMETRIC, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_nosymm_symm_col_row(const MPI_Comm& comm, std::ofstream& file)
{
	file << "NOSYMM - SYMM, COL - ROW:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, COLUMN, NONE, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, ROW, SYMMETRIC, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_symm_nosymm_row_row(const MPI_Comm& comm, std::ofstream& file)
{
	file << "SYMM - NOSYMM, ROW - ROW:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, ROW, SYMMETRIC, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, ROW, NONE, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_symm_nosymm_col_col(const MPI_Comm& comm, std::ofstream& file)
{
	file << "SYMM - NOSYMM, COL - COL:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, COLUMN, SYMMETRIC, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, COLUMN, NONE, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_symm_nosymm_row_col(const MPI_Comm& comm, std::ofstream& file)
{
	file << "SYMM - NOSYMM, ROW - COL:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, ROW, SYMMETRIC, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, COLUMN, NONE, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_symm_nosymm_col_row(const MPI_Comm& comm, std::ofstream& file)
{
	file << "SYMM - NOSYMM, COL - ROW:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, COLUMN, SYMMETRIC, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, ROW, NONE, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_symm_symm_row_row(const MPI_Comm& comm, std::ofstream& file)
{
	file << "SYMM - SYMM, ROW - ROW:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, ROW, SYMMETRIC, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, ROW, SYMMETRIC, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_symm_symm_col_col(const MPI_Comm& comm, std::ofstream& file)
{
	file << "SYMM - SYMM, COL - COL:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, COLUMN, SYMMETRIC, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, COLUMN, SYMMETRIC, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_symm_symm_row_col(const MPI_Comm& comm, std::ofstream& file)
{
	file << "SYMM - SYMM, ROW - COL:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, ROW, SYMMETRIC, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, COLUMN, SYMMETRIC, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB_symm_symm_col_row(const MPI_Comm& comm, std::ofstream& file)
{
	file << "SYMM - SYMM, COL - ROW:\n";

	int nrows = 5;
	int ncols = 5;
	double mtx1[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	double mtx2[] = {	1,	2,  3,  4,  5,
						6,	7,  8,  9,	10,
						11, 12, 13, 14, 15,
						16, 17, 18, 19, 20,
						21, 22, 23, 24, 25 };
	dense_matrix<double, int> a = dense_matrix<double, int>(nrows, ncols, mtx1, COLUMN, SYMMETRIC, comm);
	echo(a, "Matrix A", file);
	dense_matrix<double, int> b = dense_matrix<double, int>(nrows, ncols, mtx2, ROW, SYMMETRIC, comm);
	echo(b, "Matrix B", file);

	a += b;
	echo(a, "Matrix A = A + B", file);

	file << "\n\n\n";
}

void TestAddFuncAB(int argc, char* argv[])
{
	MPI_Init(&argc, &argv);
	MPI_Comm comm = MPI_COMM_WORLD;
	int rank = 0;
	MPI_Comm_rank(comm, &rank);
	if (rank != __MASTER_RANK)
		return;

	std::ofstream file;
	file.open("TestAddFunc.csv");

	// NOSYMM - NOSYMM, ROW - ROW
	TestAddFuncAB_nosymm_nosymm_row_row(comm, file);

	// NOSYMM - NOSYMM, ROW - COL
	TestAddFuncAB_nosymm_nosymm_row_col(comm, file);

	// NOSYMM - NOSYMM, COL - ROW
	TestAddFuncAB_nosymm_nosymm_col_row(comm, file);

	// NOSYMM - NOSYMM, COL - COL
	TestAddFuncAB_nosymm_nosymm_col_col(comm, file);

	// NOSYMM - NOSYMM, ROW - ROW
	TestAddFuncAB_nosymm_symm_row_row(comm, file);
	
	// NOSYMM - SYMM, COL - COL
	TestAddFuncAB_nosymm_symm_col_col(comm, file);
	
	// NOSYMM - SYMM, ROW - COL
	TestAddFuncAB_nosymm_symm_row_col(comm, file);

	// NOSYMM - SYMM, COL - ROW
	TestAddFuncAB_nosymm_symm_col_row(comm, file);

	// SYMM - NOSYMM, ROW - ROW
	TestAddFuncAB_symm_nosymm_row_row(comm, file);

	// SYMM - NOSYMM, COL - COL
	TestAddFuncAB_symm_nosymm_col_col(comm, file);

	// SYMM - NOSYMM, ROW - COL
	TestAddFuncAB_symm_nosymm_row_col(comm, file);

	// SYMM - NOSYMM, COL - ROW
	TestAddFuncAB_symm_nosymm_col_row(comm, file);

	// SYMM - SYMM, ROW - ROW
	TestAddFuncAB_symm_symm_row_row(comm, file);

	// SYMM - SYMM, COL - COL
	TestAddFuncAB_symm_symm_col_col(comm, file);

	// SYMM - SYMM, ROW - COL
	TestAddFuncAB_symm_symm_row_col(comm, file);

	// SYMM - SYMM, COL - ROW
	TestAddFuncAB_symm_symm_col_row(comm, file);

	file.close();

	MPI_Finalize();
}