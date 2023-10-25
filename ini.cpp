#include "ini.h"

#include <iostream>



// ------====== constructors and other ======------


ini::ini (const long long a) {
	negative = false;
	if (a < 0) 
		negative = true;
	
	data = std::to_string(a);
	if (negative) data.erase(0, 1); 
	for (long long i = 0; i < data.size(); i++) {
		data[i] -= '0';
	}
	
	char x = 0;
	std::string g;
	g = x;
	if (data == g) negative = false;
	data = correct (data);
}

ini::ini (const std::string a) {
	data = a;
	
	negative = false;
	if (a[0] == '-') {
		negative = true;
		data.erase(0, 1);
	}
		
	
	for (long long i = 0; i < data.size(); i++) {
		data[i] -= '0';
	}
	
	char x = 0;
	std::string g;
	g = x;
	if (data == g) negative = false;
	data = correct (data);
	data = eraseFrontZeros (data);
}

ini::ini (const ini &a) {
	negative = a.negative;	
	data = a.data;
}

ini::ini () {
	char a = 0;
	data = a;
	negative = false;
}


void ini::setConvertedString (std::string a) {
	this -> data = a;
	
	char x = 0;
	std::string g;
	g = x;
	if (data == g) negative = false;
	data = correct (data);
}

std::string ini::getString () {
	std::string a;
	
	a = this -> data;
	for (long long i = 0; i < a.size(); i++) {
		a[i] += '0';
	}
	
	return a;
}

std::string ini::getConvertedString () {
	return this-> data;
}

bool ini::isNegative () {
	return negative;
}

void ini::setNegative (bool neg) {
	negative = neg;
	
	char x = 0;
	std::string g;
	g = x;
	if (data == g) negative = false;
	data = correct (data);
}


std::string ini::correct (std::string a) {
	for (long long i = a.size() - 1; i >= 1; i--) {
		a[i - 1] += ((int)a[i] / 10);
		a[i] %= 10;
	}
	
	while ((int)a[0] > 9) {
		char b = (int)a[0] / 10;
		std::string c;
		c += b;
		
		a[0] %= 10;
		
		a.insert (0, c);
	}
	
	return a;
}

std::string ini::eraseFrontZeros (std::string a) {
	
	char x = 0;
	std::string b;
	b = x;
	if (a == b) return a;
	
	while ((int)a[0] == 0 && a.size() > 1) 
		a.erase(0, 1);
		
	return a; 
}

long long ini::size () {
	return data.size();
}



// ------====== in/out-stream functions ======------


std::ostream& operator<< (std::ostream& os, ini a) {
	if (a.isNegative()) os << "-";
	os << a.getString ();
    return os;
}

std::istream& operator>> (std::istream& is, ini &a) {
	std::string b;
	is >> b;
	a = b;
	return is;
}



// ------====== calculating functions ======------


std::string ini::addition (std::string a, std::string b) {
	if (b.size() > a.size()) std::swap (a, b);
	
	for (long long i = 1; i < b.size() + 1; i++)
		a[a.size() - i] += (int)b[b.size() - i];
	
	a = correct(a);
	
	return a;
}

std::string ini::substraction (std::string a, std::string b) {
	
	if (a == b) {
		char x = 0;
		a = x;
		return a;
	}
	
	for (long long i = 0; i < a.size() - 1; i++) {
		if ((int)a[i + 1] == 0 && b[b.size() - (a.size() - i - 1)] != 0) {
			a[i] -= 1;
			a[i + 1] += 10;
		}
	}
	
	for (long long i = 1; i < b.size() + 1; i++) {
		if (a[a.size() - i] < b[b.size() - i]) {
			a[a.size() - i - 1] -= 1;
			a[a.size() - i] += 10;
		}
		
		a[a.size() - i] -= (int)b[b.size() - i];
	}
	
	a = correct (a);
	a = eraseFrontZeros (a);
	
	return a;
}

std::string ini::multiplication (std::string a, std::string b) {
	if (a.size() < b.size()) std::swap (a, b);
	
	std::string returned;
	char x = 0;
	returned = x;
	
	for (long long i = 0; i < a.size() + b.size() - 2; i++) {
		returned += x;
	}
	
	for (long long i = 0; i < b.size(); i++) {
		for (long long j = 0; j < a.size(); j++) {
			returned[returned.size() - 1 - j - i] += ((int)a[a.size() - 1 - j] * (int)b[b.size() - 1 - i]);
		}
		
		returned = correct (returned);
	}
	
	return returned;
}

std::string ini::division (std::string a, std::string b, bool mod) {
	std::string divided = "", modulo = "";
	
	int ile;
	char ileC;
	
	if (b.size() > a.size() || (a.size() == b.size() && b > a)) {
		
		modulo = a;
		char x = 0;
		divided = x;
		
		if (mod)
		return modulo;
	
		divided = eraseFrontZeros (divided);
		return divided;
	}
	
	for (long long i = 0; i < a.size(); i++) {
		modulo += a[i];
		ile = 0;
		
		while (modulo.size() > b.size() || (modulo.size() == b.size() && modulo > b) || modulo == b) {
			ile++;
			
			b = eraseFrontZeros (b);
			modulo = substraction (modulo, b);
			
		}
		
		ileC = ile;
		divided += ileC;
	}
	
	if (mod)
		return modulo;
	
	divided = eraseFrontZeros (divided);
	return divided;
}

bool ini::isEqual (ini a, ini b) {
	return (a.getConvertedString() == b.getConvertedString() && a.isNegative() == b.isNegative());
}

bool ini::isBigger (ini a, ini b) {
	if (a.isNegative() != b.isNegative()) 
		return (a.isNegative() < b.isNegative());
	
	else {
		if (!negative)
			return (a.getConvertedString().size() > b.getConvertedString().size() || (a.getConvertedString().size() == b.getConvertedString().size() && a.getConvertedString() > b.getConvertedString()));
		else 
			return (a.getConvertedString().size() < b.getConvertedString().size() || (a.getConvertedString().size() == b.getConvertedString().size() && a.getConvertedString() < b.getConvertedString()));
	}
		
}

bool ini::isSmaller (ini a, ini b) {
	if (a.isNegative() != b.isNegative()) 
		return (a.isNegative() > b.isNegative());
	
	else {
		if (!negative)
			return (a.getConvertedString().size() < b.getConvertedString().size() || (a.getConvertedString().size() == b.getConvertedString().size() && a.getConvertedString() < b.getConvertedString()));
		else
			return (a.getConvertedString().size() > b.getConvertedString().size() || (a.getConvertedString().size() == b.getConvertedString().size() && a.getConvertedString() > b.getConvertedString()));
	}
		
}



// ------====== pre functions ======------


ini ini::preAddition (ini a, ini b) {
	if (a.isNegative() == b.isNegative()) {
		a.setConvertedString (addition (a.getConvertedString(), b.getConvertedString()));
	}
	
	else {
		if (a.getConvertedString().size() < b.getConvertedString().size() || (a.getConvertedString().size() == b.getConvertedString().size() && a.getConvertedString() < b.getConvertedString())) {
			std::swap (a, b);
		}
		
		a.setConvertedString (substraction (a.getConvertedString(), b.getConvertedString()));
	}
	
	if (a.getString() == "0") negative = false;
	
	return a;
}

ini ini::preMultiplication (ini a, ini b) {
	a.setNegative((a.isNegative() != b.isNegative()));
	
	a.setConvertedString (multiplication (a.getConvertedString(), b.getConvertedString()));
	
	if (a.getString() == "0") negative = false;
	return a;
}

ini ini::preDivision (ini a, ini b) {
	a.setNegative ((a.isNegative() != b.isNegative()));
	
	a.setConvertedString (division (a.getConvertedString(), b.getConvertedString(), false));
	
	if (a.getString() == "0") negative = false;
	return a;
}

ini ini::preModulo (ini a, ini b) {	
	a.setConvertedString (division (a.getConvertedString(), b.getConvertedString(), true));
	
	if (a.getString() == "0") negative = false;
	return a;
}



// ------====== operators ======------


ini& ini::operator= (const long long a) {
	this -> negative = false;
	if (a < 0) 
		this -> negative = true;
	
	this -> data = std::to_string(a);
	if (negative) data.erase (0, 1);
	for (long long i = 0; i < data.size(); i++) {
		this -> data[i] -= '0';
	}
	
	return *this;
}

ini& ini::operator= (const std::string a) {
	this -> data = a;
	
	this -> negative = false;
	if (a[0] == '-') {
		this -> negative = true;
		this -> data.erase(0, 1);
	}
		
	for (long long i = 0; i < data.size(); i++) {
		this -> data[i] -= '0';
	}
	
	char x = 0;
	std::string g;
	g = x;
	if (data == g) negative = false;
	data = eraseFrontZeros (data);
	
	return *this;
}

ini& ini::operator= (ini a) {
	if (this != &a) {
		this -> data = a.getConvertedString();
		this -> negative = a.isNegative();
		
		return *this;
	}
}



ini ini::operator+ (long long a) {
	ini b (a);
	
	return preAddition (*this, b);
}

ini ini::operator+ (std::string a) {
	ini b (a);
	
	return preAddition (*this, b);
}

ini ini::operator+ (ini &b) {
	
	return preAddition (*this, b);
}



ini ini::operator- (long long a) {
	ini b (a);
	b.setNegative(!(b.isNegative()));
	
	return preAddition (*this, b);
}

ini ini::operator- (std::string a) {
	ini b (a);
	b.setNegative(!(b.isNegative()));
	
	return preAddition (*this, b);
}

ini ini::operator- (ini &b) {
	b.setNegative(!(b.isNegative()));
	
	return preAddition (*this, b);
}



ini ini::operator* (long long a) {
	ini b (a);
	
	return preMultiplication (*this, b);
}

ini ini::operator* (std::string a) {
	ini b(a);
	
	return preMultiplication (*this, b);
}

ini ini::operator* (ini &b) {
	
	return preMultiplication (*this, b);
}



ini ini::operator/ (long long a) {
	ini b (a);
	
	return preDivision (*this, b);
}

ini ini::operator/ (std::string a) {
	ini b(a);
	
	return preDivision (*this, b);
}

ini ini::operator/ (ini &b) {
	
	return preDivision (*this, b);
}



ini ini::operator% (long long a) {
	ini b (a);
	
	return preModulo (*this, b);
}

ini ini::operator% (std::string a) {
	ini b(a);
	
	return preModulo (*this, b);
}

ini ini::operator% (ini &b) {
	
	return preModulo (*this, b);
}



ini ini::operator+= (long long a) {
	ini b (a);
	
	*this = preAddition (*this, b);
	return *this;
}

ini ini::operator+= (std::string a) {
	ini b (a);
	
	*this = preAddition (*this, b);
	return *this;
}

ini ini::operator+= (ini &b) {
	
	*this = preAddition (*this, b);
	return *this;
}



ini ini::operator-= (long long a) {
	ini b (a);
	b.setNegative(!(b.isNegative()));
	
	*this = preAddition (*this, b);
	return *this;
}

ini ini::operator-= (std::string a) {
	ini b (a);
	b.setNegative(!(b.isNegative()));
	
	*this = preAddition (*this, b);
	return *this;
}

ini ini::operator-= (ini &b) {
	b.setNegative(!(b.isNegative()));
	
	*this = preAddition (*this, b);
	return *this;
}



ini ini::operator*= (long long a) {
	ini b (a);
	
	*this = preMultiplication (*this, b);
	return *this;
}

ini ini::operator*= (std::string a) {
	ini b(a);
	
	*this = preMultiplication (*this, b);
	return *this;
}

ini ini::operator*= (ini &b) {
	
	*this = preMultiplication (*this, b);
	return *this;
}



ini ini::operator/= (long long a) {
	ini b (a);
	
	*this = preDivision (*this, b);
	return *this;
}

ini ini::operator/= (std::string a) {
	ini b(a);
	
	*this = preDivision (*this, b);
	return *this;
}

ini ini::operator/= (ini &b) {
	
	*this = preDivision (*this, b);
	return *this;
}



ini ini::operator%= (long long a) {
	ini b (a);
	
	*this = preModulo (*this, b);
	return *this;
}

ini ini::operator%= (std::string a) {
	ini b(a);
	
	*this = preModulo (*this, b);
	return *this;
}

ini ini::operator%= (ini &b) {
	
	*this = preModulo (*this, b);
	return *this;
}



bool ini::operator== (const long long a) {
	ini b (a);
	return isEqual (*this, b);
}

bool ini::operator== (const std::string a) {
	ini b (a);
	return isEqual (*this, b);
}

bool ini::operator== (const ini &b) {
	return isEqual (*this, b);
}



bool ini::operator!= (const long long a) {
	ini b (a);
	return !(isEqual (*this, b));
}

bool ini::operator!= (const std::string a) {
	ini b (a);
	return !(isEqual (*this, b));
}

bool ini::operator!= (const ini &b) {
	return !(isEqual (*this, b));
}



bool ini::operator> (const long long a) {
	ini b (a);
	return isBigger (*this, b);
}

bool ini::operator> (const std::string a) {
	ini b (a);
	return isBigger (*this, b);
}

bool ini::operator> (const ini &b) {
	return isBigger (*this, b);
}



bool ini::operator>= (const long long a) {
	ini b (a);
	return (isBigger (*this, b) || isEqual (*this, b));
}

bool ini::operator>= (const std::string a) {
	ini b (a);
	return (isBigger (*this, b) || isEqual (*this, b));
}

bool ini::operator>= (const ini &b) {
	return (isBigger (*this, b) || isEqual (*this, b));
}



bool ini::operator< (const long long a) {
	ini b (a);
	return isSmaller (*this, b);
}

bool ini::operator< (const std::string a) {
	ini b (a);
	return isSmaller (*this, b);
}

bool ini::operator< (const ini &b) {
	return isSmaller (*this, b);
}



bool ini::operator<= (const long long a) {
	ini b (a);
	return (isSmaller (*this, b) || isEqual (*this, b));
}

bool ini::operator<= (const std::string a) {
	ini b (a);
	return (isSmaller (*this, b) || isEqual (*this, b));
}

bool ini::operator<= (const ini &b) {
	return (isSmaller (*this, b) || isEqual (*this, b));
}



ini ini::operator++ () {
	if (negative) {
		for (long long i = 0; i < data.size() - 1; i++) {
			if (data[i + 1] == 0) {
				data[i]--;
				data[i + 1] += 10;
			}
		}
		
		data[data.size() - 1]--;		
	}
	
	else
		data[data.size() - 1]++;
	
	char x = 0;
	std::string g;
	g = x;
	if (data == g) negative = false;
	data = correct (data);
	data = eraseFrontZeros (data);
	
	return *this;
}

ini ini::operator++ (int) {
	ini a = *this;
	
	if (negative) {
		for (long long i = 0; i < data.size() - 1; i++) {
			if (data[i + 1] == 0) {
				data[i]--;
				data[i + 1] += 10;
			}
		}
		
		data[data.size() - 1]--;		
	}
	
	else
		data[data.size() - 1]++;
	
	char x = 0;
	std::string g;
	g = x;
	if (data == g) negative = false;
	data = correct (data);
	data = eraseFrontZeros (data);
	
	return a;
}



ini ini::operator-- () {
	if (!negative) {
		
		if (getString() == "0") {
			data[0]++;
			negative = true;
		}
		
		else {
			for (long long i = 0; i < data.size() - 1; i++) {
				if (data[i + 1] == 0) {
					data[i]--;
					data[i + 1] += 10;
				}
			}
			
			data[data.size() - 1]--;
		}
				
	}
	
	else
		data[data.size() - 1]++;
		
	data = correct (data);
	data = eraseFrontZeros (data);
	
	return *this;
}

ini ini::operator-- (int) {
	ini a = *this;
	
	if (!negative) {
		
		if (getString() == "0") {
			data[0]++;
			negative = true;
		}
		
		else {
			for (long long i = 0; i < data.size() - 1; i++) {
				if (data[i + 1] == 0) {
					data[i]--;
					data[i + 1] += 10;
				}
			}
			
			data[data.size() - 1]--;
		}
				
	}
	
	else
		data[data.size() - 1]++;
		
	data = correct (data);
	data = eraseFrontZeros (data);
	
	return a;
}








