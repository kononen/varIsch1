#ifndef LINSYS
#define LINSYS

#include <cstring>
#include <stdexcept>

namespace linsys
{
	template<std::size_t __dim__, class __elem_type__ = double>
	class matrix
	{
	public:
		static const std::size_t dim = __dim__;
		using elem_type = __elem_type__;
		
	private:
		elem_type *ptr;
		
	public:
		matrix() : ptr = new elem_type[dim * dim] {}
		
		matrix(const matrix &other) : ptr = new elem_type[dim * dim]
		{
			std::memcpy(ptr, other.ptr, sizeof(elem_type) * dim * dim);
		}
		
		~matrix() { delete[] ptr; }
		
		elem_type &elem(const std::size_t i, const std::size_t j)
		{
			if (i >= dim || j >= dim)
				throw std::out_of_range("Indexes must be non-negative values less than the dimension.");
			return ptr[i * dim + j];
		}
		
		const elem_type &elem(const std::size_t i, const std::size_t j) const
		{
			if (i >= dim || j >= dim)
				throw std::out_of_range("Indexes must be non-negative values less than the dimension.");
			return ptr[i * dim + j];
		}
	};
	
	template<std::size_t __dim__, class __elem_type__ = double>
	class vector
	{
	public:
		static const std::size_t dim = __dim__;
		using elem_type = __elem_type__;
		
	private:
		elem_type *ptr;
		
	public:
		vector() : ptr = new elem_type[dim] {}
		
		vector(const vector &other)
		{
			std::memcpy(ptr, other.ptr, sizeof(elem_type) * dim);
		}
		
		~vector() { delete[] ptr; }
		
		elem_type &elem(const std::size_t i)
		{
			if (i >= dim)
				throw std::out_of_range("The index must be a non-negative value less than the dimension.");
			return ptr[i];
		}
		
		const elem_type &elem(const std::size_t i) const
		{
			if (i >= dim)
				throw std::out_of_range("The index must be a non-negative value less than the dimension.");
			return ptr[i];
		}
	};
	
	template<std::size_t dim, class elem_type = double>
	vector<dim, elem_type> Gaussian_method(matrix<dim, elem_type> matr, vector<dim, elem_type> vect)
	{
		for (std::size_t i = 0; i < dim; ++i)
		{
			for (std::size_t j = i; j < dim; ++j)
			{
				
			}
		}
		vector<dim, elem_type> result;
	}
	
	template<std::size_t dim, class elem_type = double>
	vector<dim, elem_type> QRdecompos_method(matrix<dim, elem_type> matr, vector<dim, elem_type> vect)
	{
		
	}
}

#endif
