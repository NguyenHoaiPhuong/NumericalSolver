#pragma once
#include <cstddef>

# define __MASTER_RANK	0
namespace math
{
	typedef size_t msize;	// Matrix size

	enum MATRIX_TYPE
	{
		TYPE_NONE = 0,
		DENSE,
		SPARSE,
		PERMUTATION
	};

	enum MATRIX_SORT
	{		
		COLUMN = 0,
		ROW
	};

	enum MATRIX_SYMMETRY
	{
		NONE,
		SYMMETRIC
	};
}