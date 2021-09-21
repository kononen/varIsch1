#include <iostream>
#include "linsys.h"
#include "iolin.h"

using vector_t = linsys::vector<>;
using matrix_t = linsys::matrix<>;

int main(int argc, char **argv)
{
	std::size_t d;
	std::cin >> d;
	matrix_t a(d); vector_t b(d);
	
	std::cin >> augmented_mut(a, b); // enter d * (d + 1) numbers
	
	std::cout << "a := coeff(input)\na -> matrix\n"
	          << formatter(a, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	std::cout << "b := right(input)\nb -> vector\n"
	          << formatter(b, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	try
	{
		const vector_t x = Gaussian_method(a, b);
		
		std::cout << "x := Gaussian_method(a, b)\nx -> vector\n"
		          << formatter(x, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
		
		std::cout << "dist_e(a * x, b) -> " << Euclidean_distance(a.prod(x), b) << "\n";
	}
	catch (std::invalid_argument exc)
	{
		std::cout << "[EXCEPTION] " << exc.what() << "\n";
	}
	
	return 0;
}