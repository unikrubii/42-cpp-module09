#include "PmergeMe.hpp"

int main( int ac, char **av ) {
	if (ac == 1) {
		std::cerr << "Usage: ./a.out [num1] [num2] ..." << std::endl;
		return 1;
	}
	// Create an array of ints
	int *nums = new int[ ac - 1 ];
	try {
		for (int i = 1; i < ac; i++) {
			if ( atoi( av[ i ] ) <= 0 && av[ i ][ 0 ] != '0' ) {
				throw std::invalid_argument("Error: Invalid argument");
			}
			nums[ i - 1 ] = atoi( av[ i ] );
		}
	}
	catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}

	{
		std::cout << "Run with given arguments" << std::endl;
		try {
			PmergeMe pmergeMe( nums, ac - 1 );
			pmergeMe.run();
		}
		catch ( std::exception &e ) {
			std::cerr << e.what() << std::endl;
		}
	}
	std::cout << "=============================" << std::endl;
	{
		std::cout << "Run with default constructor" << std::endl;
		try {
			PmergeMe pmergeMe2;
			pmergeMe2.run();
		}
		catch ( std::exception &e ) {
			std::cerr << e.what() << std::endl;
		}
	}

	delete [] nums;
	return 0;
}