// Предварительный набросок
#ifndef LINEAR_SYSTEMS
#define LINEAR_SYSTEMS

#include <cstring>

namespace linear_systems
{
	template<std::size_t __dim__, class __elem_type__ = double>
	class matrix
	{
	public:
		static const std::size_t dim = __dim__;
		using elem_type = __elem_type__;
		
	private:
		elem_type **ptr;
		
	public:
		matrix() : ptr = new elem_type*[dim]
		{
			for (std::size_t i = 0; i < dim; ++i)
				ptr[i] = new elem_type[dim];
		}
		
		matrix(const matrix &other) : ptr = new elem_type*[dim]
		{
			for (std::size_t i = 0; i < dim; ++i)
				std::memcpy(ptr[i], other.ptr[i], sizeof(elem_type) * dim);
		}
		
		~matrix()
		{
			for (std::size_t i = 0; i < dim; ++i)
				delete[] ptr[i];
			delete[] ptr;
		}
		
		elem_type &elem(const std::size_t i, const std::size_t j)
		{
			return ptr[i][j];
		}
		
		const elem_type &elem(const std::size_t i, const std::size_t j) const
		{
			return ptr[i][j];
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
		
		elem_type &elem(const std::size_t i) { return ptr[i]; }
		
		const elem_type &elem(const std::size_t i) const { return ptr[i]; }
	};
	
	template<std::size_t dim, class elem_type = double>
	vector<dim, elem_type> solve(matrix<dim, elem_type> matr, vector<dim, elem_type> vect)
	{
		for (std::size_t i = 0; i < dim; ++i)
		{
			for (std::size_t j = i; j < dim; ++j)
			{
				
			}
		}
		vector<dim, elem_type> result;
	}
}

#endif
