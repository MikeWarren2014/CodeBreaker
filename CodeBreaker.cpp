#include "CodeBreaker.h"

#include <iostream>
#include <fstream>
#include <algorithm>

CodeBreaker::CodeBreaker()
	: Z(Integers::Integers(26)),
		punctuation(PunctuationOccurrenceList::PunctuationOccurrenceList())
{
	// initialize charFrequencyMap
	this->initCharMap();
	
}

CodeBreaker::CodeBreaker(std::string& ciphertext)
	: Z(Integers::Integers(26)), 
		punctuation(PunctuationOccurrenceList::PunctuationOccurrenceList(ciphertext)),
		ciphertext(ciphertext)
{
	// initialize charFrequencyMap
	this->initCharMap();
	this->computeFrequency(ciphertext);
	// create numeric codes
	this->makeNumericCodes();
	// rank characters by frequency
	this->rankCharacters();
}

CodeBreaker::CodeBreaker(std::string& str, bool readFromFile)
	: Z(Integers::Integers(26))
{
	// if reading from file
	if (readFromFile)
	{
		// str is filename to read from 
		// open file specified by str
		std::ifstream input(str.c_str());
		std::string line;
		// read contents to ciphertext
		while (std::getline(input, line))
		{
			this->ciphertext += line + "\n";
		}
		// close file
		input.close();
	}
	// otherwise
	else
	{
		// str is ciphertext itself
		// write it to this->ciphertext
		this->ciphertext = str;
	}
	// strip punctuation
	this->punctuation = PunctuationOccurrenceList::PunctuationOccurrenceList(this->ciphertext);
	// initialize charFrequencyMap
	this->initCharMap();
	// compute frequency of characters
	this->computeFrequency(this->ciphertext);
	// log numeric codes ('A' => 0, 'B' => 1, ... , 'Z' => 25)
	this->makeNumericCodes();
	// rank characters by frequency
	this->rankCharacters();
}

const std::string CodeBreaker::mostFrequentEnglishCharacters = "etaoinshrdlcumwfgypbvkjxqz";

void CodeBreaker::cryptAnalysis(CipherType cipher)
{
	// if this->ciphertext empty, return
	if (this->ciphertext.empty()) return;
	// copy ciphertext to plaintext
	this->plaintext = this->ciphertext;
	// if cipher is either SUBSTITUTION or AFFINE
	if ((cipher == SUBSTITUTION) || (cipher == AFFINE))
	{
		// replace most common character of ciphertext with 'e', in plaintext
		std::replace(this->plaintext.begin(),
				this->plaintext.end(),
				this->mostFrequentCipherChars[0],
				'e');
		// update the numericCodes as well
		std::replace(this->numericCodes.begin(),
				this->numericCodes.end(),
				this->Z[this->getNumericCodeFor(this->mostFrequentCipherChars[0])],
				this->Z[4]);
	}
	
}

void CodeBreaker::decryptAffine()
{
	// if this->ciphertext is empty, return
	if (this->ciphertext.empty()) return;
	// make sure what is recorded as the most frequent character in ciphertext isn't in plaintext
	int mostCommonCharacter = this->plaintext.find_first_of(this->mostFrequentCipherChars[0]);
	// if it is	
	if (mostCommonCharacter != -1)
	{
		// replace it with 'e' in numericCodes
		/*std::replace(this->plaintext.begin(),
					 this->plaintext.end(),
					 this->mostFrequentCipherChars[0],
					 'e');*/
		std::replace(this->numericCodes.begin(),
				this->numericCodes.end(),
				this->Z[this->getNumericCodeFor(this->mostFrequentCipherChars[0])],
				this->Z[4]);
	}
	// get Integer for most frequent ciphercharacter and English character
	Integer y1 = this->Z[this->getNumericCodeFor(this->mostFrequentCipherChars[0])],
						 x1 = this->Z[this->getNumericCodeFor('e')];
	// now time to replace 't'
	// for each of the next 7 most frequent characters
	for(int j = 1; j < 7; j++)
	{
		// get Integer for it and 't'
		Integer y2 = this->Z[this->getNumericCodeFor(this->mostFrequentCipherChars[j])],
							 x2 = this->Z[this->getNumericCodeFor('t')];
		
		// compute determinant of what would be the coefficient matrix. Formula for this is x1 - x2
		Integer det = x1 - x2;
		// determinant should be relatively prime to 26. It is iff it is relatively prime to its factors 2,13
		// if it is, we can continue
		if ((det % 2 != 0) && (det % 13 != 0))
		{
			// we compute invdet,a,b
			Integer invdet = this->Z.inverse(det),
								 a = invdet * (y1 - x2 * y2),
								 b = invdet * (-y2 + x1 * y1);
			// we now have formula for decrypting: x = inverse(a) * (y-b)
			try
			{
				Integer inva = this->Z.inverse(a);
				// we apply that formula to each of the remaining characters
				// for every character that is neither y1 or y2
				for (int y = 0; y < 26; y++)
				{
					if ((y != y1.val()) && (y != y2.val()))
					{
						// use formula to compute replacement character
						Integer x = inva * (y - b);
						// perform replacement
						std::replace(this->numericCodes.begin(),
									 this->numericCodes.end(),
									 Integer(y, this->Z.size()),
									 x);
					}
				}
				// form this->plaintext from this->numericCodes
				this->writeNumericCodesTo(this->plaintext, false);
				// if this->plaintext is readable, we need not keep trying
				if (this->isReadablePlaintext()) return;
			}
			catch (Integer& er)
			{
				// simply move to the next one
			}
		}
	}
}

bool CodeBreaker::isReadablePlaintext()
{
	// clone PunctuationOccurrenceList
	PunctuationOccurrenceList listClone(this->punctuation);
	// empty clone into this->plaintext
	listClone.emptyInto(this->plaintext);
	// output this->plaintext
	std::cout << "Plaintext resolved to : \n\n" << this->plaintext << "\n" << std::endl;
	std::string userResponse;
	// ask user if this->plaintext is readable
	while ((userResponse != "yes") && (userResponse != "no"))
	{
		std::cout << "Is the plaintext readable to you? (yes/no) :";
		std::getline(std::cin, userResponse);
		std::transform(userResponse.begin(), userResponse.end(), userResponse.begin(), ::tolower);
	}
	// log user answer
	return (userResponse == "yes");
}

void CodeBreaker::initCharMap()
{
	for (char c = 'A'; c <= 'Z'; c++)
	{
		this->charFrequencyMap[c] = 0;
	}
}

void CodeBreaker::resetCharMap() { this->initCharMap(); }

std::string CodeBreaker::getMostFrequentCipherChars() const { return this->mostFrequentCipherChars; }

int CodeBreaker::getNumericCodeFor(char c) const
{
	// if character is in ['A', 'Z']
	if ((c >= 'A') && (c <= 'Z'))
		// return its int value minus 'A'
		return (int)(c - 'A');
	// otherwise, if it is in ['a', 'z']
	if ((c >= 'a') && (c <= 'z'))
		// return its int value minus 'a'
		return (int)(c - 'a');
	std::cout << "invalid character: " << c << std::endl;
	return -1;
}

char CodeBreaker::getCharacterFor(int x, bool isCipherCharacter) const
{
	return (char)(((isCipherCharacter) ? 'A' : 'a' ) + x);
}

void CodeBreaker::makeNumericCodes()
{
	std::cout << "this->ciphertext.size() == " << this->ciphertext.size() << std::endl;
	std::cout << "this->numericCodes.capacity() == " << this->numericCodes.capacity() << std::endl;
	std::cout << "this->numericCodes.max_size() == " << this->numericCodes.max_size() << std::endl;
	// if there isn't as many numeric codes as there are characters in ciphertext
	while (this->numericCodes.size() < this->ciphertext.size())
	{
		std::cout << "this->numericCodes.capacity() == " << this->numericCodes.capacity() << std::endl;
		// initialize numericCodes
		// this->numericCodes = std::vector<Integer>(this->ciphertext.size());
		std::cout << "this->numericCodes.size() == " << this->numericCodes.size() << std::endl;
		this->numericCodes.push_back(this->Z[0]); 
	}
	// for every character in ciphertext
	for (int j = 0; j < this->ciphertext.size(); j++)
	{
		// if character's numerical code is not logged in numericCodes
		int numericCode = this->getNumericCodeFor(ciphertext[j]);
		if (numericCode != this->numericCodes[j].val())
			// log it
			this->numericCodes[j] = this->Z[numericCode];
			
	}
	// while there are more numericCodes than characters in ciphertexts
	while (this->numericCodes.size() > this->ciphertext.size())
		// remove last character
		this->numericCodes.pop_back();
}

void CodeBreaker::writeNumericCodesTo(std::string& target, bool isCipherCharacter)
{
	// make sure target is empty
	if (!target.empty()) target = "";
	// make sure numeric codes not empty
	if (this->numericCodes.empty())
	{
		// for now, we make numeric codes from this->ciphertext
		this->makeNumericCodes();
	}
	// for every Integer in this->numericCodes
	for (int j = 0; j < this->numericCodes.size(); j++)
	{
		// lookup character for it and append to target
		target += this->getCharacterFor(this->numericCodes[j].val(), isCipherCharacter);
	}
}


void CodeBreaker::rankCharacters()
{
	// make sure ciphertext,charFrequencyMap not empty
	// if ciphertext empty, reset map and return
	if (ciphertext.empty())
	{
		this->initCharMap();
		return;
	}
	// if charFrequencyMap empty
	if (this->charFrequencyMap.empty())
	{
		// if ciphertext not empty
		if (!this->ciphertext.empty())
		{
			// compute its frequency
			this->computeFrequency(this->ciphertext);
		}
	}
	// sort map by value
	std::vector<std::pair<char, int> > myVec(this->charFrequencyMap.begin(), 
											 this->charFrequencyMap.end());
	std::sort(myVec.begin(), myVec.end(), &CodeBreaker::pairCompare);
	// dump sorted keys (characters) into mostFrequentCipherChars
	this->mostFrequentCipherChars = "";
	for (int j = 0; j < myVec.size(); j++)
	{
		this->mostFrequentCipherChars += myVec[j].first;
	}
}

void CodeBreaker::computeFrequency(std::string& ciphertext)
{
	this->ciphertext = ciphertext;
	this->resetCharMap();
	// tally every letter in ciphertext
	for (int i = 0; i < ciphertext.length(); i++)
	{
		this->charFrequencyMap[ciphertext[i]]++;
	}
}


/* assumption to be made when running this function: charFrequencyMap tied to ciphertext
 * to check that this is true would require cloning charFrequencyMap, plus O(n) time on the string, plus O(m) time on checking that clone, where n is size of string and m is number of elements in cloned map */
long double CodeBreaker::indexOfCoincidence()
{
	// if no ciphertext or charFrequencyMap empty
	if ((this->ciphertext.empty()) || (this->charFrequencyMap.empty()))
	{
		// there is nothing.
		return 0L;
	}
	long double ioc = 0L, characterCount = 0L;
	// walk through the charFrequencyMap
	for (char c = 'A'; c <= 'Z'; c++)
	{
		long double f = (long double)(this->charFrequencyMap[c]);
		// add f choose 2 to ioc
		ioc += f * (f-1);
		// add f to characterCount
		characterCount += f;
	}
	// index of coincidence is the sum of f choose 2, divided by characterCount choose 2
	ioc /= (characterCount * (characterCount - 1));
	return ioc;
}

long double CodeBreaker::indexOfCoincidence(std::string& str)
{
	// if this function is used, assume that end-user wants to replace this->ciphertext with str
	this->ciphertext = str;
	// in that case, reset charFrequencyMap
	this->resetCharMap();
	// reset punctuation, too, populating it with str
	this->punctuation = PunctuationOccurrenceList(str);
	// computeFrequency for str
	this->computeFrequency(str);
	// then return str's indexOfCoincidence
	return this->indexOfCoincidence();
}

std::string CodeBreaker::getPlaintext() const { return this->plaintext; }
std::string CodeBreaker::getCiphertext() const { return this->ciphertext; }

void CodeBreaker::printCharacterFrequencyMap()
{
	std::cout << "this->charFrequencyMap == {\n";
	for (char c = 'A'; c <= 'Z'; c++)
	{
		std::cout << "\t\'" << c << "\' => " << this->charFrequencyMap[c] << "\n";
	}
	std::cout << "}" << std::endl;
}