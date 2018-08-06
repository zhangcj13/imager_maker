#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <complex>
#include <iomanip>
#include <random>
#include <omp.h>
#include <functional>

namespace imgmaker
{
	template <typename T>
	class mMatrix
	{
	public:
		mMatrix();
		mMatrix(const mMatrix<T> &object); // object is a mMatrix.
		mMatrix(size_t _rows, size_t _cols, const T *pA);
		mMatrix(size_t _rows, size_t _cols, const T &alpha = T(0)); // alpha is a scalar.
		
		virtual ~mMatrix();

		void creatMatrix(size_t _rows, size_t _cols);
		void setEqualRatioM(void);

		mMatrix<T>& operator=(const mMatrix<T> &object);
		mMatrix<T>& operator=(const T &alpha);
		T* operator[](size_t _index);
		const T* operator[](size_t _index) const;
		T & operator ()(size_t _x, size_t _y);
		const T &operator()(size_t _x, size_t _y) const;
		T & operator ()(size_t _x);
		mMatrix<T> operator + ( mMatrix<T> &other) ;
		mMatrix<T> operator / ( T _div) ;

		T mMax();
		T maxRows(size_t _index);
		T maxcols(size_t _index);

		size_t getsize() const;
		size_t getrows() const;
		size_t getcols() const;

		mMatrix<T> getrows(size_t _index) const;
		mMatrix<T> getcols(size_t _index) const;

		T** getdata() const;

		
	private:
		size_t size;
		size_t rows;
		size_t cols;

		T* data;
		T** pD;

		void init(size_t _rows, size_t _cols);
		void copy(const mMatrix<T> &object);
	}; // class mMatrix

	//---------------------------------------------------------------
	template <typename T>
	void mMatrix<T>::init(size_t _rows, size_t _cols)
	{
		this->rows = _rows;
		this->cols = _cols;
		this->size = _rows * _cols;

		data = new T[size];
		memset(data, 0, sizeof(*data)*size);//น้มใ
		pD = new T*[rows];

		assert(data != NULL);
		assert(pD != NULL);

		pD[0] = data;

		for (size_t i = 1; i < rows; ++i)
		{
			pD[i] = pD[i - 1] + cols;
		}
	}

	template <typename T>
	void mMatrix<T>::creatMatrix(size_t _rows, size_t _cols)
	{
		init(_rows, _cols);
	}

	template <typename T>
	void  mMatrix<T>::setEqualRatioM(void)
	{
		for (int i = 0; i < this->size; ++i)
			*(data + i) = T(i);	
	}

	template <typename T>
	inline void mMatrix<T>::copy(const mMatrix<T> &object)
	{
		init(object.rows, object.cols);
		for (size_t i = 0; i < object.rows; ++i)
		{
			for (size_t j = 0; j < object.cols; ++j)
			{
				pD[i][j] = object.pD[i][j];
			}
		}
	}

	template <typename T>
	mMatrix<T>::mMatrix() :
		rows(0),
		cols(0),
		size(0),
		data(0),
		pD(0){}

	template <typename T>
	mMatrix<T>::mMatrix(const mMatrix<T> &object){ copy(object); }

	template <typename T>
	mMatrix<T>::mMatrix(size_t _rows, size_t _cols, const T *pA)
	{
		init(_rows, _cols);
		for (size_t i = 0; i < size; ++i)
		{
			data[i] = pA[i];
		}
	}

	template <typename T>
	mMatrix<T>::mMatrix(size_t _rows, size_t _cols, const T &alpha)
	{
		init(_rows, _cols);
		for (size_t i = 0; i < size; ++i)
		{
			data[i] = alpha;
		}
	}

	template <typename T>
	mMatrix<T>::~mMatrix()
	{
		if (data != NULL) delete[]data;
		if (pD != NULL) delete[]pD;
	}

	template <typename T>
	mMatrix<T>& mMatrix<T>::operator=(const mMatrix<T> &object)
	{
		if (data == object.data) return *this;

		if (rows == object.rows && cols == object.cols)
		{
			copy(object);
		}
		else
		{
			this->~mMatrix();
			copy(object);
		}

		return *this;
	}

	template <typename T>
	mMatrix<T>& mMatrix<T>::operator=(const T &alpha)
	{
		if (alpha == 0) {
			for (size_t i = 0; i < size; ++i)
			{
				data[i] = alpha;
			}
		}
		else
		{
			for (size_t i = 0; i < rows; ++i)
			{
				for (size_t j = 0; j < cols; ++j)
				{
					if (i == j) pD[i][j] = alpha;
					else pD[i][j] = 0;
				}
			}
		}

		return *this;
	}

	template <typename T>
	T* mMatrix<T>::operator[](size_t _index)
	{
		assert(_index >= 0 && _index < rows);
		return pD[_index];
	}

	template <typename T>
	const T* mMatrix<T>::operator[](size_t _index) const
	{
		assert(_index >= 0 && _index < rows);
		return pD[index];
	}

	template <typename T>
	T & mMatrix<T>::operator ()(size_t _x, size_t _y)
	{
		assert(_x >= 0 && _y >= 0 && _x < rows && _y < cols);
		return*(data + _x*cols + _y);// pD[_x][_y];//
	}

	template <typename T>
	const T & mMatrix<T>::operator ()(size_t _x, size_t _y) const
	{
		assert(_x >= 0 && _y >= 0 && _x < rows && _y < cols);
		return*(data + _x*cols + _y);
	}

	template <typename T>
	T & mMatrix<T>::operator ()(size_t _x)
	{
		assert(_x >= 0 && _x < size);
		return *(data + _x);
	}

	template <typename T>
	mMatrix<T> mMatrix<T>::operator + ( mMatrix<T> &other)  
	{
		//assert(this->rows == other.getrows() && this->cols == other.getcols);

		mMatrix<T> ret(rows, cols);

		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j) 
			{
				ret(i,j) = pD[i][j] + other(i,j);
			}
		}
		return ret;
	}

	template <typename T>
	mMatrix<T> mMatrix<T>::operator / (T _div) 
	{
		mMatrix<T> ret(rows, cols);
		for (size_t i = 0; i < rows; ++i) {
			for (size_t j = 0; j < cols; ++j)
			{
				ret(i, j) = (T)pD[i][j] / _div;
			}
		}
		return ret;
	}

	template <typename T>
	inline size_t mMatrix<T>::getsize() const { return size; }

	template <typename T>
	inline size_t mMatrix<T>::getrows() const { return rows; }

	template <typename T>
	inline size_t mMatrix<T>::getcols() const { return cols; }

	template <typename T>
	inline mMatrix<T> mMatrix<T>::getrows(size_t _index)  const
	{
		mMatrix<T> R(1, cols);

		for (size_t i = 0; i < cols; ++i)
		{
			R[0][i] = pD[_index][i];
		}

		return R;
	}

	template <typename T>
	inline mMatrix<T> mMatrix<T>::getcols(size_t index) const
	{
		mMatrix<T> C(rows_, 1);

		for (size_t i = 0; i < rows; ++i)
		{
			C[i][0] = pD[i][index];
		}

		return C;
	}

	template <typename T>
	inline T** mMatrix<T>::getdata() const { return pD; }

	template <typename T>
	T mMatrix<T>::mMax()
	{
		T maxValue = *(this->data);
		for (size_t i = 0; i < rows; ++i)
		{
			T temp = this->maxRows(i);
			maxValue = (maxValue > temp) ? maxValue : temp;
		}
		return maxValue;
	}

	template <typename T>
	T mMatrix<T>::maxRows(size_t _index)
	{
		assert(_index >= 0 && _index<rows);
		mMatrix<T> R = this->getrows(_index);
		T maxValue = R(0);
		for (size_t i = 1; i < cols; ++i)
		{
			maxValue = (maxValue>R( i)) ? maxValue : R( i);
		}
		return maxValue;
	}

	template <typename T>
	T mMatrix<T>::maxcols(size_t _index)
	{
		assert(_index >= 0 && _index<cols);
		mMatrix<T> C = this->getcols(_index);
		T maxValue = C(0);
		for (size_t i = 1; i < rows; ++i)
		{
			maxValue = (maxValue>C(0)) ? maxValue : C(0);
		}
		return maxValue;
	}
}

