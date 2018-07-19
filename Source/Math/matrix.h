#pragma once
#include "base_matrix.h"

struct file
{
	std::string name;
	std::string path;
};

/* Declaration of Matrix */
namespace math
{
	class matrix
	{
	private:
		base_matrix_p	impl_;
		file			file_loc_;
		//h5::location_t loc_;		Not implemented yet
	public:
		/* Constructor and Destructor */
		matrix(const MPI_Comm comm = MPI_COMM_WORLD);
		matrix(const file& loc, const MPI_Comm comm = MPI_COMM_WORLD);
		matrix(const std::string& name, const std::string& path, const MPI_Comm comm = MPI_COMM_WORLD);
		//matrix(const h5::location_t& loc, const MPI_Comm comm = MPI_COMM_WORLD);						Not implemented yet
		//matrix(const std::string& f, const std::string& p, const MPI_Comm comm = MPI_COMM_WORLD);		Not implemented yet
		matrix(base_matrix_p&& impl);
		matrix(const matrix& A);
		matrix(matrix&& A);
		matrix& operator=(const matrix& A);
		matrix& operator=(matrix&& A);
		~matrix();

		/* Getters */
		msize	row_size() const;
		msize	col_size() const;
		file	file_location() const;
		// Implementation
		base_matrix& implementation();
		const base_matrix& implementation() const;

		/* Setters */
		void	location_set(const file& loc);
		void	location_set(const std::string& name, const std::string& path);
	};
}

/* Definition of Matrix */
namespace math
{
	/* Constructor and Destructor */
	matrix::matrix(const MPI_Comm comm)
	{
		impl_ = std::make_unique<base_matrix>(base_matrix(comm));
	}
	inline matrix::matrix(const file & loc, const MPI_Comm comm)
	{
		impl_ = std::make_unique<base_matrix>(base_matrix(comm));
		file_loc_ = loc;
	}
	inline matrix::matrix(const std::string & name, const std::string & path, const MPI_Comm comm)
	{
		impl_ = std::make_unique<base_matrix>(base_matrix(comm));
		file_loc_.name = name;
		file_loc_.path = path;
	}
	matrix::matrix(base_matrix_p && impl)
	{
		impl_ = std::move(impl);
	}
	matrix::matrix(const matrix & A)
	{
	}
	matrix::matrix(matrix && A)
	{
		this->impl_ = std::move(A.impl_);
		A.impl_ = std::make_unique<null_matrix>();
		this->file_loc_ = A.file_loc_;
	}
	matrix & matrix::operator=(const matrix & A)
	{
		// TODO: insert return statement here

		return *this;
	}
	matrix & matrix::operator=(matrix && A)
	{
		this->impl_ = std::move(A.impl_);
		A.impl_ = std::make_unique<null_matrix>();
		this->file_loc_ = A.file_loc_;
		return *this;
	}
	matrix::~matrix()
	{
	}

	msize matrix::row_size() const
	{
		return impl_->row_size();
	}
	msize matrix::col_size() const
	{
		return impl_->col_size();
	}
	inline file matrix::file_location() const
	{
		return file_loc_;
	}
	base_matrix & matrix::implementation()
	{
		return *impl_;
	}
	const base_matrix & matrix::implementation() const
	{
		return *impl_;
	}
	inline void matrix::location_set(const file & loc)
	{
		file_loc_ = loc;
	}
	inline void matrix::location_set(const std::string & name, const std::string & path)
	{
		file_loc_.name = name;
		file_loc_.path = path;
	}
}