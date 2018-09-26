#pragma once

// Operator +
#pragma region NOSYMM - NOSYMM

template <typename Float, typename Int>
void add_nosymm_nosymm_row_row(const Int& nrows, const Int& ncols, const Float* a, const Float* b, Float* c)
{
	Int msize = nrows * ncols;
	for (Int i = 0; i < msize; i++)
	{
		c[i] = a[i] + b[i];
	}
}

template <typename Float, typename Int>
void add_nosymm_nosymm_col_col(const Int& nrows, const Int& ncols, const Float* a, const Float* b, Float* c)
{
	Int msize = nrows * ncols;
	for (Int i = 0; i < msize; i++)
	{
		c[i] = a[i] + b[i];
	}
}

template <typename Float, typename Int>
void add_nosymm_nosymm_row_col(const Int& nrows, const Int& ncols, const Float* a, const Float* b, Float* c)
{
	for (Int row = 0; row < nrows; row++)
	{
		Float* cc = c + row * ncols;
		const Float* aa = a + row * ncols;
		const Float* bb = b + row;
		for (Int col = 0; col < ncols; col++)
		{
			*cc = *aa + *bb;
			aa++;
			bb += nrows;
			cc++;
		}
	}
}

template <typename Float, typename Int>
void add_nosymm_nosymm_col_row(const Int& nrows, const Int& ncols, const Float* a, const Float* b, Float* c)
{
	for (Int col = 0; col < ncols; col++)
	{
		Float* cc = c + col * nrows;
		const Float* aa = a + col * nrows;
		const Float* bb = b + col;
		for (Int row = 0; row < nrows; row++)
		{
			*cc = *aa + *bb;
			aa++;
			bb += ncols;
			cc++;
		}
	}
}

#pragma endregion

#pragma region NOSYMM - SYMM

template <typename Float, typename Int>
void add_nosymm_symm_row_row(const Int& nrows, const Float* a, const Float* b, Float* c)
{
	Int idx = 0;
	Int idxb = 0;
	for (Int row = 0; row < nrows; row++)
	{
		for (Int col = 0; col <= row; col++)
		{
			c[idx] = a[idx] + b[idxb];
			idxb++;
			idx++;
		}
		Int idxbb = idxb;
		for (Int col = row + 1; col < nrows; col++)
		{
			c[idx] = a[idx] + b[idxbb + row];			
			idxbb += col + 1;
			idx++;
		}
	}
}

template <typename Float, typename Int>
void add_nosymm_symm_col_col(const Int& nrows, const Float* a, const Float* b, Float* c)
{
	Int idx = 0;
	for (Int col = 0; col < nrows; col++)
	{		
		Int idxb = col;
		for (Int row = 0; row < col; row++)
		{
			c[idx] = a[idx] + b[idxb];
			idx++;
			idxb += nrows - row - 1;
		}
		for (Int row = col; row < nrows; row++)
		{
			c[idx] = a[idx] + b[idxb];
			idx++;
			idxb++;
		}
	}
}

template <typename Float, typename Int>
void add_nosymm_symm_row_col(const Int& nrows, const Float* a, const Float* b, Float* c)
{
	Int idx = 0;
	for (Int row = 0; row < nrows; row++)
	{
		Int idxb = row;
		for (Int col = 0; col < row; col++)
		{
			c[idx] = a[idx] + b[idxb];
			idx++;
			idxb += nrows - col - 1;
		}
		for (Int col = row; col < nrows; col++)
		{
			c[idx] = a[idx] + b[idxb];
			idx++;
			idxb++;
		}
	}
}

template <typename Float, typename Int>
void add_nosymm_symm_col_row(const Int& nrows, const Float* a, const Float* b, Float* c)
{
	Int idx = 0;	
	for (Int col = 0; col < nrows; col++)
	{
		Int idxb = (Int) (0.5 * col * (col+1));
		for (Int row = 0; row < col; row++)
		{
			c[idx] = a[idx] + b[idxb];
			idx++;
			idxb++;
		}
		for (Int row = col; row < nrows; row++)
		{
			c[idx] = a[idx] + b[idxb];
			idx++;
			idxb += row + 1;
		}
	}
}

#pragma endregion

#pragma region SYMM - SYMM

template <typename Float, typename Int>
void add_symm_symm_row_row(const Int& nrows, const Float* a, const Float* b, Float* c)
{
	Int msize = (Int)(0.5 * nrows * (nrows + 1));
	for (Int i = 0; i < msize; i++)
	{
		c[i] = a[i] + b[i];
	}
}

template <typename Float, typename Int>
void add_symm_symm_col_col(const Int& nrows, const Float* a, const Float* b, Float* c)
{
	Int msize = (Int)(0.5 * nrows * (nrows + 1));
	for (Int i = 0; i < msize; i++)
	{
		c[i] = a[i] + b[i];
	}
}

template <typename Float, typename Int>
void add_symm_symm_row_col(const Int& nrows, const Float* a, const Float* b, Float* c)
{
	Int idx = 0;
	for (Int row = 0; row < nrows; row++)
	{
		Int idxb = row;
		for (Int col = 0; col <= row; col++)
		{
			c[idx] = a[idx] + b[idxb];
			idx++;
			idxb += nrows - col - 1;
		}
	}
}

template <typename Float, typename Int>
void add_symm_symm_col_row(const Int& nrows, const Float* a, const Float* b, Float* c)
{
	Int idx = 0;
	for (Int col = 0; col < nrows; col++)
	{
		Int idxb = (Int)(0.5 * col * (col + 3));
		for (Int row = col; row < nrows; row++)
		{
			c[idx] = a[idx] + b[idxb];
			idx++;
			idxb += row + 1;
		}
	}
}

#pragma endregion

// Operator +=
#pragma region NOSYMM - NOSYMM

template <typename Float, typename Int>
void add_nosymm_nosymm_row_row(const Int& nrows, const Int& ncols, const Float* a, Float* b)
{
	Int msize = nrows * ncols;
	for (Int i = 0; i < msize; i++)
	{
		b[i] += a[i];
	}
}

template <typename Float, typename Int>
void add_nosymm_nosymm_col_col(const Int& nrows, const Int& ncols, const Float* a, Float* b)
{
	Int msize = nrows * ncols;
	for (Int i = 0; i < msize; i++)
	{
		b[i] += a[i];
	}
}

template <typename Float, typename Int>
void add_nosymm_nosymm_row_col(const Int& nrows, const Int& ncols, const Float* a, Float* b)
{
	for (Int row = 0; row < nrows; row++)
	{
		Float* bb = b + row * ncols;
		const Float* aa = a + row;
		for (Int col = 0; col < ncols; col++)
		{
			*bb += *aa;
			bb++;
			aa += nrows;
		}
	}
}

template <typename Float, typename Int>
void add_nosymm_nosymm_col_row(const Int& nrows, const Int& ncols, const Float* a, Float* b)
{
	for (Int col = 0; col < ncols; col++)
	{
		Float* bb = b + col * nrows;
		const Float* aa = a + col;
		for (Int row = 0; row < nrows; row++)
		{
			*bb += *aa;
			bb++;
			aa += ncols;
		}
	}
}

#pragma endregion

#pragma region NOSYMM - SYMM

template <typename Float, typename Int>
void add_nosymm_symm_row_row(const Int& nrows, const Float* a, Float* b)
{
	Int idx = 0;
	Int idxa = 0;
	for (Int row = 0; row < nrows; row++)
	{
		for (Int col = 0; col <= row; col++)
		{
			b[idx] += a[idxa];
			idxa++;
			idx++;
		}
		Int idxaa = idxa;
		for (Int col = row + 1; col < nrows; col++)
		{
			b[idx] += a[idxaa + row];
			idxaa += col + 1;
			idx++;
		}
	}
}

template <typename Float, typename Int>
void add_nosymm_symm_col_col(const Int& nrows, const Float* a, Float* b)
{
	Int idx = 0;
	for (Int col = 0; col < nrows; col++)
	{
		Int idxa = col;
		for (Int row = 0; row < col; row++)
		{
			b[idx] += a[idxa];
			idx++;
			idxa += nrows - row - 1;
		}
		for (Int row = col; row < nrows; row++)
		{
			b[idx] += a[idxa];
			idx++;
			idxa++;
		}
	}
}

template <typename Float, typename Int>
void add_symm_nosymm_col_row(const Int& nrows, const Float* a, Float* b)
{
	Int idx = 0;
	for (Int row = 0; row < nrows; row++)
	{
		Int idxa = row;
		for (Int col = 0; col < row; col++)
		{
			b[idx] += a[idxa];
			idx++;
			idxa += nrows - col - 1;
		}
		for (Int col = row; col < nrows; col++)
		{
			b[idx] += a[idxa];
			idx++;
			idxa++;
		}
	}
}

template <typename Float, typename Int>
void add_symm_nosymm_row_col(const Int& nrows, const Float* a, Float* b)	// b: nosymm - col, a: symm - row
{
	Int idx = 0;
	for (Int col = 0; col < nrows; col++)
	{
		Int idxa = (Int)(0.5 * col * (col + 1));
		for (Int row = 0; row < col; row++)
		{
			b[idx] += a[idxa];
			idx++;
			idxa++;
		}
		for (Int row = col; row < nrows; row++)
		{
			b[idx] += a[idxa];
			idx++;
			idxa += row + 1;
		}
	}
}

#pragma endregion

#pragma region SYMM - SYMM

template <typename Float, typename Int>
void add_symm_symm_row_row(const Int& nrows, const Float* a, Float* b)
{
	Int msize = (Int)(0.5 * nrows * (nrows + 1));
	for (Int i = 0; i < msize; i++)
	{
		b[i] += a[i];
	}
}

template <typename Float, typename Int>
void add_symm_symm_col_col(const Int& nrows, const Float* a, Float* b)
{
	Int msize = (Int)(0.5 * nrows * (nrows + 1));
	for (Int i = 0; i < msize; i++)
	{
		b[i] += a[i];
	}
}

template <typename Float, typename Int>
void add_symm_symm_col_row(const Int& nrows, const Float* a, Float* b)
{
	Int idx = 0;
	for (Int row = 0; row < nrows; row++)
	{
		Int idxa = row;
		for (Int col = 0; col <= row; col++)
		{
			b[idx] += a[idxa];
			idx++;
			idxa += nrows - col - 1;
		}
	}
}

template <typename Float, typename Int>
void add_symm_symm_row_col(const Int& nrows, const Float* a, Float* b)
{
	Int idx = 0;
	for (Int col = 0; col < nrows; col++)
	{
		Int idxa = (Int) ( 0.5 * col * (col + 3) );
		for (Int row = col; row < nrows; row++)
		{
			b[idx] += a[idxa];
			idx++;
			idxa += row + 1;
		}
	}
}

#pragma endregion