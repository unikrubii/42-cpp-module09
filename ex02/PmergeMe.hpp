#ifndef PMERGE_ME_HPP
# define PMERGE_ME_HPP

# include <iostream>
# include <string>
# include <cstdlib>
# include <ctime>
# include <algorithm>
# include <iterator>
# include <vector>
# include <list>
# include <exception>
# include <iomanip>
# include <sys/time.h>

// global functions
unsigned long long getTime( void );

class PmergeMe
{
	public:
		// Constructors
		PmergeMe( void );
		PmergeMe( int *nums, int size );
		PmergeMe( PmergeMe const &src );

		// Destructor
		~PmergeMe( void );

		// Operator overload
		PmergeMe &operator=( PmergeMe const &rhs );

		// Member functions
		void	run( void );
		void	printNums( void ) const;
		void	deepCopyList( std::list<int> &src, std::list<int> &dst );
		bool 	checkSorted();

		// Vector sort functions
		void	merge( std::vector<int>& arr, int left, int mid, int right );
		void	insertionSort( std::vector<int> &list );
		void	mergeInsertionSort( std::vector<int>& arr, int left, int right );

		// List sort functions
		void	merge( std::list<int>& arr, int left, int mid, int right );
		void	insertionSort( std::list<int> &list );
		void	mergeInsertionSort( std::list<int>& arr, int left, int right );

		// Templates functions
		template <typename T>
		void printContainer( T &container );

		template <typename T>
		void convertToContainer( T &container );

		// Exceptions
		class NumsIsSorted : public std::exception {
			public:
				virtual const char *what() const throw();
		};

		class NumsIsEmpty : public std::exception {
			public:
				virtual const char *what() const throw();
		};

	private:
		// Attributes
		int	*_nums;
		int	_size;
		double _timeVec;
		double _timeList;
		std::vector<int> _vec;
		std::list<int> _list;
};

#endif