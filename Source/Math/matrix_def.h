#pragma once
#include <cstddef>

namespace math
{
	typedef size_t msize;	// Matrix size

	enum MATRIX_TYPE
	{
		TYPE_NONE = 0,
		DENSE,
		SPARSE
	};

	enum MATRIX_SORT
	{
		SORT_NONE = 0,
		COLUMN,
		ROW
	};

	enum MATRIX_SYMMETRY
	{
		SYMM_NONE = 0,
		ASYMMETRIC,
		SYMMETRIC
	};
}