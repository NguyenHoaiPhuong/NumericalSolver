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
		: template_matrix<Float, Int>(rows, cols, comm), matrix_(nullptr)
	{
		msize ms = this->row_size_*this->col_size_;
		matrix_ = std::make_unique<Float[]>(ms);
		std::fill_n(matrix_.get(), ms, value);
	}

	template<typename Float, typename Int>
	dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const Float * mtx, const MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, comm)
	{
		this->matrix_ = std::make_unique<Float[]>(this->row_size_*this->col_size_);
		memcpy(this->matrix_.get(), mtx, this->row_size_*this->col_size_ * sizeof(Float));
	}

	template<typename Float, typename Int>
	dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, std::unique_ptr<Float[]>&& mtx, MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, comm), matrix_(std::move(mtx))
	{
	}

	// Move constructor
	template<typename Float, typename Int>
	dense_matrix<Float, Int>::dense_matrix(dense_matrix && other)
		: template_matrix<Float, Int>(other), matrix_(std::move(other.matrix_))
	{
	}

	// Copy constructor
	template<typename Float, typename Int>
	dense_matrix<Float, Int>::dense_matrix(const dense_matrix & other)
		: template_matrix<Float, Int>(other)
	{
		int mpi_rank;
		MPI_Comm_rank(other.comm_, &mpi_rank);
		if (mpi_rank != 0)	// 0: Master rank
			return;
		msize ms = row_size_ * col_size_;
		matrix_ = std::make_unique<Float[]>(ms);
		std::copy_n(other.matrix_.get(), ms, matrix_.get());
	}

	template<typename Float, typename Int>
	dense_matrix & dense_matrix<Float, Int>::operator=(dense_matrix && other)
	{
		this->comm_ = other.comm_;
		this->row_size_ = other.row_size_;
		this->col_size_ = other.col_size_;
		this->matrix_ = std::move(other.matrix_);
		other.row_size_ = 0;
		other.col_size_ = 0;

		return *this;
	}
	template<typename Float, typename Int>
	dense_matrix & dense_matrix<Float, Int>::operator=(const dense_matrix & other)
	{
		this->comm_ = other.comm_;
		this->row_size_ = other.row_size_;
		this->col_size_ = other.col_size_;
		
		msize ms = this->row_size_ * this->col_size_;
		this->matrix_ = std::make_unique<Float[]>(ms);
		std::copy_n(other.matrix_.get(), ms, matrix_.get());

		return *this;
	}
}