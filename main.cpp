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
	          << make_formatter(vect, std::ios::fixed | std::ios::right, 8, 3) << "end\n";
	
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
	          << make_formatter(matr, std::ios::fixed | std::ios::right, 8, 3) << "end\n";
	
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
	          << make_formatter(prod, std::ios::fixed | std::ios::right, 8, 3) << "end\n";
	
	/*for (std::size_t i = 0; i < prod.dim; ++i)
		std::cout << prod[i] << " ";
	std::cout << "\n\n";//*/
	
	// you can also try to call methods <at> with invalid parameters
	/*vect.at(4);
	matr.at(5, 1);//*/
	
	std::cout << "dist_e(vect, prod) -> " << Euclidean_distance(vect, prod) << "\n";
	std::cout << "||vect||_oct -> " << vect.oct_norm() << "\n";
	std::cout << "||vect||_sph -> " << vect.sph_norm() << "\n";
	std::cout << "||vect||_cub -> " << vect.cub_norm() << "\n";
	
	std::size_t d;
	std::cin >> d;
	matrix_t a(d); vector_t b(d);
	
	std::cin >> make_augmented(a, b); // enter 12 numbers
	std::cout << "a := coeff(input)\na -> matrix\n"
	          << make_formatter(a, std::ios::fixed | std::ios::right, 8, 3) << "end\n";
	std::cout << "b := right(input)\nb -> vector\n"
	          << make_formatter(b, std::ios::fixed | std::ios::right, 8, 3) << "end\n";
	
	std::list<std::pair<matrix_t, vector_t>> li;
	try
	{
		vector_t x = Gaussian_method(a, b, li);

		std::cout << "x := Gaussian_method(a, b)\nx -> vector\n"
		          << make_formatter(x, std::ios::fixed | std::ios::right, 8, 3) << "end\n";

		std::cout << "dist_e(a * x, b) -> " << Euclidean_distance(a.prod(x), b) << "\n";
	}
	catch (std::invalid_argument exc)
	{
		std::cout << "[EXCEPTION] " << exc.what() << "\n";
	}
	
	for (auto e : li)
	{
		std::cout << "\nmatrix\n" << make_formatter(e.first, std::ios::fixed | std::ios::right, 8, 3) << "end\n";
		std::cout << "vector\n" << make_formatter(e.second, std::ios::fixed | std::ios::right, 8, 3) << "end\n";
	}
	
	return 0;
}