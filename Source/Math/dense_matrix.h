#pragma once
#include <vector>
#include "base_matrix.h"

namespace math
{
	template<typename Float, typename Int>
	class dense_matrix : public template_matrix<Float, Int>
	{
	protected:
		std::unique_ptr<Float[]> matrix_;
	public:
		/* Constructor and Destructor */
		dense_matrix(const MPI_Comm comm = MPI_COMM_WORLD);
		dense_matrix(const Int rows, const Int cols, const MPI_Comm comm = MPI_COMM_WORLD);
		// Input data were stored in row - order std::vector<Float> mtx
		dense_matrix(const Int rows, const Int cols, const std::vector<Float>& mtx, const MPI_Comm comm = MPI_COMM_WORLD);
		// Equal value is applied to each member of the matrix
		dense_matrix(const Int rows, const Int cols, const Float value, const MPI_Comm comm = MPI_COMM_WORLD);
		// Input data were stored in column - order mtx
		dense_matrix(const Int rows, const Int cols, const Float* mtx, const MPI_Comm comm = MPI_COMM_WORLD);
		// Input data were stored in column - order mtx
		dense_matrix(const Int rows, const Int cols, std::unique_ptr<Float[]>&& mtx, MPI_Comm comm = MPI_COMM_WORLD);
		// Move constructor
		dense_matrix(dense_matrix&& other);
		// Copy constructor
		dense_matrix(const dense_matrix& other);

		dense_matrix& operator=(dense_matrix&& other);
		dense_matrix& operator=(const dense_matrix& other);
	};
	
}