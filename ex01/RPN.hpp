#ifndef RPN_HPP
# define RPN_HPP

# include <iostream>
# include <string>
# include <stack>
# include <cmath>
# include <cstdlib>
# include <sstream>

class Rpn
{
	private:
		std::stack<int>	_stack;
		std::string		_input;

	public:
		// Constructors
		Rpn();
		Rpn( std::string input );
		Rpn( Rpn const & src );

		// Destructor
		~Rpn();

		// Operator overload
		Rpn & operator=( Rpn const & rhs );

		// Member functions
		void	run();

		// Exceptions
		class ConvertException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

#endif