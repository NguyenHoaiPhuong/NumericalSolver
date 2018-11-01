#pragma once
#include <memory>
#include "mpi.h"
#include "matrix_def.h"

/* Base and Template Matrix Declaration */
namespace math
{
	class base_matrix
	{
	protected:
		MPI_Comm	comm_;

	public:
		// Constructor and Destructor
		base_matrix(const MPI_Comm comm = MPI_COMM_WORLD);
		virtual ~base_matrix();

		virtual msize row_size() const;
		virtual msize col_size() const;
		virtual MATRIX_TYPE matrix_type() const;
		virtual MATRIX_SORT matrix_sort() const;
		virtual MATRIX_SYMMETRY matrix_symmetry() const;
	};
	typedef std::unique_ptr<base_matrix> base_matrix_p;

	class null_matrix : public base_matrix	{};

	template<typename Float, typename Int>
	class template_matrix : public base_matrix
	{
	protected:
		Int					row_size_;
		Int					col_size_;
		MATRIX_TYPE			mtype_;
		MATRIX_SORT			msort_;
		MATRIX_SYMMETRY		msymm_;
	public:
		// Constructor and Destructor
		template_matrix(const MPI_Comm comm = MPI_COMM_WORLD);
		template_matrix(const Int rows, const Int cols, const MPI_Comm comm = MPI_COMM_WORLD);
		template_matrix(const Int rows, const Int cols, const MATRIX_TYPE mtype, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm = MPI_COMM_WORLD);
		template_matrix(template_matrix&& other);
		template_matrix(const template_matrix& other);
		virtual ~template_matrix();

		// Getters
		msize				row_size() const;
		msize				col_size() const;
		MATRIX_TYPE			matrix_type() const;
		MATRIX_SORT			matrix_sort() const;
		MATRIX_SYMMETRY		matrix_symmetry() const;

		// Setters
		virtual void row_set(const msize rows);
		virtual void col_set(const msize cols);
		virtual void matrix_type_set(const MATRIX_TYPE mtype);
		virtual void matrix_sort_set(const MATRIX_SORT msort);
		virtual void matrix_symmetry_set(const MATRIX_SYMMETRY msymm);
	};
}
 
/* Base Matrix Definition */
namespace math
{
	// Constructor and Destructor
	base_matrix::base_matrix(const MPI_Comm comm)
		: comm_(comm)
	{
	}
	base_matrix::~base_matrix()
	{
	}

	msize base_matrix::row_size() const
	{
		return 0;
	}
	msize base_matrix::col_size() const
	{
		return 0;
	}
	MATRIX_TYPE base_matrix::matrix_type() const
	{
		return MATRIX_TYPE::TYPE_NONE;
	}
	MATRIX_SORT base_matrix::matrix_sort() const
	{
		return MATRIX_SORT::COLUMN;
	}
	MATRIX_SYMMETRY base_matrix::matrix_symmetry() const
	{
		return MATRIX_SYMMETRY::NONE;
	}
}

/* Template Matrix Definition */
namespace math
{
	// Constructors and Destructors
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(const MPI_Comm comm)
		: base_matrix(comm), row_size_(0), col_size_(0)
	{
		mtype_ = MATRIX_TYPE::TYPE_NONE;
		msort_ = MATRIX_SORT::COLUMN;
		msymm_ = MATRIX_SYMMETRY::NONE;
	}
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(const Int rows, const Int cols, const MPI_Comm comm)
		: base_matrix(comm), row_size_(rows), col_size_(cols)
	{
		mtype_ = MATRIX_TYPE::TYPE_NONE;
		msort_ = MATRIX_SORT::COLUMN;
		msymm_ = MATRIX_SYMMETRY::NONE;
	}
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(const Int rows, const Int cols, const MATRIX_TYPE mtype, const MATRIX_SORT msort, const MATRIX_SYMMETRY msymm, const MPI_Comm comm)
		: base_matrix(comm), row_size_(rows), col_size_(cols)
		, mtype_(mtype), msort_(msort), msymm_(msymm)
	{
	}
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(template_matrix && other)
		: base_matrix(other.comm_), row_size_(other.row_size_), col_size_(other.col_size_)
		, mtype_(other.mtype_), msort_(other.msort_), msymm_(other.msymm_)
	{
	}
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(const template_matrix & other)
		: base_matrix(other.comm_), row_size_(other.row_size_), col_size_(other.col_size_)
		, mtype_(other.mtype_), msort_(other.msort_), msymm_(other.msymm_)
	{
	}
	template<typename Float, typename Int>
	template_matrix<Float, Int>::~template_matrix()
	{
	}

	// Getters
	template<typename Float, typename Int>
	msize template_matrix<Float, Int>::row_size() const
	{
		return row_size_;
	}
	template<typename Float, typename Int>
	msize template_matrix<Float, Int>::col_size() const
	{
		return col_size_;
	}
	template<typename Float, typename Int>
	MATRIX_TYPE template_matrix<Float, Int>::matrix_type() const
	{
		return mtype_;
	}
	template<typename Float, typename Int>
	MATRIX_SORT template_matrix<Float, Int>::matrix_sort() const
	{
		return msort_;
	}
	template<typename Float, typename Int>
	MATRIX_SYMMETRY template_matrix<Float, Int>::matrix_symmetry() const
	{
		return msymm_;
	}

	// Setters
	template<typename Float, typename Int>
	void template_matrix<Float, Int>::row_set(const msize rows)
	{
		row_size_ = rows;
	}
	template<typename Float, typename Int>
	void template_matrix<Float, Int>::col_set(const msize cols)
	{
		col_size_ = cols;
	}
	template<typename Float, typename Int>
	inline void template_matrix<Float, Int>::matrix_type_set(const MATRIX_TYPE mtype)
	{
		mtype_ = mtype;
	}
	template<typename Float, typename Int>
	inline void template_matrix<Float, Int>::matrix_sort_set(const MATRIX_SORT msort)
	{
		msort_ = msort;
	}
	template<typename Float, typename Int>
	inline void template_matrix<Float, Int>::matrix_symmetry_set(const MATRIX_SYMMETRY msymm)
	{
		msymm_ = msymm_;
	}
}