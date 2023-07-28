#include "PmergeMe.hpp"

// Global functions
unsigned long long getTime( void ) {
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000) + tv.tv_usec;
}

// Constructors
PmergeMe::PmergeMe( void ) : _nums(NULL), _size(0), _timeVec(0), _timeList(0), _vec(), _list() {
}

PmergeMe::PmergeMe( int *nums, int size ) : _nums(nums), _size(size), _timeVec(0), _timeList(0) {
	if ( this->checkSorted() )
		throw PmergeMe::NumsIsSorted();
	this->convertToContainer( this->_vec );
	this->convertToContainer( this->_list );
}

PmergeMe::PmergeMe( PmergeMe const &src ) {
	*this = src;
}

// Destructor
PmergeMe::~PmergeMe( void ) {
}

// Operator overload
PmergeMe &PmergeMe::operator=( PmergeMe const &rhs ) {
	if (this != &rhs ) {
		this->_nums = rhs._nums;
	}
	return *this;
}

// Member functions
void PmergeMe::run( void ) {
	if ( this->_size == 0 ) {
		throw PmergeMe::NumsIsEmpty();
	}

	std::cout << "Before: ";
	this->printNums();
	std::cout << "After: ";
	this->mergeInsertionSort( this->_vec, 0, this->_size - 1 );
	std::cout << "\tVector:\t";
	this->printContainer(this->_vec);
	this->mergeInsertionSort( this->_list, 0, this->_size - 1);
	std::cout << "\tList:\t";
	this->printContainer(this->_list);

	std::cout << "Time to process a range of 5 elements with std::vector : " << std::fixed << std::setprecision(5) << this->_timeVec << " us" << std::endl;
	std::cout << "Time to process a range of 5 elements with std::list : " << std::fixed << std::setprecision(5) << this->_timeList << " us" << std::endl;
}

bool PmergeMe::checkSorted( void ) {
	for ( int i = 0; i < this->_size - 1; i++ ) {
		if ( this->_nums[ i ] > this->_nums[ i + 1 ] ) {
			return false;
		}
	}
	return true;
}

void PmergeMe::printNums( void ) const {
	for (int i = 0; i < this->_size; i++) {
		std::cout << this->_nums[ i ] << " ";
	}
	std::cout << std::endl;
}

void PmergeMe::merge( std::vector<int>& arr, int left, int mid, int right ) {
	int leftArrSize = mid - left + 1;
	int rightArrSize = right - mid;

	std::vector<int> tmpLeft( leftArrSize );
	std::vector<int> tmpRight( rightArrSize );

	for ( int i = 0; i < leftArrSize; ++i )
		tmpLeft[ i ] = arr[ left + i ];
	for ( int i = 0; i < rightArrSize; ++i )
		tmpRight[ i ] = arr[ mid + 1 + i ];

	int i = 0, j = 0, k = left;

	while ( i < leftArrSize && j < rightArrSize ) {
		if ( tmpLeft[ i ] <= tmpRight[ j ] ) {
			arr[ k ] = tmpLeft[ i ];
			i++;
		} else {
			arr[ k ] = tmpRight[ j ];
			j++;
		}
		k++;
	}

	while ( i < leftArrSize ) {
		arr[ k++ ] = tmpLeft[ i++ ];
	}

	while ( j < rightArrSize ) {
		arr[ k++ ] = tmpRight[ j++ ];
	}
}

void PmergeMe::insertionSort( std::vector<int> &arr ) {
	int size = arr.size();
	for ( int i = 1; i < size; ++i ) {
		int key = arr[ i ];
		int j = i - 1;

		while ( j >= 0 && arr[ j ] > key ) {
			arr[ j + 1 ] = arr[ j ];
			j--;
		}
		arr[ j + 1 ] = key;
	}
}

void PmergeMe::mergeInsertionSort( std::vector<int> &arr, int left, int right ) {
	unsigned long long start = getTime();
	int size = right - left;
	if ( size < 10 ) {
		this->insertionSort( arr );
	} else {
		int mid = left + (right - left) / 2;

		this->mergeInsertionSort( arr, left, mid );
		this->mergeInsertionSort( arr, mid + 1, right );
		this->merge( arr, left, mid, right );
	}
	unsigned long long end = getTime();
	this->_timeVec += static_cast<double>((end - start) / 100000.0);
}

void PmergeMe::deepCopyList( std::list<int> &src, std::list<int> &dst ) {
	std::list<int>::iterator it = src.begin();
	std::list<int>::iterator ite = src.end();
	while (it != ite) {
		dst.push_back( *it );
		it++;
	}
}

void PmergeMe::merge( std::list<int> &lst, int left, int mid, int right ) {
	int leftArrSize = mid - left + 1;
	int rightArrSize = right - mid;
	std::list<int> tmpLeft;
	std::list<int> tmpRight;
	for ( int i = 0; i < leftArrSize; ++i ) {
		tmpLeft.push_back( lst.front() );
		lst.pop_front();
	}
	for ( int i = 0; i < rightArrSize; ++i ) {
		tmpRight.push_back( lst.front() );
		lst.pop_front();
	}

	int i = 0, j = 0;
	while ( i < leftArrSize && j < rightArrSize ) {
		if ( tmpLeft.front() <= tmpRight.front() ) {
			lst.push_back( tmpLeft.front() );
			tmpLeft.pop_front();
			i++;
		} else {
			lst.push_back( tmpRight.front() );
			tmpRight.pop_front();
			j++;
		}
	}
	while ( i < leftArrSize ) {
		lst.push_back( tmpLeft.front() );
		tmpLeft.pop_front();
		i++;
	}
	while ( j < rightArrSize ) {
		lst.push_back( tmpRight.front() );
		tmpRight.pop_front();
		j++;
	}
}

void PmergeMe::insertionSort( std::list<int> &lst ) {
	std::list<int>::iterator current = ++lst.begin();
	while ( current != lst.end() ) {
		int key = *current;
		std::list<int>::iterator prev = current;
		prev--;
		while ( prev != lst.begin() && *prev > key ) {
			prev--;
		}
		if ( prev == lst.begin() && *prev > key ) {
			if ( *prev > key ) {
				lst.insert( prev, key );
				lst.erase( current++ );
				continue;
			}
		}
		lst.insert( ++prev, key );
		lst.erase( current++ );
	}
}

void PmergeMe::mergeInsertionSort( std::list<int> &lst, int left, int right ) {
	unsigned long long start = getTime();
	int size = right - left;
	if ( size < 10 ) {
		this->insertionSort( lst );
	} else {
		int mid = left + (right - left) / 2;

		this->mergeInsertionSort( lst, left, mid );
		this->mergeInsertionSort( lst, mid + 1, right );
		this->merge( lst, left, mid, right );
	}
	unsigned long long end = getTime();
	this->_timeList += static_cast<double>((end - start) / 100000.0);
}

// Templates functions
template <typename T>
void PmergeMe::printContainer( T &container ) {
	typename T::iterator it = container.begin();
	typename T::iterator ite = container.end();
	while (it != ite) {
		std::cout << *it << " ";
		it++;
	}
	std::cout << std::endl;
}

template <typename T>
void PmergeMe::convertToContainer( T &container ) {
	for (int i = 0; i < this->_size; i++) {
		container.push_back( this->_nums[ i ] );
	}
}

// Exceptions
const char *PmergeMe::NumsIsSorted::what() const throw() {
	return "Error: The given array is already sorted.";
}

const char *PmergeMe::NumsIsEmpty::what() const throw() {
	return "Error: The given array is empty.";
}
