#ifndef INTEGER_H
#define INTEGER_H

#include <iostream>

class Integer
{
	public:
		Integer();
		Integer(int);
		Integer(int, int);
		// operators for Integer (we treat it like IntegerRing::Element from first attempt at this)
		Integer operator+(const Integer&);
		Integer operator+(int);
		friend Integer operator+(int, const Integer&);
		Integer operator+=(const Integer&);
		Integer operator+=(int);
		Integer operator-();
		Integer operator-(const Integer&);
		Integer operator-(int);
		friend Integer operator-(int, const Integer&);
		Integer operator-=(const Integer&);
		Integer operator-=(int);
		Integer operator*(const Integer&);
		Integer operator*(int);
		friend Integer operator*(int, const Integer&);
		Integer operator*=(const Integer&);
		Integer operator*=(int);
		Integer operator%(int);
		// comparison operators
		bool operator==(const Integer&) const;
		bool operator!=(const Integer&) const;
		// value-getter
		int val() const;
		friend std::ostream& operator<<(std::ostream& o, const Integer& i)
		{
			return (o << i.m);
		}
	private:
		int m, n;
		
};

#endif