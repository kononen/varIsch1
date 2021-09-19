#include <iostream>
#include "linsys.h"
#include "iolin.h"

using vector_t = linsys::vector<>;
using matrix_t = linsys::matrix<>;

int main(int argc, char **argv)
{
	vector_t vect(3);
	
	std::cin >> vect; // enter 3 numbers
	// you can also try to print <vect> without <formatter>...
	std::cout << "vect := input\nvect -> vector\n"
	          << formatter(vect, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	// ... or fill it in the code
	/*vect[0] = 9;
	vect[1] = 5;
	vect[2] = 7;
	
	for (std::size_t i = 0; i < vect.dim; ++i)
		std::cout << vect[i] << " ";
	std::cout << "\n\n";//*/
	
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
	
	vector_t prod = matr.prod(vect); // product of <matr> and <vect>
	
	std::cout << "prod := matr * vect\nprod -> vector\n"
	          << formatter(prod, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	/*for (std::size_t i = 0; i < prod.dim; ++i)
		std::cout << prod[i] << " ";
	std::cout << "\n\n";//*/
	
	// you can also try to call methods <at> with invalid parameters
	/*vect.at(4);
	matr.at(5, 1);//*/
	
	return 0;
}