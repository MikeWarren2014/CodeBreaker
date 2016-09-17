#ifndef INTEGERS_H
#define INTEGERS_H

#include "Integer.h"

#include <vector>

class Integers
{
	public:
		Integers();
		Integers(int);
		Integer operator[](int) const;
		int size() const;
		Integer inverse(int);
		Integer inverse(const Integer&);
		friend std::ostream& operator<<(std::ostream& o, const Integers& i)
		{
			o << "{ ";
			for (int j = 0; j < i.elements.size(); j++)
			{
				o << i.elements[j] << ((j == i.elements.size() - 1) ? "} " : ", ");
			}
			return o;
		}		// for computing inverse of an Integer
	private:
		int n;
		std::vector<Integer> elements;
		void createNewElement(int);
};

#endif