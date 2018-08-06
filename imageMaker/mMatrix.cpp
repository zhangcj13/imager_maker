#include "mMatrix.h"


namespace imgmaker
{
	template <typename T>
	mMatrix::~mMatrix()
	{
	}

	template <typename T>
	mMatrix<T>::mMatrixmMatrix(size_t _x, T _initdata = 0)
	{
		dimensional = 1;
		data = (T)malloc(sizeof(T)*_x);
		memset(hist, 0, sizeof(data));
	}

}
