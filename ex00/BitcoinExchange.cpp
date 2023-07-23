#include "BitcoinExchange.hpp"

// Constructor
Btc::Btc(): _fileName( "" ) {
}

Btc::Btc( std::string fileName ): _fileName( fileName ) {
	this->readFile( fileName, this->_data );
	this->readFile( "data.csv", this->_exchangeRate );
}

Btc::Btc( Btc const & src ) {
	*this = src;
}

// Destructor
Btc::~Btc() {
}

// Operator overload
Btc & Btc::operator=( Btc const & rhs ) {
	if ( this != &rhs ) {
		this->_data = rhs._data;
	}
	return *this;
}

// Getters
std::string Btc::getExtension( std::string filename ) {
	std::string extension = "";
	std::size_t found = filename.find_last_of( "." );
	if ( found != std::string::npos ) {
		extension = filename.substr( found + 1 );
	}
	return extension;
}

float Btc::getExchangeRate( std::string date ) {
	std::map< int, std::pair<std::string, float> >::iterator it = this->_exchangeRate.begin();
	while ( it != this->_exchangeRate.end() ) {
		std::string dateStr = it->second.first;
		if ( dateStr == date ) {
			return it->second.second;
		}
		else {
			int yearInput = std::atoi( date.substr( 0, 4 ).c_str() );
			int monthInput = std::atoi( date.substr( 5, 2 ).c_str() );
			int dayInput = std::atoi( date.substr( 8, 2 ).c_str() );
			int yearStr = std::atoi( dateStr.substr( 0, 4 ).c_str() );
			int monthStr = std::atoi( dateStr.substr( 5, 2 ).c_str() );
			int dayStr = std::atoi( dateStr.substr( 8, 2 ).c_str() );
			if ( yearInput < yearStr ) {
				it--;
				return it->second.second;
			}
			else if ( yearInput == yearStr ) {
				if ( monthInput < monthStr ) {
					it--;
					return it->second.second;
				}
				else if ( monthInput == monthStr ) {
					if ( dayInput < dayStr ) {
						it--;
						return it->second.second;
					}
				}
			}
		}
		it++;
	}
	return 0;
}

// Member functions
void Btc::readFile( std::string filename, std::map< int, std::pair<std::string, float> > & map ) {
	std::cout << "Reading file: " << filename << std::endl;
	std::ifstream file(filename);
	if ( !file.is_open() ) {
		throw std::runtime_error("File not found");
	}

	std::string ext = this->getExtension( filename );
	char delim;
	if ( ext == "csv") {
		delim = ',';
	}
	else if ( ext == "txt" ) {
		delim = '|';
	}
	else {
		throw std::runtime_error( "Invalid file extension" );
	}

	std::string line;
	int index = 0;
	// skip first line
	std::getline(file, line );
	while ( std::getline(file, line ) ) {
		std::istringstream iss( line );
		std::string dateStr;
		std::string priceStr;
		std::getline( iss, dateStr, delim);
		std::getline( iss, priceStr, delim);
		dateStr.erase( dateStr.find_last_not_of( " " ) + 1 );
		float price = std::atof( priceStr.c_str() );
		map[ index++ ] = std::make_pair( dateStr, price );
	}
}

bool Btc::checkDate( std::string date ) {
	int year = std::atoi( date.substr( 0, 4 ).c_str() );
	int month = std::atoi( date.substr( 5, 2 ).c_str() );
	int day = std::atoi( date.substr( 8, 2 ).c_str() );
	if ( year < 0 || ( month < 1 || month > 12 ) || ( day < 1 || day > 31 ) ) {
		return false;
	}
	std::vector<int> monthList = this->getMonthList();
	if ( this->checkIn( month, monthList) && day <= 31 ) {
		return true;
	}
	else if ( month == 2 && day == 29 ) {
		if ( this->checkLeapYear( date ) ) {
			return true;
		}
		return false;
	}
	else if ( month == 2 && day <= 28 ) {
		return true;
	}
	else if ( day <= 30 ) {
		return true;
	}
	return false;
}

bool Btc::checkIn( int month, std::vector<int> monthList ) {
	if ( std::find( monthList.begin(), monthList.end(), month ) != monthList.end() ) {
		return true;
	}
	return false;
}

bool Btc::checkLeapYear( std::string date ) {
	int year = std::atoi( date.substr( 0, 4 ).c_str() );
	if ( year % 4 == 0 ) {
		if ( year % 100 == 0 ) {
			if ( year % 400 == 0 ) {
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

std::vector<int> Btc::getMonthList() {
	std::vector<int> monthList;
	monthList.push_back( 1 );
	monthList.push_back( 3 );
	monthList.push_back( 5 );
	monthList.push_back( 7 );
	monthList.push_back( 8 );
	monthList.push_back( 10 );
	monthList.push_back( 12 );
	return monthList;
}

void Btc::printData( void ) {
	// print every thing in _data
	std::cout << "Date | Price" << std::endl;
	for ( std::map< int, std::pair<std::string, float> >::iterator it = this->_data.begin(); it != this->_data.end(); it++ ) {
		std::string date = it->second.first;
		float price = it->second.second;
		if ( !this->checkDate( date ) ) {
			std::cout << "Error: bad input => " << date << std::endl;
			continue;
		}
		else if ( price <= 0.0f ) {
			std::cout << "Error: not a positive number." << std::endl;
			continue; ;
		}
		else if ( price >= 10000 ) {
			std::cout << "Error: too large number." << std::endl;
			continue;
		}
		float rate = this->getExchangeRate( date );
		std::cout << date << " => " << price << " = " << price * rate << std::endl;
	}
}
