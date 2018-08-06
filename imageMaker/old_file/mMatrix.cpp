#include "mMatrix.h"

// �ƶ�����
template <typename T>
mMatrix<T>::mMatrix(mMatrix<T> &&other) {
	data.swap(other.data);
}

//��������
template <typename T>
mMatrix<T>::mMatrix(const mMatrix<T> &other) {
	data = other.getData();
}

// ����һ��n�еĿվ���
template <typename T>
mMatrix<T>::mMatrix(vecSizeT _x) {
	std::vector< std::vector<T> > temp(_x);
	data = temp;
}
//ͨ�����������������վ���
template <typename T>
mMatrix<T>::mMatrix(vecSizeT _x, vecSizeT _y) {
	std::vector< std::vector<T> > temp(_x, std::vector<T>(_y));
	data = temp;
}

//����������캯����������vector�Ŀ�������
template <typename T>
mMatrix<T>::mMatrix(std::vector<std::vector<T> > dvec) {
	data = dvec;
}

/*
* ����һ��ָ����С�ĵ�λ��
* @author piratf
* @param  _x ����
* @param  _y  ����
* @return    һ����λ����
*/
template <typename T>
mMatrix<T> mMatrix<T>::eye(vecSizeT _x, vecSizeT _y) {
	mMatrix<T> mat(_x, _y);

	for (vecSizeT i = 0; i < _x; ++i) {
		for (vecSizeT j = 0; j < _y; ++j) {
			if (i == j) {
				mat.data[i][j] = 1;
			}
		}
	}

	return mat;
}

/**
* ��þ����ת��
* @author piratf
* @return �µľ�������Ϊԭ�����ת��
*/
template <typename T>
mMatrix<T> mMatrix<T>::getTransposition() const {
	decltype(data.size()) sizeRow = data.size();

	if (sizeRow == 0) {
		std::cerr << "error** mMatrix<T>::getTransposition -> empty mMatrix!" << std::endl;
	}

	using vecSizeT = decltype(data.size());
	vecSizeT sizeCol = data[0].size();

	mMatrix tran(sizeCol, sizeRow);

	for (vecSizeT i = 0; i < sizeRow; ++i) {
		for (vecSizeT j = 0; j < sizeCol; ++j) {
			tran.data[j][i] = data[i][j];
		}
	}

	return tran;
}

/**
* ��̬��������ȡ���������ĵ�˽��
* @author piratf
* @param  lhs ����1
* @param  rhs ����2
* @return     double:��˵Ľ��
*/
template <typename T>
T mMatrix<T>::vectorDotProduct(const std::vector<T> lhs, std::vector<T> rhs) {
	T ans = 0;

	for (decltype(lhs.size()) i = 0; i != lhs.size(); ++i) {
		ans += lhs[i] * rhs[i];
	}

	return ans;
}

/**
* һ�������ľ�ֵ
*/
template <typename T>
T mMatrix<T>::avg(const std::vector<T> &vec) {
	T sum = 0;

	for (T var : vec) {
		sum += var;
	}

	return sum / vec.size();
}

/**
* �����Э�������
*/
template <typename T>
mMatrix<T> mMatrix<T>::cov() const {
#ifndef NOTEMPTY
#define NOTEMPTY
	assert(!empty());
#endif
	const vecSizeT sizeRow = row();
	const vecSizeT sizeCol = col();
	auto mat = this->getTransposition();
	std::vector<T> avgVec;

	// ����ÿһ�������ֵ
	for (auto &row : mat.data) {
		avgVec.push_back(avg(row));
	}

	// ���Э����������
	mMatrix temp(sizeRow, sizeCol);

	for (vecSizeT i = 0; i != sizeRow; ++i) {
		for (vecSizeT j = 0; j != sizeCol; ++j) {
			temp.data[i][j] = mat.data[i][j] - avgVec[i];
		}
	}

	// ���Э�������
	mMatrix cov(sizeRow, sizeRow);

	for (vecSizeT i = 0; i != sizeRow; ++i) {
		for (vecSizeT j = 0; j != sizeRow; ++j) {
			cov.data[i][j] = mMatrix<T>::vectorDotProduct(temp.data[i], temp.data[j]) / (sizeCol - 1);
		}
	}

	return cov;
}

/**
* ������������Э�������
* ���������еĸ������谴������
* @author piratf
* @return һ���µ�Э�������
*/
template <typename T>
mMatrix<T> mMatrix<T>::cov(const mMatrix<T> &input) {
	return input.cov();
}

/**
* �ж��Ƿ��ǿվ���
* @author piratf
* @return 1 : 0 -> �վ��� : ���ǿվ���
*/
template <typename T>
bool mMatrix<T>::empty() const {
	return !data.size();
}

/**
* �жϾ����Ƿ��Ƿ���
* @author piratf
* @return 1 : 0 -> ���� : ���Ƿ���
*/
template <typename T>
bool mMatrix<T>::isSquare() const {
	return empty() ? 0 : data.size() == data[0].size();
}

/**
* ���������ʽ
* @author piratf
* @return double: ����ʽ��ֵ
*/
template <typename T>
std::complex<double> mMatrix<T>::det() const {
	// �����������ĳ˻�
	auto e = eig();
	std::complex<double> ret = e[0];

	for (vecSizeT i = 1; i < data.size(); ++i) {
		ret *= e[i];
	}

	return ret;
}

/**
* �жϵ�ǰ�����Ƿ����������
* @author piratf
* @return 1: ��������� 0: �����������
*/
template <typename T>
bool mMatrix<T>::isSingular() const {
	return det() ? false : true;
}

/**
* ������Ԫ�ĸ�˹��ȥ������
*/
template <typename T>
mMatrix<double> mMatrix<T>::inv() const {
#ifndef NOTEMPTY
#define NOTEMPTY
	assert(!empty());
#endif
#ifndef ISSQUARE
#define ISSQUARE
	assert(isSquare());
#endif
	vecSizeT i, j, k, len = row();
	double maxVal, temp;
	//��A����������ʱ������
	mMatrix<double> TMat;

	if (SameType<T, double>::isSame) {
		TMat = *this;
	}
	else {
		TMat = this->toDouble();
	}

	//��ʼ��ans����Ϊ��λ��
	mMatrix<double> ans = mMatrix<double>::eye(row(), col());

	for (i = 0; i < len; i++) {
		//Ѱ����Ԫ
		maxVal = TMat[i][i];
		k = i;

		for (j = i + 1; j < len; j++) {
			if (std::abs(TMat[j][i]) > std::abs(maxVal)) {
				maxVal = TMat[j][i];
				k = j;
			}
		}

		//�����Ԫ�����в��ǵ�i�У������н���
		if (k != i) {
			TMat[i].swap(TMat[k]);
			ans[i].swap(ans[k]);
		}

		assert(cond2().real() < 1e11);
		//�ж���Ԫ�Ƿ�Ϊ0, ����, �����A�������Ⱦ���,�����������
		// if (cond2().real() > 1e10) {
		//     throw (Exception("ERROR** mMatrix::inv -> there is no inverse mMatrix!"));
		// }
		//��ȥA�ĵ�i�г�ȥi������ĸ���Ԫ��
		temp = TMat[i][i];

		for (j = 0; j < len; j++) {
			TMat[i][j] = TMat[i][j] / temp;     //���Խ����ϵ�Ԫ�ر�Ϊ1
			ans[i][j] = ans[i][j] / temp;       //�������
		}

		// ������
		for (j = 0; j < len; j++) {
			// ���ǵ�i��
			if (j != i) {
				temp = TMat[j][i];

				// ��j��Ԫ�� - i��Ԫ�� * j��i��Ԫ��
				for (k = 0; k < len; k++) {
					TMat[j][k] -= TMat[i][k] * temp;
					ans[j][k] -= ans[i][k] * temp;
				}
			}
		}
	}

	return ans;
}

// ���������
template <typename T>
vecSizeT mMatrix<T>::row() const {
	return data.size();
}

// ���������
template <typename T>
vecSizeT mMatrix<T>::col() const {
	if (data.size()) {
		return data[0].size();
	}
	else {
		return 0;
	}
}

// ���к�ȡĳһ�У������µľ���
template <typename T>
mMatrix<T> mMatrix<T>::row(vecSizeT index) const {
	return mMatrix<T>(data[index]);
}

// ȡ�����е�ĳһ��
template <typename T>
std::vector<T> &mMatrix<T>::operator [](vecSizeT index) {
	assert(index >= 0 && index < data.size());
	return data[index];
}

// ȡ�����е�ĳһ��
template <typename T>
const std::vector<T> &mMatrix<T>::operator [](vecSizeT index) const {
	assert(index >= 0 && index < data.size());
	return data[index];
}

// ���ɵ�ǰ����� Hessenberg ��ʽ�����¾��󷵻�
template <typename T>
mMatrix<double> mMatrix<T>::hess() const {
#ifndef NOTEMPTY
#define NOTEMPTY
	assert(!empty());
#endif
#ifndef ISSQUARE
#define ISSQUARE
	assert(isSquare());
#endif
	mMatrix<double> A = toDouble();

	vecSizeT n = data.size();
	vecSizeT i, j, k;
	mMatrix<double> ret(n, n);
	T temp = 0;
	vecSizeT max;

	for (k = 1; k < n - 1; ++k) {
		i = k - 1;
		max = k;
		temp = std::abs(A[k][i]);

		for (j = k + 1; j < n; ++j) {
			if (temp < std::abs(A[j][i])) {
				temp = std::abs(A[j][i]);
				max = j;
			}
		}

		ret[0][0] = A[max][i];
		i = max;

		if (ret[0][0]) {
			if (i != k) {
				for (j = k - 1; j < n; ++j) {
					temp = A[i][j];
					A[i][j] = A[k][j];
					A[k][j] = temp;
				}

				for (j = 0; j < n; ++j) {
					temp = A[j][i];
					A[j][i] = A[j][k];
					A[j][k] = temp;
				}
			}

			for (i = k + 1; i < n; ++i) {
				temp = A[i][k - 1] / ret[0][0];
				A[i][k - 1] = 0;

				for (vecSizeT j = k; j < n; ++j) {
					A[i][j] -= temp * A[k][j];
				}

				for (j = 0; j < n; ++j) {
					A[j][k] += temp * A[j][i];
				}
			}
		}
	}

	return A;
}

/**
* ���ؾ����ȫ�����������Ը�����ʾ
* QR �ֽⷨ
*/
template<typename T>
mMatrix<std::complex<double>> mMatrix<T>::eig(double eps, unsigned LOOP) const {
#ifndef NOTEMPTY
#define NOTEMPTY
	assert(!empty());
#endif
#ifndef ISSQUARE
#define ISSQUARE
	assert(isSquare());
#endif
	unsigned loop = LOOP;
	const vecSizeT n = data.size();
	vecSizeT m = n;
	mMatrix<double> A = hess();
	mMatrix<double> ret(n, 2);
	vecSizeT i, j, k, t;
	double tempVar, indexVar, sign, p, q;
	double r, x, s, e, f, z, y, temp;
	double num;

	while (m != 0) {
		t = m - 1;

		while (t > 0) {
			temp = std::abs(A[t - 1][t - 1]);
			temp += std::abs(A[t][t]);
			temp *= eps;

			if (std::abs(A[t][t - 1]) > temp) {
				--t;
			}
			else {
				break;
			}
		}

		if (t == m - 1) {
			ret[m - 1][0] = A[m - 1][m - 1];
			ret[m - 1][1] = 0;
			m -= 1;
			loop = LOOP;
		}
		else if (t == m - 2) {
			tempVar = -A[m - 1][m - 1] - A[m - 2][m - 2];
			indexVar = A[m - 1][m - 1] * A[m - 2][m - 2]
				- A[m - 1][m - 2] * A[m - 2][m - 1];
			num = tempVar * tempVar - 4 * indexVar;
			y = std::sqrt(std::abs(num));

			if (num > 0) {
				sign = 1;

				if (tempVar < 0) {
					sign = -1;
				}

				ret[m - 1][0] = -(tempVar + sign * y) / 2;
				ret[m - 1][1] = 0;
				ret[m - 2][0] = indexVar / ret[m - 1][0];
				ret[m - 2][1] = 0;
			}
			else {
				ret[m - 1][0] = -tempVar / 2;
				ret[m - 2][0] = -tempVar / 2;
				ret[m - 1][1] = y / 2;
				ret[m - 2][1] = -y / 2;
			}

			m -= 2;
			loop = LOOP;
		}
		else {
			if (loop < 1) {
				return mMatrix<std::complex<double> >();
			}

			--loop;
			j = t + 2;

			while (j < m) {
				A[j][j - 2] = 0;
				++j;
			}

			j = t + 3;

			while (j < m) {
				A[j][j - 3] = 0;
				++j;
			}

			k = t;

			while (k < m - 1) {
				if (k != t) {
					p = A[k][k - 1];
					q = A[k + 1][k - 1];

					if (k != m - 2) {
						r = A[k + 2][k - 1];
					}
					else {
						r = 0;
					}
				}
				else {
					tempVar = A[m - 1][m - 1];
					indexVar = A[m - 2][m - 2];
					x = tempVar + indexVar;
					y = tempVar * indexVar - A[m - 2][m - 1] * A[m - 1][m - 2];
					p = A[t][t] * (A[t][t] - x) + A[t][t + 1] * A[t + 1][t] + y;
					q = A[t + 1][t] * (A[t][t] + A[t + 1][t + 1] - x);
					r = A[t + 1][t] * A[t + 2][t + 1];
				}

				if (p != 0 || q != 0 || r != 0) {
					if (p < 0) {
						sign = -1;
					}
					else {
						sign = 1;
					}

					s = sign * std::sqrt(p * p + q * q + r * r);

					if (k != t) {
						A[k][k - 1] = -s;
					}

					e = -q / s;
					f = -r / s;
					x = -p / s;
					y = -x - f * r / (p + s);
					num = e * r / (p + s);
					z = -x - e * q / (p + s);

					for (j = k; j < m; ++j) {
						tempVar = A[k][j];
						indexVar = A[k + 1][j];
						p = x * tempVar + e * indexVar;
						q = e * tempVar + y * indexVar;
						r = f * tempVar + num * indexVar;

						if (k != m - 2) {
							tempVar = A[k + 2][j];
							p += f * tempVar;
							q += num * tempVar;
							r += z * tempVar;
							A[k + 2][j] = r;
						}

						A[k + 1][j] = q;
						A[k][j] = p;
					}

					j = k + 3;

					if (j > m - 2) {
						j = m - 1;
					}

					for (i = t; i < j + 1; ++i) {
						tempVar = A[i][k];
						indexVar = A[i][k + 1];
						p = x * tempVar + e * indexVar;
						q = e * tempVar + y * indexVar;
						r = f * tempVar + num * indexVar;

						if (k != m - 2) {
							tempVar = A[i][k + 2];
							p += f * tempVar;
							q += num * tempVar;
							r += z * tempVar;
							A[i][k + 2] = r;
						}

						A[i][k + 1] = q;
						A[i][k] = p;
					}
				}

				++k;
			}
		}
	}

	// ����һ������
	mMatrix<std::complex<double> >res(n, 1);

	for (vecSizeT i = 0; i < ret.row(); ++i) {
		// �ж��Ƿ��Ǹ�������
		bool flag = ComplexType<T>::isComplex;

		if (flag) {
			res[i][0] = std::complex<double>(static_cast<std::complex<T> >(ret[i][0]).real(), static_cast<std::complex<T> >(ret[i][1]).real());
		}
		else {
			res[i][0] = std::complex<double>(ret[i][0], ret[i][1]);
		}
	}

	return res;
}

//���ؾ���������Ԫ��
template <typename T>
T mMatrix<T>::max() const {
	if (!data.size()) {
		return static_cast<T>(0);
	}

	T maxv = data[0][0];

	for (vecSizeT i = 0; i < data.size(); ++i) {
		for (vecSizeT j = 0; j < data[0].size(); ++j) {
			maxv = data[i][j] < maxv ? maxv : data[i][j];
		}
	}

	return maxv;
}

//���ؾ�������С��Ԫ��
template <typename T>
T mMatrix<T>::min() const {
	if (!data.size()) {
		return static_cast<T>(0);
	}

	T minv = data[0][0];

	for (vecSizeT i = 0; i < data.size(); ++i) {
		for (vecSizeT j = 0; j < data[0].size(); ++j) {
			minv = data[i][j] < minv ? data[i][j] : minv;
		}
	}

	return minv;
}

// ������ ����ʽ �µ�������
template <typename T>
std::complex<double> mMatrix<T>::cond2() const {
	// ��ȡ����ֵ
	auto e = eig();
	return e.max() / e.min();
}

// ����ľ�ֵ
template <typename T>
T mMatrix<T>::avg() const {
	if (!empty()) {
		return static_cast<T>(0);
	}

	T sum = 0;

	for (vecSizeT i = 0; i < data.size(); ++i) {
		for (vecSizeT j = 0; j < data[0].size(); ++j) {
			sum += data[i][j];
		}
	}

	// for (const auto row : data) {
	//     for (T var : row) {
	//         sum += var;
	//     }
	// }
	return sum / (row() * col());
}

// ������Ӹ�ֵ
template <typename T>
mMatrix<T> mMatrix<T>::operator += (const mMatrix<T> &other) {
#ifndef EQUALSIZE
#define EQUALSIZE
	assert(data.size());
	assert(row() == other.row() && col() == other.col());
#endif

	for (vecSizeT i = 0; i < row(); ++i) {
		for (vecSizeT j = 0; j < col(); ++j) {
			data[i][j] += other[i][j];
		}
	}

	return *this;
}

// �������
template <typename T>
mMatrix<T> mMatrix<T>::operator + (const mMatrix<T> &other) const {
#ifndef EQUALSIZE
#define EQUALSIZE
	assert(data.size());
	assert(row() == other.row() && col() == other.col());
#endif

	mMatrix<T> ret(row(), col());

	for (vecSizeT i = 0; i < row(); ++i) {
		for (vecSizeT j = 0; j < col(); ++j) {
			ret[i][j] = data[i][j] + other[i][j];
		}
	}

	return ret;
}


// �������
template <typename T>
mMatrix<T> mMatrix<T>::operator -= (const mMatrix<T> &other) {
#ifndef EQUALSIZE
#define EQUALSIZE
	assert(data.size());
	assert(row() == other.row() && col() == other.col());
#endif

	for (vecSizeT i = 0; i < row(); ++i) {
		for (vecSizeT j = 0; j < col(); ++j) {
			data[i][j] -= other[i][j];
		}
	}

	return *this;
}

//�������

template <typename T>
mMatrix<T> mMatrix<T>::operator - (const mMatrix<T> &other) const {
#ifndef EQUALSIZE
#define EQUALSIZE
	assert(data.size());
	assert(row() == other.row() && col() == other.col());
#endif

	mMatrix<T> ret(row(), col());

	for (vecSizeT i = 0; i < row(); ++i) {
		for (vecSizeT j = 0; j < col(); ++j) {
			ret[i][j] = data[i][j] - other[i][j];
		}
	}

	return ret;
}

/* �������
* ��ͨ�㷨*/
template <typename T>
void mMatrix<T>::mul(mMatrix<T> &ret, const mMatrix<T> &other) const {
#ifndef MULCHECK
#define MULCHECK
	assert(data.size());
	assert(col() == other.row());
#endif

	for (vecSizeT i = 0; i < row(); ++i) {
		for (vecSizeT k = 0; k < col(); ++k) {
			for (vecSizeT j = 0; j < col(); ++j) {
				ret[i][j] += data[i][k] * other[k][j];
			}
		}
	}

	return;
}

/* �������
* ��ͨ�㷨*/
template <typename T>
mMatrix<T> mMatrix<T>::operator * (const mMatrix<T> &other) const {
#ifndef MULCHECK
#define MULCHECK
	assert(data.size());
	assert(col() == other.row());
#endif
	mMatrix<T> ret(col(), other.row());

	// �Գƾ���ʹ�� ˹����ɭ�˷�
	if (row() == col()) {
		smul(ret, other);
	}
	else {
		// ��ͨ�˷�
		mul(ret, other);
	}

	return ret;
}

/**
* ���� *=
* ��ͨ�㷨
*/
template <typename T>
mMatrix<T> mMatrix<T>::operator *= (const mMatrix<T> &other) {
#ifndef MULCHECK
#define MULCHECK
	assert(data.size());
	assert(col() == other.row());
#endif
	mMatrix<T> ret(col(), other.row());

	// ��ĶԳƾ���ʹ�� ˹����ɭ�˷�
	if (row() > 50 && row() == col()) {
		smul(ret, other);
	}
	else {
		// ��ͨ�˷�
		mul(ret, other);
	}

	return ret;
}

/**
* �������
*/
template <typename T>
mMatrix<double> mMatrix<T>::div(const mMatrix<T> &other) const {
#ifndef DIVCHECK
#define DIVCHECK
	assert(data.size());
	assert(other.row() == other.col());
#endif

	return this->toDouble() * other.inv();
}
/**
* �����ҳ�
*/
template <typename T>
mMatrix<double> mMatrix<T>::rdiv(const mMatrix<T> &other) const {
#ifndef DIVCHECK
#define DIVCHECK
	assert(data.size());
	assert(other.row() == other.col());
#endif

	return this->inv() * other.toDouble();
}

/**
* �������
* ���
*/
template <typename T>
mMatrix<double> mMatrix<T>::operator / (const mMatrix<T> &other) const {
#ifndef DIVCHECK
#define DIVCHECK
	assert(data.size());
	assert(other.row() == other.col());
#endif

	return div(other);
}

/**
* �������
* ���
*/
template <typename T>
mMatrix<double> mMatrix<T>::operator /= (const mMatrix<T> &other) {
#ifndef DIVCHECK
#define DIVCHECK
	assert(data.size());
	assert(other.row() == other.col());
#endif

	return *this = div(other);
}

/**
* �������
* �ҳ�
*/
template <typename T>
mMatrix<double> mMatrix<T>::operator % (const mMatrix<T> &other) const {
#ifndef DIVCHECK
#define DIVCHECK
	assert(data.size());
	assert(other.row() == other.col());
#endif

	return rdiv(other);
}

/**
* ת��Ϊ double ����
*/
template <typename T>
mMatrix<double> mMatrix<T>::toDouble() const {
	mMatrix<double> mat(row(), col());

	// ��������Ǹ�������ֻȡʵ�����֣�������������
	// δʵ��
	for (vecSizeT i = 0; i < row(); ++i) {
		for (vecSizeT j = 0; j < col(); ++j) {
			mat[i][j] = static_cast<double>(data[i][j]);
		}
	}

	return mat;
}

/**
* ˹����ɭ�˷�����������Ҫ���� n * n ����
*/
template <typename T>
void mMatrix<T>::smul(mMatrix<T> &ret, const mMatrix<T> &other) const {
#ifndef MULCHECK
#define MULCHECK
	assert(data.size());
	assert(col() == other.row());
#endif
#ifndef ISSQUARE
#define ISSQUARE
	assert(isSquare());
#endif
#ifndef OTHERISSQUARE
#define OTHERISSQUARE
	assert(other.isSquare());
#endif
	vecSizeT n = row();
	StrassenMul(0, n, 0, n, other, ret);
}

/**
* ˹����ɭ�˷������Ӷ� n ^ 2.80
*/
template <typename T>
void mMatrix<T>::StrassenMul(vecSizeT rs, vecSizeT re, vecSizeT cs, vecSizeT ce, const mMatrix<T> &other, mMatrix<T> &ret) const {
#ifndef MULCHECK
#define MULCHECK
	assert(data.size());
	assert(col() == other.row());
#endif

	if (re - rs == 2 && ce - cs == 2) {
		vecSizeT rs1 = rs + 1;
		vecSizeT cs1 = cs + 1;
		T P1 = data[rs][cs] * (other[rs][cs1] - other[rs1][cs1]);
		T P2 = (data[rs][cs] + data[rs][cs1]) * other[rs1][cs1];
		T P3 = (data[rs1][cs] + data[rs1][cs1]) * other[rs][cs];
		T P4 = data[rs1][cs1] * (other[rs1][cs] - other[rs][cs]);
		T P5 = (data[rs][cs] + data[rs1][cs1]) * (other[rs][cs] + other[rs1][cs1]);
		T P6 = (data[rs][cs1] - data[rs1][cs1]) * (other[rs1][cs] + other[rs1][cs1]);
		T P7 = (data[rs][cs] - data[rs1][cs]) * (other[rs][cs] + other[rs][cs1]);
		ret[rs][cs] = P5 + P4 - P2 + P6;
		ret[rs][cs1] = P1 + P2;
		ret[rs1][cs] = P3 + P4;
		ret[rs1][cs1] = P1 + P5 - P3 - P7;
	}
	else if (re - rs < 2 || rs - rs < 2) {
		for (vecSizeT i = rs; i < re; ++i) {
			for (vecSizeT k = cs; k < ce; ++k) {
				for (vecSizeT j = cs; j < ce; ++j) {
					ret[i][j] += data[i][k] * other[k][j];
				}
			}
		}
	}
	else {
		vecSizeT rm = rs + ((re - rs) / 2);
		vecSizeT cm = cs + ((ce - cs) / 2);
		StrassenMul(rs, rm, cs, cm, other, ret);
		StrassenMul(rm, re, cs, cm, other, ret);
		StrassenMul(rs, rm, cm, ce, other, ret);
		StrassenMul(rm, re, cm, ce, other, ret);
	}
}

/**
* �Ӿ�����ȡһ����
* �� 0 ��ʼ���� re ����
* �����µ���һ�����󣬲�Ӱ��ԭ����
*/
template <typename T>
mMatrix<T> mMatrix<T>::cut(vecSizeT rs, vecSizeT re, vecSizeT cs, vecSizeT ce) const {
#ifndef NOTEMPTY
#define NOTEMPTY
	assert(!empty());
#endif
	assert(re < row() && rs >= 0 && ce < col() && cs >= 0);
	mMatrix<T> ret((re + 1) - rs, (ce + 1) - cs);

	for (vecSizeT i = rs, ri = 0; i <= re; ++i, ++ri) {
		for (vecSizeT j = cs, rj = 0; j <= ce; ++j, ++rj) {
			ret[ri][rj] = data[i][j];
		}
	}

	return ret;
}

/**
* �������
*/
template <typename T>
void mMatrix<T>::clear() {
	data.clear();
}

/**
* ��������
*/
template <typename T>
void mMatrix<T>::setZero() {
	vecSizeT n = row();
	vecSizeT m = col();

	for (vecSizeT i = 0; i < n; ++i) {
		std::memset(&data[i][0], 0, sizeof(T) * m);
	}
}

/**
* ��������
*/
template <typename T>
mMatrix<T> mMatrix<T>::operator = (const mMatrix<T> &other) {
	data = other.getData();
	return *this;
}

/**
* �ƶ�����
*/
template <typename T>
mMatrix<T> mMatrix<T>::operator = (mMatrix<T> &&other) {
	data.swap(other.getData());
	return *this;
}

/**
* ��ȡ data ��Ա���������������
*/
template <typename T>
std::vector<std::vector<T> > &mMatrix<T>::getData() {
	return data;
}

/**
* �� const ��ʽ��ȡ��Ա�������ڰ�ȫ��
*/
template <typename T>
const std::vector<std::vector<T> > &mMatrix<T>::getData() const {
	return data;
}

/**
* ���� 0 - 1 ֮���һ����̬�����
*/
template <typename T>
T mMatrix<T>::randn() {
	setRand();
	return normDis(*_genPtr);
}

/**
* ����һ�� n * n ��̬�������
* �������Ϊ����ı߳�
*/
template <typename T>
mMatrix<T> mMatrix<T>::randn(vecSizeT n) {
	setRand();
	mMatrix<T> mat(n, n);

	for (vecSizeT i = 0; i < n; ++i) {
		for (vecSizeT j = 0; j < n; ++j) {
			mat[i][j] = normDis(*_genPtr);
		}
	}

	return mat;
}

/**
* ����һ����̬�������
* �������Ϊ���������������
*/
template <typename T>
mMatrix<T> mMatrix<T>::randn(vecSizeT r, vecSizeT c) {
	setRand();
	mMatrix<T> mat(r, c);
	auto fun = std::bind(normDis, *_genPtr);

	for (vecSizeT i = 0; i < r; ++i) {
		for (vecSizeT j = 0; j < c; ++j) {
			mat[i][j] = normDis(*_genPtr);
		}
	}

	return mat;
}

/**
* ��ʼ�����������������
*/
template <typename T>
void mMatrix<T>::setRand() {
	if (!_genPtr) {
#ifdef linux
		std::random_device rd;
		_genPtr = new std::mt19937(rd());
#else
		_genPtr = new std::mt19937(std::time(NULL));
#endif
	}
}

/**
* �����ʼ�����������������
*/
template <typename T>
void mMatrix<T>::setRand(std::mt19937 *_p) {
	if (_genPtr) {
		delete _genPtr;
	}

	_genPtr = _p;
}

/**
* ��������Ǹ����������� 0 - 1 ֮���һ�����ȷֲ������
* ������������Σ����� 0 - 65525 ֮���һ�����ȷֲ������
*/
template <typename T>
T mMatrix<T>::rand() {
	setRand();

	if (SameType<T, double>::isSame) {
		return unifDoubleDis(*_genPtr);
	}
	else if (SameType<T, float>::isSame) {
		return unifFloatDis(*_genPtr);
	}
	else {
		return unifIntDis(*_genPtr);
	}
}

/**
* ����һ�� n * n ���ȷֲ��������
* �������Ϊ����ı߳�
*/
template <typename T>
mMatrix<T> mMatrix<T>::rand(vecSizeT n) {
	setRand();
	mMatrix<T> mat(n, n);

	for (vecSizeT i = 0; i < n; ++i) {
		for (vecSizeT j = 0; j < n; ++j) {
			mat[i][j] = rand();
		}
	}

	return mat;
}

/**
* ����һ�����ȷֲ��������
* �������Ϊ���������������
*/
template <typename T>
mMatrix<T> mMatrix<T>::rand(vecSizeT r, vecSizeT c) {
	setRand();
	mMatrix<T> mat(r, c);

	for (vecSizeT i = 0; i < r; ++i) {
		for (vecSizeT j = 0; j < c; ++j) {
			mat[i][j] = rand();
		}
	}

	return mat;
}