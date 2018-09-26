#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include "matrix_def.h"

#define __ECHO_PRECISION    8
#define __ECHO_WIDTH        18

using namespace math;

#pragma region Echo Dense Matrix

template <typename Float, typename Int>
void echo_dense_matrix( const Int& nrows, const Int& ncols, const Float* mtx, const MATRIX_SYMMETRY& symm, const MATRIX_SORT& sort )
{
	std::cout << "DENSE MATRIX";
	switch (sort)
	{
	case COLUMN:
		std::cout << ",SORT = COLUMN";
		break;
	case ROW:
		std::cout << ",SORT = ROW";
		break;
	default:
		break;
	}
	switch (symm)
	{
	case NONE:
		std::cout << ",SYMMETRY = NONE";
		break;
	case SYMMETRIC:
		std::cout << ",SYMMETRY = SYMMETRIC";
		break;
	default:
		break;
	}
	std::cout << std::endl;

	if (symm == SYMMETRIC)
	{
		if (sort == ROW)
		{
			echo_dense_matrix_sym_row_sort(nrows, mtx);
		}
		else
		{
			echo_dense_matrix_sym_col_sort(nrows, mtx);
		}
	}
	else
	{
		if (sort == ROW)
		{
			echo_dense_matrix_no_sym_row_sort(nrows, ncols, mtx);
		}
		else
		{
			echo_dense_matrix_no_sym_col_sort(nrows, ncols, mtx);
		}
	}
}

template <typename Float, typename Int>
void echo_dense_matrix_no_sym_row_sort(const Int& nrows, const Int& ncols, const Float* mtx, std::ostream& out = std::cout)
{
	for (Int row = 0; row < nrows; row++)
	{
		const Float* val = mtx + row * ncols;
		for (Int col = 0; col < ncols; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << val[col];
			out << "\t";
		}
		out << "\n";
	}
}

template <typename Float, typename Int>
void echo_dense_matrix_no_sym_col_sort(const Int& nrows, const Int& ncols, const Float* mtx, std::ostream& out = std::cout)
{
	for (Int row = 0; row < nrows; row++)
	{
		for (Int col = 0; col < ncols; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[col*nrows + row];
			out << "\t";
		}
		out << "\n";
	}
}

template <typename Float, typename Int>
void echo_dense_matrix_sym_row_sort(const Int& nrows, const Float* mtx, std::ostream& out = std::cout)
{
	Int idx = 0;
	for (Int row = 0; row < nrows; row++)
	{
		for (Int col = 0; col <= row; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[idx++];
			out << "\t";
		}
		Int idx1 = idx + row;
		for (Int col = row + 1; col < nrows; col++)
		{			
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[idx1];
			out << "\t";

			idx1 += col + 1;
		}
		out << "\n";
	}
}

template <typename Float, typename Int>
void echo_dense_matrix_sym_col_sort(const Int& nrows, const Float* mtx, std::ostream& out = std::cout)
{
	for (Int row = 0; row < nrows; row++)
	{
		Int idx = row;
		for (Int col = 0; col < row; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[idx];
			out << "\t";

			idx += nrows - col - 1;
		}
		Int idx1 = idx;
		for (Int col = row; col < nrows; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[idx1++];
			out << "\t";
		}
		out << "\n";
	}
}

#pragma endregion

#pragma region File Echo Dense Matrix

template <typename Float, typename Int>
void echo_dense_matrix(const Int& nrows, const Int& ncols, const Float* mtx, const MATRIX_SYMMETRY& symm, const MATRIX_SORT& sort, const std::string& Header, std::ofstream& out)
{
	out << Header.data() << "\n";
	out << "DENSE MATRIX";
	switch (sort)
	{
	case COLUMN:
		out << ",SORT = COLUMN";
		break;
	case ROW:
		out << ",SORT = ROW";
		break;
	default:
		break;
	}
	switch (symm)
	{
	case NONE:
		out << ",SYMMETRY = NONE";
		break;
	case SYMMETRIC:
		out << ",SYMMETRY = SYMMETRIC";
		break;
	default:
		break;
	}
	out << "\n";

	if (symm == SYMMETRIC)
	{
		if (sort == ROW)
		{
			echo_dense_matrix_sym_row_sort(nrows, mtx, out);
		}
		else
		{
			echo_dense_matrix_sym_col_sort(nrows, mtx, out);
		}
	}
	else
	{
		if (sort == ROW)
		{
			echo_dense_matrix_no_sym_row_sort(nrows, ncols, mtx, out);
		}
		else
		{
			echo_dense_matrix_no_sym_col_sort(nrows, ncols, mtx, out);
		}
	}
}

template <typename Float, typename Int>
void echo_dense_matrix_no_sym_row_sort(const Int& nrows, const Int& ncols, const Float* mtx, std::ofstream& out)
{
	for (Int row = 0; row < nrows; row++)
	{
		const Float* val = mtx + row * ncols;
		for (Int col = 0; col < ncols; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << val[col];
			out << "\t";
		}
		out << "\n";
	}
}

template <typename Float, typename Int>
void echo_dense_matrix_no_sym_col_sort(const Int& nrows, const Int& ncols, const Float* mtx, std::ofstream& out)
{
	for (Int row = 0; row < nrows; row++)
	{
		for (Int col = 0; col < ncols; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[col*nrows + row];
			out << "\t";
		}
		out << "\n";
	}
}

template <typename Float, typename Int>
void echo_dense_matrix_sym_row_sort(const Int& nrows, const Float* mtx, std::ofstream& out)
{
	Int idx = 0;
	for (Int row = 0; row < nrows; row++)
	{
		for (Int col = 0; col <= row; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[idx++];
			out << "\t";
		}
		Int idx1 = idx + row;
		for (Int col = row + 1; col < nrows; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[idx1];
			out << "\t";

			idx1 += col + 1;
		}
		out << "\n";
	}
}

template <typename Float, typename Int>
void echo_dense_matrix_sym_col_sort(const Int& nrows, const Float* mtx, std::ofstream& out)
{
	for (Int row = 0; row < nrows; row++)
	{
		Int idx = row;
		for (Int col = 0; col < row; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[idx];
			out << "\t";

			idx += nrows - col - 1;
		}
		Int idx1 = idx;
		for (Int col = row; col < nrows; col++)
		{
			out << std::scientific << std::setprecision(__ECHO_PRECISION) << std::setw(__ECHO_WIDTH) << std::right << mtx[idx1++];
			out << "\t";
		}
		out << "\n";
	}
}

#pragma endregion

#pragma region Echo Permutation Matrix
template <typename Int>
void echo_permutation_matrix(const Int& msize, const Int* idx, const MATRIX_SYMMETRY& symm, const MATRIX_SORT& sort)
{
	std::cout << "PERMUTATION MATRIX";
	switch (sort)
	{
	case COLUMN:
		std::cout << ",SORT = COLUMN";
		break;
	case ROW:
		std::cout << ",SORT = ROW";
		break;
	default:
		break;
	}
	switch (symm)
	{
	case NONE:
		std::cout << ",SYMMETRY = NONE";
		break;
	case SYMMETRIC:
		std::cout << ",SYMMETRY = SYMMETRIC";
		break;
	default:
		break;
	}
	std::cout << std::endl;

	if (symm == SYMMETRIC)
	{
		std::cout << "Symmetric permutation matrix hasn't been implemented yet!\n";
	}
	else
	{
		if (sort == ROW)
		{
			echo_perm_matrix_no_sym_row_sort(msize, idx);
		}
		else
		{
			echo_perm_matrix_no_sym_col_sort(msize, idx);
		}
	}
}

template <typename Int>
void echo_perm_matrix_no_sym_row_sort(const Int& msize, const Int* colIdx, std::ostream& out = std::cout)
{
	for (Int row = 0; row < msize; row++)
	{
		for (Int col = 0; col < msize; col++)
		{
			if (col == colIdx[row])
			{
				out << "1\t";
			}
			else
			{
				out << "0\t";
			}
		}
		out << "\n";
	}
}

template <typename Int>
void echo_perm_matrix_no_sym_col_sort(const Int& msize, const Int* rowIdx, std::ostream& out = std::cout)
{
	std::unique_ptr<Int[]> colIdx = std::make_unique<Int[]>(msize);
	for (Int col = 0; col < msize; col++)
	{
		colIdx[rowIdx[col]] = col;
	}
	for (Int row = 0; row < msize; row++)
	{
		for (Int col = 0; col < msize; col++)
		{
			if (col == colIdx[row])
			{
				out << "1\t";
			}
			else
			{
				out << "0\t";
			}
		}
		out << "\n";
	}
}
#pragma endregion

#pragma region File Echo Permutation Matrix
template <typename Int>
void echo_permutation_matrix(const Int& msize, const Int* idx, const MATRIX_SYMMETRY& symm, const MATRIX_SORT& sort, const std::string& Header, std::ofstream& out)
{
	out << Header.data() << "\n";
	out << "DENSE MATRIX";
	switch (sort)
	{
	case COLUMN:
		out << ",SORT = COLUMN";
		break;
	case ROW:
		out << ",SORT = ROW";
		break;
	default:
		break;
	}
	switch (symm)
	{
	case NONE:
		out << ",SYMMETRY = NONE";
		break;
	case SYMMETRIC:
		out << ",SYMMETRY = SYMMETRIC";
		break;
	default:
		break;
	}
	out << "\n";

	if (symm == SYMMETRIC)
	{
		std::cout << "Symmetric permutation matrix hasn't been implemented yet!\n";
	}
	else
	{
		if (sort == ROW)
		{
			echo_perm_matrix_no_sym_row_sort(msize, idx, out);
		}
		else
		{
			echo_perm_matrix_no_sym_col_sort(msize, idx, out);
		}
	}
}

template <typename Int>
void echo_perm_matrix_no_sym_row_sort(const Int& msize, const Int* colIdx, std::ofstream& out)
{
	for (Int row = 0; row < msize; row++)
	{
		for (Int col = 0; col < msize; col++)
		{
			if (col == colIdx[row])
			{
				out << "1\t";
			}
			else
			{
				out << "0\t";
			}
		}
		out << "\n";
	}
}

template <typename Int>
void echo_perm_matrix_no_sym_col_sort(const Int& msize, const Int* rowIdx, std::ofstream& out)
{
	std::unique_ptr<Int[]> colIdx = std::make_unique<Int[]>(msize);
	for (Int col = 0; col < msize; col++)
	{
		colIdx[rowIdx[col]] = col;
	}
	for (Int row = 0; row < msize; row++)
	{
		for (Int col = 0; col < msize; col++)
		{
			if (col == colIdx[row])
			{
				out << "1\t";
			}
			else
			{
				out << "0\t";
			}
		}
		out << "\n";
	}
}
#pragma endregion