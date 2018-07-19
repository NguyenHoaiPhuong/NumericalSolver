#pragma once
#include "base_matrix.h"

/* Dense Matrix Declareation */
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
		dense_matrix(const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const Int rows, const Int cols, const std::vector<Float>& mtx, const MPI_Comm comm = MPI_COMM_WORLD);

		// Equal value is applied to each member of the matrix
		dense_matrix(const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const Int rows, const Int cols, const Float value, const MPI_Comm comm = MPI_COMM_WORLD);

		// Input data were stored in column - order mtx
		dense_matrix(const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const Int rows, const Int cols, const Float* mtx, const MPI_Comm comm = MPI_COMM_WORLD);

		// Input data were stored in column - order mtx
		dense_matrix(const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const Int rows, const Int cols, std::unique_ptr<Float[]>&& mtx, MPI_Comm comm = MPI_COMM_WORLD);

		// Move constructor
		dense_matrix(dense_matrix&& other);
		// Copy constructor
		dense_matrix(const dense_matrix& other);

		dense_matrix& operator=(dense_matrix&& other);
		dense_matrix& operator=(const dense_matrix& other);
	};
}

/* Dense Matrix Definition */
namespace math
{
	/* Constructor and Destructor */
	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const MPI_Comm comm)
		: template_matrix<Float, Int>(comm), matrix_(nullptr)
	{
		mtype_ = MATRIX_TYPE::DENSE;
		msort_ = MATRIX_SORT::COLUMN;			// Default
		msymm_ = MATRIX_SYMMETRY::SYMM_NONE;	// Default
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const MPI_Comm comm)
		: template_matrix<Float, Int>(MATRIX_TYPE::DENSE, MATRIX_SORT::COLUMN, MATRIX_SYMMETRY::SYMM_NONE, rows, cols, comm), matrix_(nullptr)
	{
		matrix_ = std::make_unique<Float[]>(this->row_size_ * this->col_size_);
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const Int rows, const Int cols, const std::vector<Float>& mtx, const MPI_Comm comm)
		: template_matrix<Float, Int>(MATRIX_TYPE::DENSE, msort, msymm, rows, cols, comm), matrix_(nullptr)
	{
		msize ms;
		if (msymm == MATRIX_SYMMETRY::SYMMETRIC)
			ms = (msize) ( (this->row_size_ * this->row_size_ + this->row_size_) * 0.5 );
		else
			ms = (msize) ( this->row_size_ * this->col_size_ );
		matrix_ = std::make_unique<Float[]>(ms);
		Int i = 0;
		if (msort == MATRIX_SORT::ROW)
		{
			memcpy(matrix_.get(), mtx.data(), ms * sizeof(Float));
		}
		else
		{
			for (auto itr = mtx.begin(); itr != mtx.end(); itr++)
			{
				matrix_[i] = *itr;
				i += this->row_size_;
				if (i > this->row_size_*this->col_size_)
					i = i%this->row_size_ + 1;
			}
		}
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const Int rows, const Int cols, const Float value, const MPI_Comm comm)
		: template_matrix<Float, Int>(MATRIX_TYPE::DENSE, msort, msymm, rows, cols, comm), matrix_(nullptr)
	{
		msize ms;
		if (msymm == MATRIX_SYMMETRY::SYMMETRIC)
			ms = (msize) ( (this->row_size_ * this->row_size_ + this->row_size_) * 0.5 );
		else
			ms = (msize) ( this->row_size_ * this->col_size_ );
		matrix_ = std::make_unique<Float[]>(ms);
		std::fill_n(matrix_.get(), ms, value);
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const Int rows, const Int cols, const Float * mtx, const MPI_Comm comm)
		: template_matrix<Float, Int>(MATRIX_TYPE::DENSE, msort, msymm, rows, cols, comm), matrix_(nullptr)
	{
		msize ms;
		if (msymm == MATRIX_SYMMETRY::SYMMETRIC)
			ms = (msize) ( (this->row_size_ * this->row_size_ + this->row_size_) * 0.5 );
		else
			ms = (msize) ( this->row_size_ * this->col_size_ );
		this->matrix_ = std::make_unique<Float[]>(ms);
		memcpy(this->matrix_.get(), mtx, ms * sizeof(Float));
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const Int rows, const Int cols, std::unique_ptr<Float[]>&& mtx, MPI_Comm comm)
		: template_matrix<Float, Int>(MATRIX_TYPE::DENSE, msort, msymm, rows, cols, comm), matrix_(std::move(mtx))
	{
	}

	// Move constructor
	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(dense_matrix && other)
		: template_matrix<Float, Int>(other), matrix_(std::move(other.matrix_))
	{
	}

	// Copy constructor
	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const dense_matrix & other)
		: template_matrix<Float, Int>(other)
	{
		int mpi_rank;
		MPI_Comm_rank(other.comm_, &mpi_rank);
		if (mpi_rank != 0)	// 0: Master rank
			return;

		msize ms;
		if (other.msymm_ == MATRIX_SYMMETRY::SYMMETRIC)
			ms = (msize) ( (row_size_ * row_size_ + row_size_) * 0.5 );
		else
			ms = (msize) ( row_size_ * col_size_ );
		matrix_ = std::make_unique<Float[]>(ms);
		memcpy(matrix_.get(), other.matrix_.get(), ms * sizeof(Float));
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int> & dense_matrix<Float, Int>::operator=(dense_matrix && other)
	{
		this->comm_ = other.comm_;
		this->row_size_ = other.row_size_;
		this->col_size_ = other.col_size_;
		this->mtype_ = other.mtype_;
		this->msort_ = other.msort_;
		this->msymm_ = other.msymm_;
		this->matrix_ = std::move(other.matrix_);
		other.row_size_ = 0;
		other.col_size_ = 0;

		return *this;
	}
	template<typename Float, typename Int>
	inline dense_matrix<Float, Int> & dense_matrix<Float, Int>::operator=(const dense_matrix & other)
	{
		this->comm_ = other.comm_;
		this->row_size_ = other.row_size_;
		this->col_size_ = other.col_size_;
		this->mtype_ = other.mtype_;
		this->msort_ = other.msort_;
		this->msymm_ = other.msymm_;
		msize ms;
		if (other.msymm_ == MATRIX_SYMMETRY::SYMMETRIC)
			ms = (msize) ( (row_size_ * row_size_ + row_size_) * 0.5 );
		else
			ms = (msize) ( row_size_ * col_size_ );
		this->matrix_ = std::make_unique<Float[]>(ms);
		memcpy(matrix_.get(), other.matrix_.get(), ms * sizeof(Float));

		return *this;
	}
}