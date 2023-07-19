#ifndef BITCOINECHANGE_HPP
# define BITCOINECHANGE_HPP

# include <iostream>
# include <fstream>
# include <sstream>
# include <string>
# include <vector>
# include <cstdlib>
# include <iomanip>
# include <map>
# include <algorithm>
# include <iterator>
# include <exception>
# include <utility>

class Btc
{
	private:
		std::map< int, std::pair<std::string, float> > _data;
		std::map< int, std::pair<std::string, float> > _exchangeRate;
		std::string _fileName;

	public:
		// Constructor
		Btc();
		Btc( std::string fileName );
		Btc( Btc const & src );

		// Destructor
		~Btc();

		// Operator overload
		Btc & operator=( Btc const & rhs );

		// Getters
		int getExchangeRate( std::string date );
		std::string getExtension( std::string filename );

		// Member functions
		void readFile( std::string filename, std::map< int, std::pair<std::string, float> > & map );
		void printData();
		bool checkDate( std::string date );
		bool checkLeapYear( std::string date );
		bool checkIn( int month, std::vector<int> monthList );
		std::vector<int> getMonthList();
};

#endif