#pragma once
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
