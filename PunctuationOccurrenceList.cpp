#include "PunctuationOccurrenceList.h"
#include "PunctuationOccurrence.h"

#include <string>

PunctuationOccurrenceList::PunctuationOccurrenceList()
{
	
}

PunctuationOccurrenceList::PunctuationOccurrenceList(std::string& str)
{
	this->fillFrom(str);
}

PunctuationOccurrenceList::PunctuationOccurrenceList(const PunctuationOccurrenceList& l)
 : LinkedList<PunctuationOccurrence>::LinkedList(l)
{

}

/*PunctuationOccurrenceList::~PunctuationOccurrenceList()
{
	// if this is not empty 
	if (!this->isEmpty())
	{
		// empty it
		this->empty();
	}
}*/

void PunctuationOccurrenceList::fillFrom(std::string& str)
{
	// if this is empty
	if (this->isEmpty())
	{
		// extract all punctuation marks from str into this
		// NOTE: punctuation marks include ' ', ',' '.', '\'', '\"', '(', ')', '-'
		std::string punctuations = " ,.\'\"()-?!10\n\r:;";
		// for every puncuation found
		//bool firstPunctuation = true;
		for (int pos = str.find_first_of(punctuations);
				pos != -1;
				pos = str.find_first_of(punctuations, pos))
		{
			// log PunctuationOccurrence to this
			int regPos = pos + this->size();
			this->logPunctuation(str[pos], regPos);
			str.erase(pos, 1);
		}
	}
}

PunctuationOccurrenceList PunctuationOccurrenceList::parse(const std::string& str)
{
	// create blank PunctuationOccurrenceList
	PunctuationOccurrenceList list;
	// extract all punctuation marks from str into blank list
	// NOTE: punctuation marks include ' ', ',' '.', '\'', '\"', '(', ')', '-'
	std::string punctuations = " ,.\'\"()-";
	// for every puncuation found
	for (int pos = str.find_first_of(punctuations);
			pos != -1;
			pos = str.find_first_of(punctuations, pos + 1))
	{
		// log PunctuationOccurrence to list
		list.logPunctuation(str[pos], pos);
	}
	return list;
}

void PunctuationOccurrenceList::logPunctuation(char c, int pos)
{
	this->addToEnd(PunctuationOccurrence(pos, c));
}

void PunctuationOccurrenceList::emptyInto(std::string& str)
{
	// NOTE: Assumption is that this is sorted by spot of PunctuationOccurrence. Unexpected results will occur if assumption not true.
	// remove every PunctuationOccurrence this contains and dump it back into str
	while (!this->isEmpty())
	{
		PunctuationOccurrence o = this->eraseStartingElement();
		str.insert(o.getLocation(), 1, o.getPunctuation());
	}
}