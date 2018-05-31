#include "stdafx.h"
#include "base_matrix.h"

/* Base Matrix */
namespace math
{
	// Constructor and Destructor
	base_matrix::base_matrix(MPI_Comm comm)
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