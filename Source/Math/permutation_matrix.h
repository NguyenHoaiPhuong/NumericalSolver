#pragma once

#include "operation.h"
#include "base_matrix.h"
#include <array>
#include <vector>
#include <memory>

// Permutation matrix declaration
namespace math
{
	template <typename Int>
	class permutation_matrix : public base_matrix
	{
	private:
		template <typename O, typename... IArgs> friend class op::implementation;

	protected:
		Int						msize_;
		std::unique_ptr<Int[]>	perm_;
		MATRIX_TYPE				mtype_;
		MATRIX_SORT				msort_;
		MATRIX_SYMMETRY			msymm_;

	public:
		// Constructors
		permutation_matrix(const MPI_Comm comm = MPI_COMM_WORLD);
		permutation_matrix(const Int msize, const MPI_Comm comm = MPI_COMM_WORLD);
		permutation_matrix(const Int msize, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm = MPI_COMM_WORLD);
		permutation_matrix(const Int msize, const std::vector< std::array<Int, 2> >& values, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm = MPI_COMM_WORLD);
		permutation_matrix(const permutation_matrix& other);
		permutation_matrix(permutation_matrix&& other);

		// operators
		permutation_matrix& operator=(const permutation_matrix& other);
		permutation_matrix& operator=(permutation_matrix&& other);

		msize			row_size() const;
		msize			col_size() const;
		MATRIX_TYPE		matrix_type() const;
		MATRIX_SORT		matrix_sort() const;
		MATRIX_SYMMETRY matrix_symmetry() const;
	};	
}

// Permutation matrix definition
namespace math
{
	/* Constructors */
	template<typename Int>
	inline permutation_matrix<Int>::permutation_matrix(const MPI_Comm comm)
		: base_matrix(comm), msize_(0), perm_(nullptr)
		, mtype_(PERMUTATION), msort_(ROW), msymm_(NONE)
	{
	}
	template<typename Int>
	inline permutation_matrix<Int>::permutation_matrix(const Int msize, const MPI_Comm comm)
		: base_matrix(comm), msize_(msize), perm_(nullptr)
		, mtype_(PERMUTATION), msort_(ROW), msymm_(NONE)
	{
		perm_ = std::make_unique<Int[]>(msize_);
	}
	template<typename Int>
	inline permutation_matrix<Int>::permutation_matrix(const Int msize, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm)
		: base_matrix(comm), msize_(msize), perm_(nullptr)
		, mtype_(PERMUTATION), msort_(msort), msymm_(msymm)
	{
		if (msymm_ == NONE)
		{
			if (msort_ == ROW)
			{
				perm_ = std::make_unique<Int[]>(msize_);
			}
			else
			{
				perm_ = std::make_unique<Int[]>(msize_);
			}
		}
		else
		{
			std::cout << "Symmetric permutation matrix hasn't been implemented yet!\n";
		}
	}
	template<typename Int>
	inline permutation_matrix<Int>::permutation_matrix(	const Int msize, const std::vector<std::array<Int, 2>>& values,
														const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm )
		: base_matrix(comm), msize_(msize), perm_(nullptr)
		, mtype_(PERMUTATION), msort_(msort), msymm_(msymm)
	{
		if (msymm_ == NONE)
		{
			if (msort_ == ROW)
			{
				perm_ = std::make_unique<Int[]>(msize_);
				for (auto r : values)
				{
					perm_[r[0]] = r[1];
				}
			}
			else
			{
				perm_ = std::make_unique<Int[]>(msize_);
				for (auto r : values)
				{
					perm_[r[1]] = r[0];
				}
			}
		}
		else
		{
			std::cout << "Symmetric permutation matrix hasn't been implemented yet!\n";
		}
	}
	template<typename Int>
	inline permutation_matrix<Int>::permutation_matrix(const permutation_matrix & other)
		: base_matrix(other.comm_), msize_(other.msize_), perm_(nullptr)
		, mtype_(PERMUTATION), msort_(other.msort_), msymm_(other.msymm_)
	{
		if (msymm_ == NONE)
		{
			if (msort_ == ROW)
			{
				perm_ = std::make_unique<Int[]>(msize_);
				memcpy(perm_.get(), other.perm_.get(), msize_ * sizeof(Int));
			}
			else
			{
				perm_ = std::make_unique<Int[]>(msize_);
				memcpy(perm_.get(), other.perm_.get(), msize_ * sizeof(Int));
			}
		}
		else
		{
			std::cout << "Symmetric permutation matrix hasn't been implemented yet!\n";
		}
	}
	template<typename Int>
	inline permutation_matrix<Int>::permutation_matrix(permutation_matrix && other)
		: base_matrix(other.comm_), msize_(other.msize_), perm_(nullptr)
		, mtype_(PERMUTATION), msort_(other.msort_), msymm_(other.msymm_)
	{
		perm_ = std::move(other.perm_);
	}

	/* Operator = */
	template<typename Int>
	inline permutation_matrix<Int> & permutation_matrix<Int>::operator=(const permutation_matrix & other)
	{
		msize_		= other.msize_;
		mtype_		= other.mtype_;
		msort_		= other.msort_;
		msymm_		= other.msymm_;

		if (msymm_ == NONE)
		{
			if (msort_ == ROW)
			{
				perm_ = std::make_unique<Int[]>(msize_);
				memcpy(perm_.get(), other.perm_.get(), msize_ * sizeof(Int));
			}
			else
			{
				perm_ = std::make_unique<Int[]>(msize_);
				memcpy(perm_.get(), other.perm_.get(), msize_ * sizeof(Int));
			}
		}
		else
		{
			std::cout << "Symmetric permutation matrix hasn't been implemented yet!\n";
		}
		return *this;
	}
	template<typename Int>
	inline permutation_matrix<Int> & permutation_matrix<Int>::operator=(permutation_matrix && other)
	{
		msize_		= other.msize_;
		mtype_		= other.mtype_;
		msort_		= other.msort_;
		msymm_		= other.msymm_;
		perm_		= std::move(other.perm_);
		
		return *this;
	}

	template<typename Int>
	inline msize permutation_matrix<Int>::row_size() const
	{
		return msize_;
	}

	template<typename Int>
	inline msize permutation_matrix<Int>::col_size() const
	{
		return msize_;
	}

	template<typename Int>
	inline MATRIX_TYPE permutation_matrix<Int>::matrix_type() const
	{
		return MATRIX_TYPE::PERMUTATION;
	}

	template<typename Int>
	inline MATRIX_SORT permutation_matrix<Int>::matrix_sort() const
	{
		return msort_;
	}

	template<typename Int>
	inline MATRIX_SYMMETRY permutation_matrix<Int>::matrix_symmetry() const
	{
		return msymm_;
	}

	
}