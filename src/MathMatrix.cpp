#pragma once
#include <string>
#include "MathMatrix.h"
#include "MathVec.h"
#include <stdexcept>

// MathMatrix<class T, unsigned int rowDim, unsigned int colDim>::

// constructor
template <class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim>::MathMatrix(T null) {
	data = new T*[rowDim];
	for(u_int y = 0; y < rowDim; y++) {
		data[y] = new T[colDim];
		for(u_int x = 0; x < colDim; x++) {
			data[y][x] = null;
		}
	}
	nullElement = null;
}

// deconstructor
template <class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim>::~MathMatrix() {
	for(unsigned int y = 0; y < rowDim; y++)
		delete[] data[y];
	delete[] data;
}

// copy constructor
template <class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim>::MathMatrix(const MathMatrix& source) {
	data = new T*[rowDim];
	for(u_int y = 0; y < rowDim; y++) {
		data[y] = new T[colDim];
		for(u_int x = 0; x < colDim; x++) {
			data[y][x] = source.data[y][x];
		}
	}
	nullElement = source.nullElement;
}

// move constructor
template <class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim>::MathMatrix(MathMatrix&& source) noexcept {
	nullElement = source.nullElement;
	data = source.data;
	source.data = nullptr;
}

// get cell
template <class T, unsigned int rowDim, unsigned int colDim>
T MathMatrix<T, rowDim, colDim>::get(unsigned int row, unsigned int col) const {
	throw_if_out_of_bounds(row, col);
	return data[row][col];
}

// set cell
template <class T, unsigned int rowDim, unsigned int colDim>
void MathMatrix<T, rowDim, colDim>::set(unsigned int row, unsigned int col, T value) {
	throw_if_out_of_bounds(row, col);
	data[row][col] = value;
}

// get 0 element
template <class T, unsigned int rowDim, unsigned int colDim>
T MathMatrix<T, rowDim, colDim>::getNullElement() const {
	return nullElement;
}

// get vec of column ↓
template <class T, unsigned int rowDim, unsigned int colDim>
MathVec<T, rowDim> MathMatrix<T, rowDim, colDim>::getColumn(int index) const {
	throw_if_out_of_bounds_x(index);
	MathVec<T, rowDim> vec = MathVec<T, rowDim>(nullElement);
	for (u_int y = 0; y < rowDim; y++)
	{
		vec.set(y, get(y, index));
	}
	return vec;
}

// get vec of row →
template <class T, unsigned int rowDim, unsigned int colDim>
MathVec<T, colDim> MathMatrix<T, rowDim, colDim>::getRow(int index) const {
	throw_if_out_of_bounds_y(index);
	MathVec<T, colDim> vec = MathVec<T, colDim>(nullElement);
	for (u_int x = 0; x < colDim; x++)
	{
		vec.set(x, get(index, x));
	}
	return vec;
}




// + op
template <class T, unsigned int rowDim, unsigned int colDim>
MathMatrix<T, rowDim, colDim> MathMatrix<T, rowDim, colDim>::operator+(const MathMatrix<T, rowDim, colDim>& m) {
	MathMatrix<T, rowDim, colDim> matr = MathMatrix<T, rowDim, colDim>(nullElement);

	for(u_int y = 0; y < rowDim; y++) {
		for(u_int x = 0; x < colDim; x++) {
			matr.data[y][x] = this->data[y][x] + m.data[y][x];
		}
	}
	return matr;
}


// private funcs
template <class T, unsigned int rowDim, unsigned int colDim>
void MathMatrix<T, rowDim, colDim>::throw_if_out_of_bounds(unsigned int y, unsigned int x) const {
	throw_if_out_of_bounds_x(x);
	throw_if_out_of_bounds_y(y);
}
template <class T, unsigned int rowDim, unsigned int colDim>
void MathMatrix<T, rowDim, colDim>::throw_if_out_of_bounds_x(unsigned int x) const {
	if(x >= colDim) {
		std::string error = "";
		std::string x_str = std::to_string(x);
		std::string colDim_str = std::to_string(colDim);
		throw std::out_of_range("x:" + x_str +" not in col range " + "[0-" + colDim_str + "]");
	}
}
template <class T, unsigned int rowDim, unsigned int colDim>
void MathMatrix<T, rowDim, colDim>::throw_if_out_of_bounds_y(unsigned int y) const {
	if(y >= rowDim) {
		std::string error = "";
		std::string y_str = std::to_string(y);
		std::string rowDim_str = std::to_string(rowDim);
		throw std::out_of_range("y:" + y_str+" not in row range " + "[0-" + rowDim_str+ "]");
	}
}

