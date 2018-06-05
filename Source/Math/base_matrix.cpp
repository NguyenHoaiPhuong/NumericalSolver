#include "stdafx.h"
#include "base_matrix.h"

/* Base Matrix */
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
}

/* Template Matrix */
namespace math
{
	// Constructors and Destructors
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(const MPI_Comm comm)
		: base_matrix(comm), row_size_(0), col_size_(0)
	{
	}
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(const Int rows, const Int cols, const MPI_Comm comm)
		: base_matrix(comm), row_size_(rows), col_size_(cols)
	{
	}
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(template_matrix && other)
		: base_matrix(other.comm_), row_size_(other.row_size_), col_size_(other.col_size_)
	{
	}
	template<typename Float, typename Int>
	template_matrix<Float, Int>::template_matrix(const template_matrix & other)
		: base_matrix(other.comm_), row_size_(other.row_size_), col_size_(other.col_size_)
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
}