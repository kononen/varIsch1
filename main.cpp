#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <iomanip>
#include "linsys.h"
#include "iolin.h"

using vector32 = linsys::vector<float>;
using matrix32 = linsys::matrix<float>;

using vector64 = linsys::vector<>;
using matrix64 = linsys::matrix<>;

int main(int argc, char **argv)
{
	std::cout << "Current directory:\n";
#ifdef _WIN32
	std::system("cd");
#else
	std::system("pwd");
#endif
	std::cout << "\n";
	
	std::string address;
	matrix64 A64;
	vector64 b64;
	std::size_t dim;
	std::ofstream save;
	
	bool incorrect_symbol;
	do
	{
		incorrect_symbol = false;
		char c;
		std::cout << "Enter <R|r> to generate a random linear system.\n";
		std::cout << "Enter <I|i> to read the matrix of coefficients and the vector from individual files.\n";
		std::cout << "Enter <A|a> to read the augmented matrix from a single file.\n";
		std::cin.get(c);
		std::cin.get();
		
		std::ifstream fin;
		switch (c)
		{
		case 'R':
		case 'r':
			std::cout << "Dimension := ";
			std::cin >> dim;
			
			std::cout << "Minimal value := ";
			double a;
			std::cin >> a;
			
			std::cout << "Maximal value := ";
			double b;
			std::cin >> b;
			
			{
				std::mt19937 gen(time(0));
				std::uniform_real_distribution<> dis(a, b);
				
				A64 = matrix64::random(dim, dis, gen);
				b64 = vector64::random(dim, dis, gen);
			}
			
			std::cout << "Enter <I|i> to save the matrix of coefficients and the vector in individual files.\n";
			std::cout << "Enter <A|a> to save the augmented matrix in a single file.\n";
			std::cin.get();
			std::cin.get(c);
			std::cin.get();
			
			bool incorrect_symbol_inner;
			do
			{
				incorrect_symbol_inner = false;
				switch (c)
				{
				case 'I':
				case 'i':
					std::cout << "Save the matrix of coefficients in a file: ";
					std::getline(std::cin, address);
					save.open(address);
					save << dim << "\n" << formatter(A64, std::ios::fixed | std::ios::right, 12, 6);
					save.close();
					
					std::cout << "Save the vector in a file: ";
					std::getline(std::cin, address);
					save.open(address);
					save << dim << "\n" << formatter(b64, std::ios::fixed | std::ios::right, 12, 6);
					save.close();
					break;
					
				case 'A':
				case 'a':
					std::cout << "Save the augmented matrix in a file: ";
					std::getline(std::cin, address);
					save.open(address);
					save << dim << "\n" << formatter(augmented(A64, b64), std::ios::fixed | std::ios::right, 12, 6);
					save.close();
					break;
					
				default:
					std::cout << "Incorrect symbol \'" << c << "\'. Please try again.\n";
					incorrect_symbol_inner = true;
					break;
				}
			}
			while (incorrect_symbol_inner);
			break;
			
		case 'I':
		case 'i':
			do
			{
				std::cout << "Read the matrix of coefficients from a file: ";
				std::getline(std::cin, address);
				fin.open(address);
				if (!fin.is_open())
					std::cout << "File \'" << address << "\' does not exist. Please try again.\n";
			}
			while (!fin.is_open());
			fin >> dim;
			A64 = matrix64(dim);
			fin >> A64;
			fin.close();
			
			do
			{
				std::cout << "Read the vector from a file: ";
				std::getline(std::cin, address);
				fin.open(address);
				if (!fin.is_open())
					std::cout << "File \'" << address << "\' does not exist. Please try again.\n";
			}
			while (!fin.is_open());
			fin >> dim;
			b64 = vector64(dim);
			fin >> b64;
			fin.close();
			break;
			
		case 'A':
		case 'a':
			do
			{
				std::cout << "Read the augmented matrix from a file: ";
				std::getline(std::cin, address);
				fin.open(address);
				if (!fin.is_open())
					std::cout << "File \'" << address << "\' does not exist. Please try again.\n";
			}
			while(!fin.is_open());
			fin >> dim;
			A64 = matrix64(dim); b64 = vector64(dim);
			fin >> augmented_mut(A64, b64);
			fin.close();
			break;
			
		default:
			std::cout << "Incorrect symbol \'" << c << "\'. Please try again.\n";
			incorrect_symbol = true;
		}
	}
	while (incorrect_symbol);
	
	auto A32 = (matrix32)A64;
	auto b32 = (vector32)b64;
	
	std::cout << "\nTrying to solve by Gaussian method with single precision...\n";
	try
	{
		auto t = clock();
		const auto x = Gaussian_method(A32, b32);
		auto seconds = (long double)(clock() - t) / CLOCKS_PER_SEC;
		
		std::cout << "Successfully solved.\n";
		auto f = std::cout.flags();
		auto p = std::cout.precision();
		std::cout << "Elapsed time: " << std::fixed << std::setprecision(6) << seconds << " sec.\n";
		std::cout.flags(f);
		std::cout.precision(p);
		std::cout << "Residual: "
		          << Euclidean_distance(((matrix64)A32).prod((vector64)x), (vector64)b32) << "\n\n";
		
		std::cout << "Save the solution in a file: ";
		std::getline(std::cin, address);
		save.open(address);
		save << x.dim << "\n" << formatter(x, std::ios::fixed | std::ios::right, 12, 6);
		save.close();
	}
	catch (std::invalid_argument exc)
	{
		std::cout << "[EXCEPTION] " << exc.what() << "\n";
	}
	
	std::cout << "\nTrying to solve by Gaussian method with double precision...\n";
	try
	{
		auto t = clock();
		const auto x = Gaussian_method(A64, b64);
		auto seconds = (long double)(clock() - t) / CLOCKS_PER_SEC;
		
		std::cout << "Successfully solved.\n";
		auto f = std::cout.flags();
		auto p = std::cout.precision();
		std::cout << "Elapsed time: " << std::fixed << std::setprecision(6) << seconds << " sec.\n";
		std::cout.flags(f);
		std::cout.precision(p);
		std::cout << "Residual: " << Euclidean_distance(A64.prod(x), b64) << "\n\n";
		
		std::cout << "Save the solution in a file: ";
		std::getline(std::cin, address);
		save.open(address);
		save << x.dim << "\n" << formatter(x, std::ios::fixed | std::ios::right, 12, 6);
		save.close();
	}
	catch (std::invalid_argument exc)
	{
		std::cout << "[EXCEPTION] " << exc.what() << "\n";
	}
	
	std::cout << "\nTrying to solve by QR-decomposition method with single precision...\n";
	try
	{
		auto t = clock();
		const auto qrx = QR_decomposition_method(A32, b32);
		auto seconds = (long double)(clock() - t) / CLOCKS_PER_SEC;
		
		std::cout << "Successfully solved.\n";
		auto f = std::cout.flags();
		auto p = std::cout.precision();
		std::cout << "Elapsed time: " << std::fixed << std::setprecision(6) << seconds << " sec.\n";
		std::cout.flags(f);
		std::cout.precision(p);
		std::cout << "Residual: "
		          << Euclidean_distance(((matrix64)A32).prod((vector64)qrx.X), (vector64)b32) << "\n\n";
		
		std::cout << "Q: matrix\n" << formatter(qrx.Q, std::ios::fixed | std::ios::right, 12, 6) << "end\n\n";
		std::cout << "R: matrix\n"
		          << formatter(qrx.R, std::ios::fixed | std::ios::right, 12, 6, UPPER_TRIANGULAR) << "end\n\n";
		
		std::cout << "Save matrix Q in a file: ";
		std::getline(std::cin, address);
		save.open(address);
		save << qrx.Q.dim << "\n" << formatter(qrx.Q, std::ios::fixed | std::ios::right, 12, 6);
		save.close();
		
		std::cout << "Save matrix R in a file: ";
		std::getline(std::cin, address);
		save.open(address);
		save << qrx.R.dim << "\n" << formatter(qrx.R, std::ios::fixed | std::ios::right, 12, 6, UPPER_TRIANGULAR);
		save.close();
		
		std::cout << "Save the solution in a file: ";
		std::getline(std::cin, address);
		save.open(address);
		save << qrx.X.dim << "\n" << formatter(qrx.X, std::ios::fixed | std::ios::right, 12, 6);
		save.close();
	}
	catch (std::invalid_argument exc)
	{
		std::cout << "[EXCEPTION] " << exc.what() << "\n";
	}
	
	std::cout << "\nTrying to solve by QR-decomposition method with double precision...\n";
	try
	{
		auto t = clock();
		const auto qrx = QR_decomposition_method(A64, b64);
		auto seconds = (long double)(clock() - t) / CLOCKS_PER_SEC;
		
		std::cout << "Successfully solved.\n";
		auto f = std::cout.flags();
		auto p = std::cout.precision();
		std::cout << "Elapsed time: " << std::fixed << std::setprecision(6) << seconds << " sec.\n";
		std::cout.flags(f);
		std::cout.precision(p);
		std::cout << "Residual: " << Euclidean_distance(A64.prod(qrx.X), b64) << "\n\n";
		
		std::cout << "Q: matrix\n" << formatter(qrx.Q, std::ios::fixed | std::ios::right, 12, 6) << "end\n\n";
		std::cout << "R: matrix\n"
		          << formatter(qrx.R, std::ios::fixed | std::ios::right, 12, 6, UPPER_TRIANGULAR) << "end\n\n";
		
		std::cout << "Save matrix Q in a file: ";
		std::getline(std::cin, address);
		save.open(address);
		save << qrx.Q.dim << "\n" << formatter(qrx.Q, std::ios::fixed | std::ios::right, 12, 6);
		save.close();
		
		std::cout << "Save matrix R in a file: ";
		std::getline(std::cin, address);
		save.open(address);
		save << qrx.R.dim << "\n" << formatter(qrx.R, std::ios::fixed | std::ios::right, 12, 6, UPPER_TRIANGULAR);
		save.close();
		
		std::cout << "Save the solution in a file: ";
		std::getline(std::cin, address);
		save.open(address);
		save << qrx.X.dim << "\n" << formatter(qrx.X, std::ios::fixed | std::ios::right, 12, 6);
		save.close();
	}
	catch (std::invalid_argument exc)
	{
		std::cout << "[EXCEPTION] " << exc.what() << "\n";
	}
	
	std::cin.get();
	return 0;
}