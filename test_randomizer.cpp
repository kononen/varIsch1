#include <iostream>
#include "linsys.h"
#include "iolin.h"
#include <random>

using vector_t = linsys::vector<>;
using matrix_t = linsys::matrix<>;

int main(int argc, char **argv)
{
	std::mt19937 gen(0);
	std::uniform_real_distribution<> dis(1.5, 1.6);
	
	std::size_t d;
	std::cin >> d;
	auto A = matrix_t::random(d, dis, gen);
	auto B = vector_t::random(d, dis, gen);
	
	std::cout << "A := random\nA -> matrix\n"
	          << formatter(A, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	std::cout << "B := random\nB -> vector\n"
	          << formatter(B, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	return 0;
}