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

using std::cout;
using std::endl;
namespace imgmaker
{
	using vecSizeT = size_t;

	// 单线程随机数生成器，使用 setRand
	static std::mt19937 *_genPtr;
	static std::normal_distribution<double> normDis(0, 1);
	static std::uniform_real_distribution<double> unifDoubleDis(0, 1);
	static std::uniform_real_distribution<float> unifFloatDis(0, 1);
	static std::uniform_int_distribution<int> unifIntDis(0, 65535);

	// 辅助代码
	// =========================================
	// 用来判断类别是否相同
	// =========================================
	template <typename T, typename U>
	struct SameType {
		static const bool isSame = false;
	};

	template <typename T>
	struct SameType<T, T> {
		static const bool isSame = true;
	};

	// 用来判断类别是否是复数
	// =========================================
	template <typename T>
	struct ComplexType {
		static const bool isComplex = false;
	};

	template <typename T>
	struct ComplexType <std::complex<T> > {
		static const bool isComplex = true;
	};

	// 重载判断复数的大小
	// =========================================
	template <typename T>
	bool operator < (const std::complex<T> &lhs, const std::complex<T> &rhs) {
		return lhs.real() < rhs.real();
	}

	template <typename T>
	bool operator < (const std::complex<T> &lhs, const T &rhs) {
		return lhs.real() < rhs.real();
	}


	class Exception {

	public:
		explicit Exception(const std::string &_m) : message(_m) {
		}

		void printMessage() const {
			std::cout << message << std::endl;
		}

	private:
		std::string message;
	};

	// 矩阵的逆不存在 - 异常类
	class NoInverseException : public Exception {

	};

	// 复数矩阵无法进行这个运算 - 异常类
	class ComplexTypeCantDo : public Exception {

	};

	// 辅助代码结束
	// =========================================

	template <typename T>
	class mMatrix 
	{
	public:
		//initial func
		mMatrix() = default;
		mMatrix(mMatrix<T> &&other);
		mMatrix(const mMatrix<T> &other);
		mMatrix(vecSizeT _x);
		mMatrix(vecSizeT _x, vecSizeT _y);
		mMatrix(std::vector<std::vector<T> > dvec);
		//rand matrix
		static void inline setRand();
		static void inline setRand(std::mt19937 *_p);
		static T inline randn();
		static mMatrix<T> inline randn(vecSizeT n);
		static mMatrix<T> inline randn(vecSizeT r, vecSizeT c);

		static T inline rand();
		static mMatrix<T> inline rand(vecSizeT n);
		static mMatrix<T> inline rand(vecSizeT r, vecSizeT c);

		// static T inline random();
		void inline clear();
		void inline swap(mMatrix<T> &rhs) { data.swap(rhs.getData());	}
		void inline setZero();
		std::vector<std::vector<T> > &getData();
		const std::vector<std::vector<T> > &getData() const;

		vecSizeT inline col() const;
		vecSizeT inline row() const;

		mMatrix<T> inline cut(vecSizeT rs, vecSizeT re, vecSizeT cs, vecSizeT ce) const;
		mMatrix<T> inline row(vecSizeT index) const;

		mMatrix<double> toDouble() const;
		mMatrix<double> inv() const;
		mMatrix<T> cov() const;
		mMatrix<double> hess() const;
		mMatrix<std::complex<double>> eig(double eps = 1e-12, unsigned LOOP = 100000) const;

		void mul(mMatrix<T> &ret, const mMatrix<T> &other) const;
		void smul(mMatrix<T> &ret, const mMatrix<T> &other) const;
		void StrassenMul(vecSizeT rs, vecSizeT re, vecSizeT cs, vecSizeT ce, const mMatrix<T> &other, mMatrix<T> &ret) const;
		mMatrix<double> div(const mMatrix<T> &other) const;
		mMatrix<double> rdiv(const mMatrix<T> &other) const;

		T inline max() const;
		T inline min() const;
		T inline avg() const;
		std::complex<double> cond2() const;

		static T vectorDotProduct(const std::vector<T> lhs, std::vector<T> rhs);
		static mMatrix<T> cov(const mMatrix<T> &input);
		static mMatrix<T> eye(vecSizeT _x, vecSizeT _y);
		static T inline avg(const std::vector<T> &vec);

		bool inline empty() const;
		bool inline isSquare() const;
		bool inline isSingular() const;

		std::complex<double> det() const;
		mMatrix<T> getTransposition() const;

		std::vector<T> &operator [](vecSizeT index);
		const std::vector<T> &operator [](vecSizeT index) const;
		mMatrix<T> operator = (const mMatrix<T> &other);
		mMatrix<T> operator = (mMatrix<T> &&other);
		mMatrix<T> inline operator + (const mMatrix<T> &other) const;
		mMatrix<T> inline operator - (const mMatrix<T> &other) const;
		mMatrix<T> inline operator * (const mMatrix<T> &other) const;
		mMatrix<double> inline operator / (const mMatrix<T> &other) const;
		mMatrix<double> inline operator % (const mMatrix<T> &other) const;
		mMatrix<T> inline operator *= (const mMatrix<T> &other);
		mMatrix<T> inline operator += (const mMatrix<T> &other);
		mMatrix<T> inline operator -= (const mMatrix<T> &other);
		mMatrix<double> inline operator /= (const mMatrix<T> &other);

		/*
		* 矩阵快速幂
		* 参数需要一个当前类类型成员，出于泛型考虑使用 friend 实现
		* 友元模板实现
		*/
		friend mMatrix<T> inline operator ^ (const mMatrix<T> &mat, unsigned exponent) 
		{
			mMatrix<T> ans = eye(mat.row(), mat.col());
			mMatrix<T> src = mat;

			for (; exponent; exponent >>= 1) {
				if (exponent & 1) {
					ans *= src;
				}

				src *= src;
			}
			return ans;
		}

		/**
		* 友元模板实现
		*/
		friend std::ostream &operator << (std::ostream &o, const mMatrix<T> &mat) {
			// 判断要输出的数是否是 double 类型
			bool dFlag = SameType<T, double>::isSame;

			if (dFlag) {
				using std::ios;
				using std::setprecision;
				o << setiosflags(ios::right) << setiosflags(ios::scientific) << setprecision(4);
			}

			for (vecSizeT i = 0; i != mat.data.size(); ++i) {
				for (vecSizeT j = 0; j != mat.data[i].size(); ++j) {
					if (dFlag) {
						o << std::setw(12) << mat.data[i][j] << ' ';
					}
					else {
						o << mat.data[i][j] << ' ';
					}
				}

				if (i < mat.data.size() - 1) {
					o << '\n';
				}
			}

			o << std::endl;
			return o;
		}

	private:
		std::vector<std::vector<T> > data;
		static std::mt19937 gen;
	};

}
