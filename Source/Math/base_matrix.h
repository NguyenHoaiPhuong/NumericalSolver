#pragma once
#include <memory>
#include "mpi.h"
#include "msize.h"

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
	};
	typedef std::unique_ptr<base_matrix> base_matrix_p;

	class null_matrix : public base_matrix	{};

	template<typename Float, typename Int>
	class template_matrix : public base_matrix
	{
	protected:
		Int row_size_;
		Int col_size_;
	public:
		// Constructor and Destructor
		template_matrix(const MPI_Comm comm = MPI_COMM_WORLD);
		template_matrix(const Int rows, const Int cols, const MPI_Comm comm = MPI_COMM_WORLD);
		template_matrix(template_matrix&& other);
		template_matrix(const template_matrix& other);
		virtual ~template_matrix();

		// Getters
		msize row_size() const;
		msize col_size() const;
		// Setters
		void row_set(const msize rows);
		void col_set(const msize cols);
	};
}
 