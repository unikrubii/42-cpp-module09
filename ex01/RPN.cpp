#include "RPN.hpp"

// Constructor
Rpn::Rpn( void ): _input( "" ) {
}

Rpn::Rpn( std::string input ): _input( input ) {
}

Rpn::Rpn( Rpn const & src ) {
	*this = src;
}

// Destructor
Rpn::~Rpn( void ) {
}

// Operator overload
Rpn & Rpn::operator=( Rpn const & rhs ) {
	if ( this != &rhs ) {
		this->_stack = rhs._stack;
	}
	return *this;
}

// Member functions
void Rpn::run( void ) {
	std::istringstream iss( this->_input );
	std::string token;
	while ( iss >> token ) {
		// check if token is digit
		if ( std::isdigit( token[0] ) ) {
			// convert token to int
			int num = std::atoi( token.c_str() );
			// push to stack
			this->_stack.push( num );
		}
		else if ( token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/' || token[0] == '%' || token[0] == '^' ) {
			// check if stack has at least two elements
			if ( this->_stack.size() < 2 ) {
				throw Rpn::ConvertException();
			}
			// pop two numbers from stack
			int num2 = this->_stack.top();
			this->_stack.pop();
			int num1 = this->_stack.top();
			this->_stack.pop();
			// perform operation
			switch( token[0] ) {
				case '+':
					this->_stack.push( num1 + num2 );
					break;
				case '-':
					this->_stack.push( num1 - num2 );
					break;
				case '*':
					this->_stack.push( num1 * num2 );
					break;
				case '/':
					this->_stack.push( num1 / num2 );
					break;
				case '%':
					this->_stack.push( num1 % num2 );
					break;
				case '^':
					this->_stack.push( std::pow( num1, num2 ) );
					break;
			}
		}
		else {
			throw Rpn::ConvertException();
		}
	}
	// check if stack has only one element
	if ( this->_stack.size() != 1 ) {
		throw Rpn::ConvertException();
	}
	else {
		std::cout << this->_stack.top() << std::endl;
	}
}

// Exceptions
const char* Rpn::ConvertException::what() const throw() {
	return "Error";
}
