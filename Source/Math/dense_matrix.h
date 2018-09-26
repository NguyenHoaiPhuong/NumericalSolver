#pragma once
#include "operation.h"
#include "base_matrix.h"
#include "dense_matrix.hpp"

/* Dense Matrix Declareation */
namespace math
{
	template<typename Float, typename Int>
	class dense_matrix : public template_matrix<Float, Int>
	{
	private:
		template <typename O, typename... IArgs> friend class op::implementation;

	protected:
		std::unique_ptr<Float[]> matrix_;
	public:
		/* Constructor and Destructor */
		dense_matrix(const MPI_Comm comm = MPI_COMM_WORLD);
		dense_matrix(const Int rows, const Int cols, const MPI_Comm comm = MPI_COMM_WORLD);
		dense_matrix(const Int rows, const Int cols, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm = MPI_COMM_WORLD);

		// Input data were stored in row - order std::vector<Float> mtx
		dense_matrix(const Int rows, const Int cols, const std::vector<Float>& mtx, const MATRIX_SORT msort = COLUMN, const MATRIX_SYMMETRY msymm = NONE, const MPI_Comm comm = MPI_COMM_WORLD);

		// Equal value is applied to each member of the matrix
		dense_matrix(const Int rows, const Int cols, const Float value, const MATRIX_SORT msort = COLUMN, const MATRIX_SYMMETRY msymm = NONE, const MPI_Comm comm = MPI_COMM_WORLD);

		// Input data were stored in column - order mtx
		dense_matrix(const Int rows, const Int cols, const Float* mtx, const MATRIX_SORT msort = COLUMN, const MATRIX_SYMMETRY msymm = NONE, const MPI_Comm comm = MPI_COMM_WORLD);

		// Input data were stored in column - order mtx
		dense_matrix(const Int rows, const Int cols, std::unique_ptr<Float[]>&& mtx, const MATRIX_SORT msort = COLUMN, const MATRIX_SYMMETRY msymm = NONE, MPI_Comm comm = MPI_COMM_WORLD);

		// Move constructor
		dense_matrix(dense_matrix&& other);
		// Copy constructor
		dense_matrix(const dense_matrix& other);

		dense_matrix&	operator=(dense_matrix&& other);
		dense_matrix&	operator=(const dense_matrix& other);

		dense_matrix	operator+(const dense_matrix& other);
		dense_matrix&	operator+=(const dense_matrix& other);
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
		msymm_ = MATRIX_SYMMETRY::NONE;			// Default
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, MATRIX_TYPE::DENSE, MATRIX_SORT::COLUMN, MATRIX_SYMMETRY::NONE, comm), matrix_(nullptr)
	{
		matrix_ = std::make_unique<Float[]>(this->row_size_ * this->col_size_);
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, MATRIX_TYPE::DENSE, msort, msymm, comm), matrix_(nullptr)
	{
		matrix_ = std::make_unique<Float[]>(this->row_size_ * this->col_size_);
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const std::vector<Float>& mtx, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, MATRIX_TYPE::DENSE, msort, msymm, comm), matrix_(nullptr)
	{
		msize ms;
		if (msymm == MATRIX_SYMMETRY::SYMMETRIC)
		{
			_ASSERT(rows == cols);
			ms = (msize)((this->row_size_ * this->row_size_ + this->row_size_) * 0.5);
		}			
		else
			ms = (msize) ( this->row_size_ * this->col_size_ );
		matrix_ = std::make_unique<Float[]>(ms);
		memcpy(matrix_.get(), mtx.data(), ms * sizeof(Float));
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const Float value, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, MATRIX_TYPE::DENSE, msort, msymm, comm), matrix_(nullptr)
	{
		msize ms;
		if (msymm == MATRIX_SYMMETRY::SYMMETRIC)
		{
			_ASSERT(rows == cols);
			ms = (msize)((this->row_size_ * this->row_size_ + this->row_size_) * 0.5);
		}			
		else
			ms = (msize) ( this->row_size_ * this->col_size_ );
		matrix_ = std::make_unique<Float[]>(ms);
		std::fill_n(matrix_.get(), ms, value);
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, const Float * mtx, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, MATRIX_TYPE::DENSE, msort, msymm, comm), matrix_(nullptr)
	{
		msize ms;
		if (msymm == MATRIX_SYMMETRY::SYMMETRIC)
		{
			_ASSERT(rows == cols);
			ms = (msize)((this->row_size_ * this->row_size_ + this->row_size_) * 0.5);
		}
		else
			ms = (msize) ( this->row_size_ * this->col_size_ );
		this->matrix_ = std::make_unique<Float[]>(ms);
		memcpy(this->matrix_.get(), mtx, ms * sizeof(Float));
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int>::dense_matrix(const Int rows, const Int cols, std::unique_ptr<Float[]>&& mtx, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, MPI_Comm comm)
		: template_matrix<Float, Int>(rows, cols, MATRIX_TYPE::DENSE, msort, msymm, comm), matrix_(std::move(mtx))
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

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int> dense_matrix<Float, Int>::operator+(const dense_matrix & other)
	{
		dense_matrix<Float, Int> R;

		_ASSERT(this->comm_ == other.comm_ && this->row_size_ == other.row_size_ && this->col_size_ == other.col_size_);

		if (this->msymm_ == MATRIX_SYMMETRY::NONE && other.msymm_ == MATRIX_SYMMETRY::NONE)
		{
			R = dense_matrix<Float, Int>(this->row_size_, this->col_size_,this->msort_, this->msymm_, this->comm_);
			if (R.msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_nosymm_row_row(this->row_size_, this->col_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_nosymm_row_col(this->row_size_, this->col_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_nosymm_col_row(this->row_size_, this->col_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_nosymm_col_col(this->row_size_, this->col_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
		}
		else if (this->msymm_ == MATRIX_SYMMETRY::NONE && other.msymm_ == MATRIX_SYMMETRY::SYMMETRIC)
		{
			R = dense_matrix<Float, Int>(this->row_size_, this->col_size_, this->msort_, this->msymm_, this->comm_);
			if (R.msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_symm_row_row(this->row_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_symm_row_col(this->row_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_symm_col_row(this->row_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_symm_col_col(this->row_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
		}
		else if (this->msymm_ == MATRIX_SYMMETRY::SYMMETRIC && other.msymm_ == MATRIX_SYMMETRY::NONE)
		{
			R = dense_matrix<Float, Int>(other.row_size_, other.col_size_, other.msort_, other.msymm_, other.comm_);
			if (R.msort_ == MATRIX_SORT::ROW && this->msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_symm_row_row(other.row_size_, other.matrix_.get(), this->matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::ROW && this->msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_symm_row_col(other.row_size_, other.matrix_.get(), this->matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::COLUMN && this->msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_symm_col_row(other.row_size_, other.matrix_.get(), this->matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::COLUMN && this->msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_symm_col_col(other.row_size_, other.matrix_.get(), this->matrix_.get(), R.matrix_.get());
			}
		}
		else if (this->msymm_ == MATRIX_SYMMETRY::SYMMETRIC && other.msymm_ == MATRIX_SYMMETRY::SYMMETRIC)
		{
			R = dense_matrix<Float, Int>(this->row_size_, this->col_size_, this->msort_, this->msymm_, this->comm_);
			if (R.msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::ROW)
			{
				add_symm_symm_row_row(this->row_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_symm_symm_row_col(this->row_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::ROW)
			{
				add_symm_symm_col_row(this->row_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
			else if (R.msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_symm_symm_col_col(this->row_size_, this->matrix_.get(), other.matrix_.get(), R.matrix_.get());
			}
		}

		return R;
	}

	template<typename Float, typename Int>
	inline dense_matrix<Float, Int> & dense_matrix<Float, Int>::operator+=(const dense_matrix & other)
	{
		_ASSERT(this->comm_ == other.comm_ && this->row_size_ == other.row_size_ && this->col_size_ == other.col_size_);

		if (this->msymm_ == MATRIX_SYMMETRY::NONE && other.msymm_ == MATRIX_SYMMETRY::NONE)
		{
			if (this->msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_nosymm_row_row(this->row_size_, this->col_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_nosymm_row_col(this->row_size_, this->col_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_nosymm_col_row(this->row_size_, this->col_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_nosymm_col_col(this->row_size_, this->col_size_, other.matrix_.get(), this->matrix_.get());
			}
		}
		else if (this->msymm_ == MATRIX_SYMMETRY::NONE && other.msymm_ == MATRIX_SYMMETRY::SYMMETRIC)
		{
			if (this->msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_symm_row_row(this->row_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_symm_nosymm_col_row(this->row_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::ROW)
			{
				add_symm_nosymm_row_col(this->row_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_symm_col_col(this->row_size_, other.matrix_.get(), this->matrix_.get());
			}
		}
		else if (this->msymm_ == MATRIX_SYMMETRY::SYMMETRIC && other.msymm_ == MATRIX_SYMMETRY::NONE)
		{
			this->msymm_ = other.msymm_;

			Int ms = other.row_size_ * other.col_size_;
			std::unique_ptr<Float[]> res = std::make_unique<Float[]>(ms);
			memcpy(res.get(), other.matrix_.get(), ms * sizeof(Float));

			if (this->msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::ROW)
			{
				add_nosymm_symm_row_row(this->row_size_, this->matrix_.get(), res.get());
			}
			else if (this->msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::COLUMN)
			{
				this->msort_ = other.msort_;
				add_symm_nosymm_row_col(this->row_size_, this->matrix_.get(), res.get());
			}
			else if (this->msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::ROW)
			{
				this->msort_ = other.msort_;
				add_symm_nosymm_col_row(this->row_size_, this->matrix_.get(), res.get());
			}
			else if (this->msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_nosymm_symm_col_col(this->row_size_, this->matrix_.get(), res.get());
			}
			this->matrix_ = std::move(res);
		}
		else if (this->msymm_ == MATRIX_SYMMETRY::SYMMETRIC && other.msymm_ == MATRIX_SYMMETRY::SYMMETRIC)
		{
			if (this->msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::ROW)
			{
				add_symm_symm_row_row(this->row_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::ROW && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_symm_symm_col_row(this->row_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::ROW)
			{
				add_symm_symm_row_col(this->row_size_, other.matrix_.get(), this->matrix_.get());
			}
			else if (this->msort_ == MATRIX_SORT::COLUMN && other.msort_ == MATRIX_SORT::COLUMN)
			{
				add_symm_symm_col_col(this->row_size_, other.matrix_.get(), this->matrix_.get());
			}
		}

		return *this;
	}

}