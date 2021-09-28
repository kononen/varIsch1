#include <iostream>
#include "linsys.h"
#include "iolin.h"

using matrix_t = linsys::matrix<>;

int main(int argc, char **argv)
{
	matrix_t matr(3);
	
	std::cin >> matr; // enter 9 numbers
	// you can also try to print <matr> without <formatter>...
	std::cout << "matr := input\nmatr -> matrix\n"
	          << formatter(matr, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	// ... or fill it in the code
	/*matr[0][0] = 7; matr[0][1] = 2; matr[0][2] = 9;
	matr[1][0] = 6; matr[1][1] = 4; matr[1][2] = 5;
	matr[2][0] = 1; matr[2][1] = 8; matr[2][2] = 3;
	
	for (std::size_t i = 0; i < matr.dim; ++i)
	{
		for (std::size_t j = 0; j < matr.dim; ++j)
			std::cout << matr[i][j] << " ";
		std::cout << "\n";
	}
	std::cout << "\n";//*/
	
	auto invm = matr.inverse();
	
	std::cout << "matr^-1 -> matrix\n"
	          << formatter(invm, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	std::cout << "matr * matr^-1 -> matrix\n"
	          << formatter(matr * invm, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	return 0;
}
