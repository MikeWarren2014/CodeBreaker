#ifndef PUNCTUATIONOCCURRENCELIST_H
#define PUNCTUATIONOCCURRENCELIST_H

#include <iostream>
#include <string>

#include "LinkedList.h"
#include "PunctuationOccurrence.h"

class PunctuationOccurrenceList : public LinkedList<PunctuationOccurrence>
{
	public:
		PunctuationOccurrenceList();
		PunctuationOccurrenceList(std::string&);
		PunctuationOccurrenceList(const PunctuationOccurrenceList&);
		//~PunctuationOccurrenceList();
		static PunctuationOccurrenceList parse(const std::string&);
		void emptyInto(std::string&);
		/*friend std::ostream& operator<<(std::ostream& o, const PunctuationOccurrenceList& l)
		{
			return o;
		}*/

	private:
		void fillFrom(std::string&);
		void logPunctuation(char, int);
};

#endif
