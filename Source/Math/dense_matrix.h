#pragma once
#include <memory>
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
		// Input data were stored in row - order
		dense_matrix(const Int rows, const Int cols, const std::vector<Float>& mtx, const MPI_Comm comm = MPI_COMM_WORLD);
		dense_matrix(const Int rows, const Int cols, const Float value, const MPI_Comm comm = MPI_COMM_WORLD);
	};
	
}