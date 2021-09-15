#ifndef LINSYS_H
#define LINSYS_H

#include <cstring>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <list>
#include <utility>

namespace linsys
{
	template<class T = double>
	class vector
	{
	public:
		const std::size_t dim;
		using elem_type = T;
		
	private:
		T *ptr;
		
	public:
		vector(const std::size_t d) : dim(d), ptr(new T[d]) {}
		
		vector(const vector<T> &other) : dim(other.dim), ptr(new T[dim])
		{
			std::memcpy(ptr, other.ptr, sizeof(T) * dim);
		}
		
		vector(vector<T> &&other) : dim(other.dim), ptr(other.ptr)
		{
			other.ptr = nullptr;
		}
		
		~vector() { delete[] ptr; }
		
		T &operator[](const std::size_t i) { return ptr[i]; }
		
		const T &operator[](const std::size_t i) const { return ptr[i]; }
		
		T &at(const std::size_t i)
		{
			if (i >= dim)
				throw std::out_of_range("The index must be a non-negative value less than the dimension.");
			return ptr[i];
		}
		
		const T &at(const std::size_t i) const
		{
			if (i >= dim)
				throw std::out_of_range("The index must be a non-negative value less than the dimension.");
			return ptr[i];
		}
		
		void swap_in_self(const std::size_t i, const std::size_t j)
		{
			if (i >= dim || j >= dim)
				throw std::out_of_range("Indexes must be non-negative values less than the dimension.");
			auto t = ptr[i];
			ptr[i] = ptr[j];
			ptr[j] = t;
		}
		
		auto oct_norm() const
		{
			auto result = std::abs(ptr[0]);
			for (std::size_t i = 1; i < dim; ++i)
				result += std::abs(ptr[i]);
			return result;
		}
		
		auto sph_norm() const
		{
			auto e = std::abs(ptr[0]);
			auto s = e * e;
			for (std::size_t i = 1; i < dim; ++i)
			{
				e = std::abs(ptr[i]);
				s += e * e;
			}
			return std::sqrt(s);
		}
		
		auto cub_norm() const
		{
			auto result = std::abs(ptr[0]);
			for (std::size_t i = 1; i < dim; ++i)
			{
				auto e = std::abs(ptr[i]);
				if (e > result) result = e;
			}
			return result;
		}
	};
	
	template<class T>
	auto Euclidean_distance(const vector<T> &a, const vector<T> &b)
	{
		if (a.dim != b.dim) throw std::invalid_argument("Mismatch of dimentions.");
		auto d = std::abs(a[0] - b[0]);
		auto s = d * d;
		for (std::size_t i = 1; i < a.dim; ++i)
		{
			d = std::abs(a[i] - b[i]);
			s += d * d;
		}
		return std::sqrt(s);
	}
	
	template<class T = double>
	class matrix
	{
	public:
		const std::size_t dim;
		using elem_type = T;
		
	private:
		T *ptr;
		
	public:
		matrix(const std::size_t d) : dim(d), ptr(new T[d * d]) {}
		
		matrix(const matrix<T> &other) : dim(other.dim), ptr(new T[dim * dim])
		{
			std::memcpy(ptr, other.ptr, sizeof(T) * dim * dim);
		}
		
		matrix(matrix<T> &&other) : dim(other.dim), ptr(other.ptr)
		{
			other.ptr = nullptr;
		}
		
		~matrix() { delete[] ptr; }
		
		T *operator[](const std::size_t i) { return ptr + (i * dim); }
		
		const T *operator[](const std::size_t i) const { return ptr + (i * dim); }
		
		T &at(const std::size_t i, const std::size_t j)
		{
			if (i >= dim || j >= dim)
				throw std::out_of_range("Indexes must be non-negative values less than the dimension.");
			return ptr[i * dim + j];
		}
		
		const T &at(const std::size_t i, const std::size_t j) const
		{
			if (i >= dim || j >= dim)
				throw std::out_of_range("Indexes must be non-negative values less than the dimension.");
			return ptr[i * dim + j];
		}
		
		auto prod(const vector<T> &vect) const
		{
			if (dim != vect.dim) throw std::invalid_argument("Mismatch of dimentions.");
			vector<T> result(dim);
			for (std::size_t i = 0; i < dim; ++i)
			{
				result[i] = operator[](i)[0] * vect[0];
				for (std::size_t j = 1; j < dim; ++j)
					result[i] += operator[](i)[j] * vect[j];
			}
			return result;
		}
		
		void swap_rows_in_self(const std::size_t i, const std::size_t j)
		{
			if (i >= dim || j >= dim)
				throw std::out_of_range("Indexes must be non-negative values less than the dimension.");
			
			T *pt = new T[dim];
			T *pi = ptr + (i * dim);
			T *pj = ptr + (j * dim);
			
			std::memcpy(pt, pi, sizeof(T) * dim);
			std::memcpy(pi, pj, sizeof(T) * dim);
			std::memcpy(pj, pt, sizeof(T) * dim);
			
			delete[] pt;
		}
	};
	
	template<class T>
	auto Gaussian_method(matrix<T> matr, vector<T> vect, std::list<std::pair<matrix<T>, vector<T>>> &li)
	{
		auto dim = matr.dim;
		if (dim != vect.dim) throw std::invalid_argument("Mismatch of dimentions.");
		
		for (std::size_t i = 0; i < dim; ++i)
		{
			std::size_t i_max = i;
			for (std::size_t j = i + 1; j < dim; ++j)
				if (std::abs(matr[i_max][i]) < std::abs(matr[j][i]))
					i_max = j;
			if (std::abs(matr[i_max][i]) < std::numeric_limits<T>::epsilon())
				throw std::invalid_argument("The matrix of coefficients is singular.");
			
			if (i != i_max)
			{
				matr.swap_rows_in_self(i, i_max);
				vect.swap_in_self(i, i_max);
			}
			
			auto top_row = matr[i];
			for (std::size_t j = i + 1; j < dim; ++j)
			{
				auto cur_row = matr[j];
				auto quot = cur_row[i] / top_row[i];
				for (std::size_t k = i + 1; k < dim; ++k)
					cur_row[k] -= quot * top_row[k];
				vect[j] -= quot * vect[i];
				li.emplace_back(matr, vect);
			}
		}
		
		vector<T> result(dim);
		result[dim - 1] = vect[dim - 1] / matr[dim - 1][dim - 1];
		for (std::size_t i = dim - 2; i < i + 1; --i)
		{
			auto row = matr[i];
			auto s = row[i + 1] * result[i + 1];
			for (auto j = i + 2; j < dim; ++j)
				s += row[j] * result[j];
			result[i] = (vect[i] - s) / row[i];
		}
		return result;
	}
	
	template<class T>
	auto QRdecompos_method(matrix<T> matr, vector<T> vect)
	{
		
	}
}

#endif