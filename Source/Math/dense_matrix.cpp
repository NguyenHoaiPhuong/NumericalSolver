#include "dense_matrix.h"

namespace math
{
	/* Constructor and Destructor */
	template<typename Float, typename Int>
	dense_matrix<Float, Int>::dense_matrix(const MPI_Comm comm)
		: template_matrix<Float, Int>(comm), matrix_(nullptr)
	{
	}

	template<typename Float, typename Int>
	dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, comm), matrix_(nullptr)
	{
		matrix_ = std::make_unique<Float[]>(this->row_size_ * this->col_size_);
	}

	template<typename Float, typename Int>
	dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const std::vector<Float>& mtx, const MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, comm), matrix_(nullptr)
	{
		matrix_ = std::make_unique<Float[]>(this->row_size_ * this->col_size_);
		Int i = 0;
		for (auto itr = mtx.begin(); itr != mtx.end(); itr++)
		{
			matrix_[i] = *itr;
			i += this->row_size_;
			if (i > this->row_size_*this->col_size_)
				i = i%this->row_size_ + 1;
		}
	}

	template<typename Float, typename Int>
	dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const Float value, const MPI_Comm comm)
	{
	}


}