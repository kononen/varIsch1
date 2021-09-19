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
	
	std::cin >> augmented(a, b); // enter d * (d + 1) numbers
	
	std::cout << "a := coeff(input)\na -> matrix\n"
	          << formatter(a, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	std::cout << "b := right(input)\nb -> vector\n"
	          << formatter(b, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
	
	try
	{
		const auto qrx = QR_decomposition_method(a, b);
		
		std::cout << "(q, r, x) := QR_decomposition_method(a, b)\nq -> matrix\n"
		          << formatter(qrx.Q, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
		
		std::cout << "r -> matrix\n"
		          << formatter(qrx.R, std::ios::fixed | std::ios::right, 12, 6, UPPER_TRIANGULAR) << "end\n";
		
		std::cout << "x -> vector\n"
		          << formatter(qrx.X, std::ios::fixed | std::ios::right, 12, 6) << "end\n";
		
		/*std::cout << "q * q^T -> matrix\n" << formatter(
			qr.first * qr.first.transpose(),
			std::ios::scientific | std::ios::right,
			15,
			6
		) << "end\n";//*/
		
		std::cout << "dist_e(a * x, b) -> " << Euclidean_distance(a.prod(qrx.X), b) << "\n";
	}
	catch (std::invalid_argument exc)
	{
		std::cout << "[EXCEPTION] " << exc.what() << "\n";
	}
	
	return 0;
}