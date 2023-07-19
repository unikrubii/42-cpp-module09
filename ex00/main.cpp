#include "BitcoinExchange.hpp"

int main( int ac, char **argv ) {
	if ( ac != 2 ) {
		std::cout << "Usage: ./btc [filename]" << std::endl;
		return 1;
	}
	try {
		Btc btc( argv[ 1 ] );
		btc.printData();
	}
	catch ( std::exception & e ) {
		std::cout << e.what() << std::endl;
	}
	return 0;
}
