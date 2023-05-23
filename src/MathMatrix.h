#pragma once
#include <string>
#include "MathVec.h"
#include "math.h"
template <class T, unsigned int rowDim, unsigned int colDim>
class MathMatrix {
public:
	MathMatrix(T null);
	~MathMatrix();

	MathMatrix(const MathMatrix& source);
	MathMatrix(MathMatrix&& source) noexcept;

	T get(unsigned int row, unsigned int col) const;
	void set(unsigned int row, unsigned int col, T value);
	T getNullElement() const;
	MathVec<T, rowDim> getColumn(int index) const;
	MathVec<T, colDim> getRow(int index) const;

	MathMatrix operator+(const MathMatrix& matrix);

private:
	void throw_if_out_of_bounds(unsigned int y, unsigned int x) const;
	void throw_if_out_of_bounds_x(unsigned int x) const;
	void throw_if_out_of_bounds_y(unsigned int y) const;
	T** data;
	T nullElement;
};


template <class T, unsigned int rowDim, unsigned int colDim>
std::string to_string(const MathMatrix<T, rowDim, colDim>& m) {
	std::string message = "";
	for(int y=0; y<rowDim; y++) {
		message += "|";
		for(int x=0; x<colDim; x++) {
			message += std::to_string(m.get(y,x));

			// spacing
			if(x < colDim - 1) {
				message += " ";
			}
		}
		message += "|\n";
	}
	return message;
}


// matrix scalar multiplication
template <class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim> operator*(const MathMatrix<T, rowDim, colDim>& matrix, const T& el) {
	MathMatrix<T, rowDim, colDim> matrix_return = MathMatrix<T, rowDim, colDim>(matrix.getNullElement());
	for(u_int y = 0; y < rowDim; y++) {
		for(u_int x = 0; x < colDim; x++) {
			T value = matrix.get(y,x) * el;
			matrix_return.set(y,x, value);
		}
	}
	return matrix_return;
}

// matrix scalar multiplication
template <class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim> operator*(const T& el, const MathMatrix<T, rowDim, colDim>& matrix) {
	MathMatrix<T, rowDim, colDim> matrix_return = MathMatrix<T, rowDim, colDim>(matrix.getNullElement());
	for(u_int y = 0; y < rowDim; y++) {
		for(u_int x = 0; x < colDim; x++) {
			T value = matrix.get(y,x) * el;
			matrix_return.set(y,x, value);
		}
	}
	return matrix_return;
}

// matrix vector multiplication A*b
template <class T, unsigned int rowDim, unsigned int colDim>
MathVec<T, colDim> operator*(const MathMatrix<T, rowDim, colDim>& matrix, const MathVec<T, rowDim>& vec) {
	MathVec<T, colDim> vec_return = MathVec<T, colDim>(matrix.getNullElement());
	for(u_int y = 0; y < rowDim; y++) {
		T vec_row = matrix.getNullElement();
		for(u_int x = 0; x < colDim; x++) {
			vec_row += matrix.get(y,x) * vec.get(x);
		}
		vec_return.set(y, vec_row);
	}
	return vec_return;
}


// matrix matrix multiplication
template <class T, unsigned int rowDim, unsigned int colDim, unsigned int colDim_2>
MathMatrix<T, rowDim, colDim_2> operator*(const MathMatrix<T, rowDim, colDim>& matrix1, const MathMatrix<T, colDim, colDim_2>& matrix2) {
	MathMatrix<T, rowDim, colDim_2> matrix_return = MathMatrix<T, rowDim, colDim_2>(matrix1.getNullElement());
	u_int matrix2_x = 0;

	for(u_int matrix2_x = 0; matrix2_x < colDim_2; matrix2_x++) {
		for(u_int y = 0; y < rowDim; y++) {
			T matrix2_col = matrix1.getNullElement();

			for(u_int x = 0; x < colDim; x++) {
				matrix2_col += matrix1.get(y,x) * matrix2.get(x, matrix2_x);
			}
			matrix_return.set(y, matrix2_x, matrix2_col);
		}
	}
	return matrix_return;
}


template <class T>
MathVec2<T> rotate2dVec(const MathVec2<T>& vec, float angle_rad) {
	MathVec2<T> vec_return = MathVec2<T>(0);
	T x1_vec = vec.get(0);
	T x2_vec = vec.get(1);
	float x1 = std::cos(angle_rad) * x1_vec - std::sin(angle_rad) * x2_vec;
	float x2 = std::sin(angle_rad) * x1_vec + std::cos(angle_rad) * x2_vec;
	vec_return.set(0, x1);
	vec_return.set(1, x2);
	return vec_return;
}