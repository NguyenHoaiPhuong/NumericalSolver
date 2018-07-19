#pragma once
#include "operation.h"
#include "matrix.h"

namespace op
{
	class ASSIGN_OPERATION {};
	using assign_operation = operation<void, ASSIGN_OPERATION, const math::base_matrix, math::base_matrix>;
}

namespace math
{
	void assign(const base_matrix& A, base_matrix& B) { op::assign_operation::perform(A, B); }
	void assign(const matrix& A, matrix& B) { op::assign_operation::perform(A.implementation(), B.implementation()); }
}

namespace op
{
	using namespace math;

	__implementation(void, assign_operation, const null_matrix, null_matrix)::operator()(const base_matrix& A, base_matrix& B) {}

	__implementation(void, assign_operation, const dense_matrix<double, int>, dense_matrix<double, int>)
		::operator()(const base_matrix& A, base_matrix& B) {
		const dense_matrix<double, int>& a = static_cast<const dense_matrix<double, int>&>(A);
		dense_matrix<double, int>& b = static_cast<dense_matrix<double, int>&>(B);
		/*int rank = 0;
		mpi::comm_rank(a.communicator_, &rank);
		if (rank != __MASTER_RANK)
			return;

		assign_dense_to_dense(a.row_size_, a.col_size_, a.matrix_.get(), a.communicator_, b.row_size_, b.col_size_, b.matrix_, b.communicator_);*/
	}
}