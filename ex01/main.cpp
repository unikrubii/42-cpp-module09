#include "RPN.hpp"

int main( int av, char **ac ) {
	if ( av != 2 ) {
		std::cout << "Usage: ./rpn \"<expression>\"" << std::endl;
		return 1;
	}
	Rpn rpn( ac[1] );
	try {
		rpn.run();
	}
	catch ( std::exception &e ) {
		std::cout << e.what() << std::endl;
		return 1;
	}
	return 0;
}