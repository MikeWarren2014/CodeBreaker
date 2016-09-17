#ifndef PUNCTUATIONOCCURRENCE_H
#define PUNCTUATIONOCCURRENCE_H

#include <iostream>

class PunctuationOccurrence
{
	public:
		PunctuationOccurrence();
		PunctuationOccurrence(int, char);
		int getLocation() const;
		char getPunctuation() const;
		friend std::ostream& operator<<(std::ostream& o, const PunctuationOccurrence& p)
		{
			return (o << 
				"{\n\tcharacter: " << p.punctuation <<
				"\n\tlocation: " << p.spot << "}" << std::endl);
		}
	private:
		int spot;
		char punctuation;	
};

#endif
