#ifndef LINSYS_H
#define LINSYS_H

#include <cstring>
#include <stdexcept>
#include <cmath>

namespace linsys
{
	template<std::size_t __dim__, class __elem_type__ = double>
	class vector
	{
	public:
		static const std::size_t dim = __dim__;
		using elem_type = __elem_type__;
		
	private:
		elem_type *ptr;
		
	public:
		vector() : ptr(new elem_type[dim]) {}
		
		vector(const vector<dim, elem_type> &other) : ptr(new elem_type[dim])
		{
			std::memcpy(ptr, other.ptr, sizeof(elem_type) * dim);
		}
		
		vector(vector<dim, elem_type> &&other) : ptr(other.ptr)
		{
			other.ptr = nullptr;
		}
		
		~vector() { delete[] ptr; }
		
		elem_type &operator[](const std::size_t i) { return ptr[i]; }
		
		const elem_type &operator[](const std::size_t i) const { return ptr[i]; }
		
		elem_type &at(const std::size_t i)
		{
			if (i >= dim)
				throw std::out_of_range("The index must be a non-negative value less than the dimension.");
			return ptr[i];
		}
		
		const elem_type &at(const std::size_t i) const
		{
			if (i >= dim)
				throw std::out_of_range("The index must be a non-negative value less than the dimension.");
			return ptr[i];
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
	
	template<std::size_t dim, class elem_type>
	auto Euclidean_distance(const vector<dim, elem_type> &a, const vector<dim, elem_type> &b)
	{
		auto d = std::abs(a[0] - b[0]);
		auto s = d * d;
		for (std::size_t i = 1; i < dim; ++i)
		{
			d = std::abs(a[i] - b[i]);
			s += d * d;
		}
		return std::sqrt(s);
	}
	
	template<std::size_t __dim__, class __elem_type__ = double>
	class matrix
	{
	public:
		static const std::size_t dim = __dim__;
		using elem_type = __elem_type__;
		
	private:
		elem_type *ptr;
		
	public:
		matrix() : ptr(new elem_type[dim * dim]) {}
		
		matrix(const matrix<dim, elem_type> &other) : ptr(new elem_type[dim * dim])
		{
			std::memcpy(ptr, other.ptr, sizeof(elem_type) * dim * dim);
		}
		
		matrix(matrix<dim, elem_type> &&other) : ptr(other.ptr)
		{
			other.ptr = nullptr;
		}
		
		~matrix() { delete[] ptr; }
		
		elem_type *operator[](const std::size_t i) { return ptr + (i * dim); }
		
		const elem_type *operator[](const std::size_t i) const { return ptr + (i * dim); }
		
		elem_type &at(const std::size_t i, const std::size_t j)
		{
			if (i >= dim || j >= dim)
				throw std::out_of_range("Indexes must be non-negative values less than the dimension.");
			return ptr[i * dim + j];
		}
		
		const elem_type &at(const std::size_t i, const std::size_t j) const
		{
			if (i >= dim || j >= dim)
				throw std::out_of_range("Indexes must be non-negative values less than the dimension.");
			return ptr[i * dim + j];
		}
		
		auto prod(const vector<dim, elem_type> &vect) const
		{
			vector<dim, elem_type> result;
			for (std::size_t i = 0; i < dim; ++i)
			{
				result[i] = operator[](i)[0] * vect[0];
				for (std::size_t j = 1; j < dim; ++j)
					result[i] += operator[](i)[j] * vect[j];
			}
			return result;
		}
	};
	
	template<std::size_t dim, class elem_type>
	auto Gaussian_method(matrix<dim, elem_type> matr, vector<dim, elem_type> vect)
	{
		for (std::size_t i = 0; i < dim; ++i)
		{
			for (std::size_t j = i; j < dim; ++j)
			{
				
			}
		}
		vector<dim, elem_type> result;
	}
	
	template<std::size_t dim, class elem_type>
	auto QRdecompos_method(matrix<dim, elem_type> matr, vector<dim, elem_type> vect)
	{
		
	}
}

#endif