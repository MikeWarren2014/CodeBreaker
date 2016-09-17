#include "Integer.h"

Integer::Integer()
	: m(0), n(0)
{
	
}

Integer::Integer(int x)
	: m(x), n(0)
{
	
}

Integer::Integer(int x, int y)
	: m(x), n(y)
{
	
}

Integer Integer::operator+(const Integer& rhs)
{
	if ((this->n == rhs.n) && (this->n <= 1)) return ((*this) + rhs.m);
	return Integer(-1); // error object
}

Integer Integer::operator+(int x)
{
	// compute (this->m + x) % this->n
	int sum = (this->m + x) % this->n;
	// if less than 0
	if (sum < 0)
		// add this->n to it
		sum += this->n;
	return Integer(sum);
}

Integer operator+(int x, const Integer& i)
{
	return (x + i);
}

Integer Integer::operator+=(const Integer& rhs)
{
	return ((*this) = (*this) + rhs);
}

Integer Integer::operator+=(int x)
{
	return ((*this) = (*this) + x);
}

Integer Integer::operator-(const Integer& rhs)
{
	if ((this->n == rhs.n) && (this->n <= 1)) return ((*this) - rhs.m);
	return Integer(-1); // error object
}

Integer Integer::operator-(int x)
{
	// compute (this->m - x) % this->n
	int difference = (this->m - x) % this->n;
	// if less than 0
	if (difference < 0)
		// add this->n to it
		difference -= this->n;
	return Integer(difference);
}

Integer Integer::operator-() { return Integer(-this->m); }

Integer operator-(int x, const Integer& i)
{
	return (-x + i);
}

Integer Integer::operator-=(const Integer& rhs)
{
	return ((*this) = (*this) - rhs);
}

Integer Integer::operator-=(int x)
{
	return ((*this) = (*this) - x);
}

Integer Integer::operator*(const Integer& rhs)
{
	if ((this->n == rhs.n) && (this->n <= 1)) return ((*this) * rhs.m);
	return Integer(-1); // error object
}

Integer Integer::operator*(int x)
{
	// compute (this->m * x) % this->n
	int product = (this->m * x) % this->n;
	// if less than 0
	if (product < 0)
		// add this->n to it
		product *= this->n;
	return Integer(product);
}

Integer operator*(int x, const Integer& i)
{
	return (x * i);
}

Integer Integer::operator*=(const Integer& rhs)
{
	return ((*this) = (*this) * rhs);
}

Integer Integer::operator*=(int x)
{
	return ((*this) = (*this) * x);
}

Integer Integer::operator%(int x)
{
	return Integer(this->m % x);
}

bool Integer::operator==(const Integer& rhs) const
{
	return ((this->m == rhs.m) && (this->n == rhs.n));
}

bool Integer::operator!=(const Integer& rhs) const
{
	return !((*this) == rhs);
}

int Integer::val() const { return this->m; }