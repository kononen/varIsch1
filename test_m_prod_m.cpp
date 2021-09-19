// inactivated as unnecessary; uncomment linsys.h:229 to activate
#include <iostream>
#include "linsys.h"
#include "iolin.h"

using matrix_t = linsys::matrix<>;

int main(int argc, char **argv)
{
	std::size_t d;
	std::cin >> d;
	matrix_t A(d), B(d);
	
	std::cin >> A >> B;
	
	std::cout << "A := input\nA -> matrix\n"
	          << formatter(A, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	std::cout << "B := input\nB -> matrix\n"
	          << formatter(B, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	std::cout << "A * B -> matrix\n"
	          << formatter(A * B, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	return 0;
}