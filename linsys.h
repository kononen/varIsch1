#ifndef LINSYS_H
#define LINSYS_H

#include <cstring>
#include <stdexcept>
#include <cmath>
#include <limits>
#include <utility>

namespace linsys
{
	template<class T>
	bool iszero(const T arg)
	{
		return std::abs(arg) <= std::numeric_limits<T>::epsilon();
	}
	
	template<>
	bool iszero(const double arg)
	{
		return std::abs(arg) <= 1e-15;
	}
	
	template<>
	bool iszero(const float arg)
	{
		return std::abs(arg) <= 1e-6;
	}
	
	template<class T = double>
	class vector
	{	
	private:
		T *ptr;
		
	public:
		std::size_t dim;
		using elem_type = T;
		
		vector() : dim(0), ptr(nullptr) {}
		
		vector(const std::size_t d) : dim(d), ptr(new T[d]) {}
		
		// !!! DO NOT USE UNLESS ABSOLUTELY NECESSARY !!!
		vector(T *p, const std::size_t d) : dim(d), ptr(p) {}
		
		vector(const vector<T> &other) : dim(other.dim), ptr(new T[other.dim])
		{
			std::memcpy(ptr, other.ptr, sizeof(T) * dim);
		}
		
		template<class U>
		explicit vector(const vector<U> &other) : dim(other.dim), ptr(new T[other.dim])
		{
			for (std::size_t i = 0; i < dim; ++i)
				ptr[i] = (T)other[i];
		}
		
		vector(vector<T> &&other) : dim(other.dim), ptr(other.ptr)
		{
			other.ptr = nullptr;
		}
		
		vector<T> &operator=(const vector<T> &other)
		{
			if (dim != other.dim)
			{
				delete[] ptr;
				dim = other.dim;
				ptr = new T[dim];
			}
			std::memcpy(ptr, other.ptr, sizeof(T) * dim);
			return *this;
		}
		
		vector<T> &operator=(vector<T> &&other)
		{
			dim = other.dim;
			std::swap(ptr, other.ptr);
			return *this;
		}
		
		~vector() { delete[] ptr; }
		
		const T *get_ptr() const { return ptr; }
		
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
		
		template<class distribution, class generator>
		vector<T> &fill_random(distribution &dis, generator &gen)
		{
			for (std::size_t i = 0; i < dim; ++i)
				ptr[i] = dis(gen);
			return *this;
		}
		
		template<class distribution, class generator>
		static auto random(const std::size_t d, distribution &dis, generator &gen)
		{
			vector<T> result(d);
			return result.fill_random(dis, gen);
		}
	};
	
	template<class T>
	auto Euclidean_distance(const vector<T> &a, const vector<T> &b)
	{
		if (a.dim != b.dim) throw std::invalid_argument("Mismatch of dimensions.");
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
	private:
		T *ptr;
		
	public:
		std::size_t dim;
		using elem_type = T;
		
		class row
		{
		private:
			T *p;
			const std::size_t d;
			row(T *new_p, const std::size_t new_d) : p(new_p), d(new_d) {}
			
		public:
			T &operator[](const std::size_t i) { return p[i]; }
			const T &operator[](const std::size_t i) const { return p[i]; }
			
			auto to_vector() const
			{
				T *arr = new T[d];
				std::memcpy(arr, p, sizeof(T) * d);
				return vector<T>(arr, d);
			}
			
			row &set(const vector<T> &v)
			{
				if (d != v.dim) throw std::invalid_argument("Mismatch of dimensions.");
				std::memcpy(p, v.get_ptr(), sizeof(T) * d);
				return *this;
			}
			
			friend row matrix<T>::operator[](const std::size_t i);
		};
		
		class const_row
		{
		private:
			const T *p;
			const std::size_t d;
			const_row(const T *new_p, const std::size_t new_d) : p(new_p), d(new_d) {}
			
		public:
			const T &operator[](const std::size_t i) const { return p[i]; }
			
			auto to_vector() const
			{
				T *arr = new T[d];
				std::memcpy(arr, p, sizeof(T) * d);
				return vector<T>(arr, d);
			}
			
			friend const_row matrix<T>::operator[](const std::size_t i) const;
		};
		
		matrix() : dim(0), ptr(nullptr) {}
		
		matrix(const std::size_t d) : dim(d), ptr(new T[d * d]) {}
		
		matrix(const matrix<T> &other) : dim(other.dim), ptr(new T[other.dim * other.dim])
		{
			std::memcpy(ptr, other.ptr, sizeof(T) * dim * dim);
		}
		
		template<class U>
		explicit matrix(const matrix<U> &other) : dim(other.dim), ptr(new T[other.dim * other.dim])
		{
			for (std::size_t i = 0; i < dim; ++i)
			{
				auto row = operator[](i);
				auto other_row = other[i];
				for (std::size_t j = 0; j < dim; ++j)
					row[j] = (T)other_row[j];
			}
		}
		
		matrix(matrix<T> &&other) : dim(other.dim), ptr(other.ptr)
		{
			other.ptr = nullptr;
		}
		
		matrix<T> &operator=(const matrix<T> &other)
		{
			if (dim != other.dim)
			{
				delete[] ptr;
				dim = other.dim;
				ptr = new T[dim * dim];
			}
			std::memcpy(ptr, other.ptr, sizeof(T) * dim * dim);
			return *this;
		}
		
		matrix<T> &operator=(matrix<T> &&other)
		{
			dim = other.dim;
			std::swap(ptr, other.ptr);
			return *this;
		}
		
		~matrix() { delete[] ptr; }
		
		const T *get_ptr() const { return ptr; }
		
		row operator[](const std::size_t i) { return row(ptr + (i * dim), dim); }
		
		const_row operator[](const std::size_t i) const { return const_row(ptr + (i * dim), dim); }
		
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
		
		auto prod(const vector<T> &vect) const
		{
			if (dim != vect.dim) throw std::invalid_argument("Mismatch of dimensions.");
			vector<T> result(dim);
			for (std::size_t i = 0; i < dim; ++i)
			{
				result[i] = operator[](i)[0] * vect[0];
				for (std::size_t j = 1; j < dim; ++j)
					result[i] += operator[](i)[j] * vect[j];
			}
			return result;
		}
		
		auto transpose() const
		{
			matrix<T> result(dim);
			for (std::size_t i = 0; i < dim; ++i)
			{
				auto row = operator[](i);
				for (std::size_t j = 0; j < dim; ++j)
					result[j][i] = row[j];
			}
			return result;
		}
		
		auto spec_prod(const matrix<T> &other) const
		{
			if (dim != other.dim) throw std::invalid_argument("Mismatch of dimensions.");
			matrix<T> result(dim);
			for (std::size_t i = 0; i < dim; ++i)
			{
				auto a = operator[](i);
				auto r = result[i];
				for (std::size_t j = 0; j < dim; ++j)
				{
					auto b = other[j];
					auto &e = r[j];
					e = a[0] * b[0];
					for (std::size_t k = 1; k < dim; ++k)
						e += a[k] * b[k];
				}
			}
			return result;
		}
		
		auto operator*(const matrix<T> &other) const
		{
			return spec_prod(other.transpose());
		}
		
		matrix<T> &fill_identity()
		{
			for (std::size_t i = 0; i < dim; ++i)
			{
				auto row = operator[](i);
				for (std::size_t j = 0; j < i; ++j) row[j] = 0;
				row[i] = 1;
				for (std::size_t j = i + 1; j < dim; ++j) row[j] = 0;
			}
			return *this;
		}
		
		static auto identity(const std::size_t d)
		{
			matrix<T> result(d);
			return result.fill_identity();
		}
		
		template<class distribution, class generator>
		matrix<T> &fill_random(distribution &dis, generator &gen)
		{
			for (std::size_t i = 0; i < dim * dim; ++i)
				ptr[i] = dis(gen);
			return *this;
		}
		
		template<class distribution, class generator>
		static auto random(const std::size_t d, distribution &dis, generator &gen)
		{
			matrix<T> result(d);
			return result.fill_random(dis, gen);
		}
		
		auto back_substitution(const vector<T> &vect) const
		{
			if (dim != vect.dim) throw std::invalid_argument("Mismatch of dimensions.");
			
			vector<T> result(dim);
			result[dim - 1] = vect[dim - 1] / operator[](dim - 1)[dim - 1];
			for (std::size_t i = dim - 2; i < i + 1; --i)
			{
				auto row = operator[](i);
				auto s = row[i + 1] * result[i + 1];
				for (std::size_t j = i + 2; j < dim; ++j)
					s += row[j] * result[j];
				result[i] = (vect[i] - s) / row[i];
			}
			return result;
		}
		
		auto spec_QR_decomposition() const
		{
			std::pair<matrix<T>, matrix<T>> result;
			result.first = identity(dim);
			result.second = *this;
			
			for (std::size_t i = 0; i < dim - 1; ++i)
			{
				auto mtop = result.second[i], qtop = result.first[i];
				for (std::size_t j = i + 1; j < dim; ++j)
				{
					auto mcur = result.second[j], qcur = result.first[j];
					if (!iszero(mcur[i]))
					{
						const T a = mtop[i], b = mcur[i];
						const T h = std::hypot(a, b);
						const T c = a / h, s = b / h;
						
						mtop[i] = c * mtop[i] + s * mcur[i];
						for (std::size_t k = i + 1; k < dim; ++k)
						{
							const T buffer = c * mtop[k] + s * mcur[k];
							mcur[k] = -s * mtop[k] + c * mcur[k];
							mtop[k] = buffer;
						}
						
						for (std::size_t k = 0; k < dim; ++k)
						{
							const T buffer = c * qtop[k] + s * qcur[k];
							qcur[k] = -s * qtop[k] + c * qcur[k];
							qtop[k] = buffer;
						}
					}
				}
				if (iszero(mtop[i]))
					throw std::invalid_argument("The matrix cannot be decomposed because it is singular.");
			}
			if (iszero(result.second[dim - 1][dim - 1]))
				throw std::invalid_argument("The matrix cannot be decomposed because it is singular.");
			
			return result;
		}
		
		auto QR_decomposition() const
		{
			auto result = spec_QR_decomposition();
			result.first = result.first.transpose();
			return result;
		}
		
		auto inverse() const
		{
			auto qr = QR_decomposition();
			matrix<T> result(dim);
			for (std::size_t i = 0; i < dim; ++i)
				result[i].set(qr.second.back_substitution(qr.first[i].to_vector()));
			return result.transpose();
		}
	};
	
	template<class T>
	auto Gaussian_method(matrix<T> matr, vector<T> vect)
	{
		const auto dim = matr.dim;
		if (dim != vect.dim) throw std::invalid_argument("Mismatch of dimensions.");
		
		for (std::size_t i = 0; i < dim; ++i)
		{
			std::size_t i_max = i;
			for (std::size_t j = i + 1; j < dim; ++j)
				if (std::abs(matr[i_max][i]) < std::abs(matr[j][i]))
					i_max = j;
			if (iszero(matr[i_max][i]))
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
				const auto quot = cur_row[i] / top_row[i];
				for (std::size_t k = i + 1; k < dim; ++k)
					cur_row[k] -= quot * top_row[k];
				vect[j] -= quot * vect[i];
			}
		}
		
		return matr.back_substitution(vect);
	}
	
	template<class T>
	struct QR_decomposition_method_result_t
	{
		matrix<T> Q, R;
		vector<T> X;
	};
	
	template<class T>
	QR_decomposition_method_result_t<T> QR_decomposition_method(matrix<T> matr, vector<T> vect)
	{
		const auto dim = matr.dim;
		if (dim != vect.dim) throw std::invalid_argument("Mismatch of dimensions.");
		
		const auto qr = matr.spec_QR_decomposition();
		
		vect = qr.first.prod(vect);
		
		return { qr.first.transpose(), qr.second, qr.second.back_substitution(vect) };
	}
}

#endif
