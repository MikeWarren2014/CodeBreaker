#include "PunctuationOccurrence.h"

PunctuationOccurrence::PunctuationOccurrence()
 : spot(-1), punctuation((char)0)
{

}

PunctuationOccurrence::PunctuationOccurrence(int s, char c) 
 : spot(s), punctuation(c)
{
	
}

int PunctuationOccurrence::getLocation() const { return this->spot; }
char PunctuationOccurrence::getPunctuation() const { return this->punctuation; }
