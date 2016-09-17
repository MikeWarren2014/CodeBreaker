#include "Integers.h"

// this group is simplest simulation of the integers modulo n
// therefore, Integer(-1) is error object
Integers::Integers()
	: n(0)
{
	
}

Integers::Integers(int size)
	: n(size), elements(std::vector<Integer>(size))
{
	for (int j = 0; j < n; j++)
		createNewElement(j);
}

void Integers::createNewElement(int m)
{
	Integer newInteger(m, this->n);
	this->elements[m] = newInteger;
}

Integer Integers::operator[](int x) const
{
	// we treat this like circular array
	int index = ((n > 1) ? x % n : x);
	if (index < 0)
	{ 
		if (n <= 1) return Integer(-1);
		index += n;
	}
	return this->elements[index];
}

int Integers::size() const { return this->n; }

Integer Integers::inverse(int x)
{
	// make sure x in (0, this->n) . If not, either throw exception or return 0
	if ((x <= 0) || (x >= this->n)) throw Integer(-1);
	// Extended Euclidean Algorithm
	int t = 0,
		r = this->n,
		newT = 1,
		newR = x;		
	while (newR != 0)
	{
		int quotient = r / newR,
			tCopy = t,
			rCopy = r,
			newTCopy = newT,
			newRCopy = newR;
		t = newT;
		newT = tCopy - quotient * newTCopy;
		r = newR;
		newR = rCopy - quotient * newRCopy;
	}
	if (r > 1)
	{
		throw Integer(-1);
	}
	if (t < 0) t = t + this->n;
	return Integer(t, this->n);
}

Integer Integers::inverse(const Integer& el)
{
	return this->inverse(el.val());
}