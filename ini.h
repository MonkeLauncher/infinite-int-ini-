#ifndef INI_H
#define INI_H

#include <iostream>
#include <string>


class ini {
	public:
		// -----===== FUNctions ====-----
		
		
		// constructor(s)
		ini ();
		ini (const long long a);
		ini (const std::string a);
		ini (const ini &a);
		
		// return funcs
		std::string getString ();
		bool isNegative ();
		void setNegative (bool neg);
		void setConvertedString (std::string a);
		std::string getConvertedString ();
		long long size ();
		
		// editor funcs
		std::string correct (std::string a);
		std::string eraseFrontZeros (std::string a);
		
		
		// operators
		ini& operator= (const long long a);
		ini& operator= (const std::string a);
		ini& operator= (ini a);
		
		ini operator+ (long long a);
		ini operator+ (std::string a);
		ini operator+ (ini &b);
		
		ini operator- (long long a);
		ini operator- (std::string a);
		ini operator- (ini &b);
		
		ini operator* (long long a);
		ini operator* (std::string a);
		ini operator* (ini &b);
		
		ini operator/ (long long a);
		ini operator/ (std::string a);
		ini operator/ (ini &b);
		
		ini operator% (long long a);
		ini operator% (std::string a);
		ini operator% (ini &b);
		
		ini operator+= (long long a);
		ini operator+= (std::string a);
		ini operator+= (ini &b);
		
		ini operator-= (long long a);
		ini operator-= (std::string a);
		ini operator-= (ini &b);
		
		ini operator*= (long long a);
		ini operator*= (std::string a);
		ini operator*= (ini &b);
		
		ini operator/= (long long a);
		ini operator/= (std::string a);
		ini operator/= (ini &b);
		
		ini operator%= (long long a);
		ini operator%= (std::string a);
		ini operator%= (ini &b);
		
		bool operator== (const long long a);
		bool operator== (const std::string a);
		bool operator== (const ini &b);
		
		bool operator!= (const long long a);
		bool operator!= (const std::string a);
		bool operator!= (const ini &b);
		
		bool operator> (const long long a);
		bool operator> (const std::string a);
		bool operator> (const ini &b);
		
		bool operator>= (const long long a);
		bool operator>= (const std::string a);
		bool operator>= (const ini &b);
		
		bool operator< (const long long a);
		bool operator< (const std::string a);
		bool operator< (const ini &b);
		
		bool operator<= (const long long a);
		bool operator<= (const std::string a);
		bool operator<= (const ini &b);
		
		ini operator++ ();
		ini operator++ (int);
		
		ini operator-- ();
		ini operator-- (int);
		
		
		
		// printing
		friend std::ostream& operator<< (std::ostream& os, ini a);
		friend std::istream& operator>> (std::istream& is, ini &a);	
		
		
		
		// -----====== Varriables =====-----
		std::string data;
		bool negative;
		
	private:
		
		// calculating functions
		ini preAddition (ini a, ini b);
		ini preMultiplication (ini a, ini b);
		ini preDivision (ini a, ini b);
		ini preModulo (ini a, ini b);
		
		std::string addition (std::string a, std::string b);
		std::string substraction (std::string a, std::string b);
		std::string multiplication (std::string a, std::string b);
		std::string division (std::string a, std::string b, bool mod);
		
		bool isEqual (ini a, ini b);
		bool isBigger (ini a, ini b);
		bool isSmaller (ini a, ini b);
		
};


std::ostream& operator<< (std::ostream& os, ini a);
std::istream& operator>> (std::istream& is, ini &a);

#endif
