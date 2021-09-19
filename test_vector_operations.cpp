#include <iostream>
#include "linsys.h"
#include "iolin.h"

using vector_t = linsys::vector<>;

int main(int argc, char **argv)
{
	vector_t a(3), b(3);
	
	std::cin >> a; // enter 3 numbers
	// you can also try to print <a> without <formatter>...
	std::cout << "a := input\na -> vector\n"
	          << formatter(a, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	// ... or fill it in the code
	/*a[0] = 9;
	a[1] = 5;
	a[2] = 7;
	
	for (std::size_t i = 0; i < a.dim; ++i)
		std::cout << a[i] << " ";
	std::cout << "\n\n";//*/
	
	std::cin >> b;
	std::cout << "b := input\nb -> vector\n"
	          << formatter(b, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	std::cout << "dist_e(a, b) -> " << Euclidean_distance(a, b) << "\n";
	std::cout << "||a||_oct -> " << a.oct_norm() << "\n";
	std::cout << "||a||_sph -> " << a.sph_norm() << "\n";
	std::cout << "||a||_cub -> " << a.cub_norm() << "\n";
	
	return 0;
}