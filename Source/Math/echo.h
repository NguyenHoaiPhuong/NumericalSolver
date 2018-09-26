#pragma once
#include "operation.h"
#include "matrix.h"
#include "dense_matrix.h"
#include "permutation_matrix.h"
#include "echo.hpp"

namespace op
{
	class ECHO_OPERATION {};
	using echo_operation = operation<void, ECHO_OPERATION, const math::base_matrix>;

	class FILE_ECHO_OPERATION {};
	using file_echo_operation = operation<void, FILE_ECHO_OPERATION, const math::base_matrix, const std::string, std::ofstream>;
}

namespace math
{
	void echo(const base_matrix& A) { op::echo_operation::perform(A); }
	void echo(const matrix& A) { op::echo_operation::perform(A.implementation()); }

	void echo(const base_matrix& A, const std::string& Header, std::ofstream& out) { op::file_echo_operation::perform(A, Header, out); }
	void echo(const matrix& A, const std::string& Header, std::ofstream& out) { op::file_echo_operation::perform(A.implementation(), Header, out); }
}

// echo_operation
namespace op
{
	using namespace math;

	// Null matrix writting by std::cout
	__implementation(void, echo_operation, const null_matrix&)
		::operator()(const base_matrix& A) 
	{
		std::cout << "Null Matrix\n";
	}

	// Dense matrix writting by std::cout
	__implementation(void, echo_operation, const dense_matrix<double, int>&)
		::operator()(const base_matrix& A)
	{
		const dense_matrix<double, int>& a = static_cast<const dense_matrix<double, int>&>(A);
		echo_dense_matrix( a.row_size_, a.col_size_, a.matrix_.get(), a.msymm_, a.msort_ );
	}

	//  Permutation matrix writting by std::cout
	__implementation(void, echo_operation, const permutation_matrix<int>&)
		::operator()(const base_matrix& A)
	{
		const permutation_matrix<int>& a = static_cast<const permutation_matrix<int>&>(A);
		echo_permutation_matrix( a.msize_, a.perm_.get(), a.msymm_, a.msort_ );
	}
}

// file_echo_operation
namespace op
{
	using namespace math;

	// Null matrix writting to file
	__implementation(void, file_echo_operation, const null_matrix&, const std::string&, std::ofstream& )
		::operator()(const base_matrix& A, const std::string& Header, std::ofstream& out) 
	{
		out << Header.data() << "\n";
		out << "Null Matrix\n";
	}

	// Dense matrix writting to file
	__implementation(void, file_echo_operation, const dense_matrix<double, int>&, const std::string&, std::ofstream&)
		::operator()(const base_matrix& A, const std::string& Header, std::ofstream& out)
	{
		const dense_matrix<double, int>& a = static_cast<const dense_matrix<double, int>&>(A);
		echo_dense_matrix(a.row_size_, a.col_size_, a.matrix_.get(), a.msymm_, a.msort_, Header, out);
	}

	// Permutation matrix writting to file
	__implementation(void, file_echo_operation, const permutation_matrix<int>&, const std::string&, std::ofstream&)
		::operator()(const base_matrix& A, const std::string& Header, std::ofstream& out)
	{
		const permutation_matrix<int>& a = static_cast<const permutation_matrix<int>&>(A);
		echo_permutation_matrix(a.msize_, a.perm_.get(), a.msymm_, a.msort_, Header, out);
	}
}