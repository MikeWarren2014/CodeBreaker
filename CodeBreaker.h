#ifndef CODEBREAKER_H
#define CODEBREAKER_H

#include <string>
#include <map>
#include <utility>
#include <vector>

#include "CipherType.h"
#include "Integers.h"
#include "PunctuationOccurrenceList.h"

class CodeBreaker
{
	public:
		CodeBreaker();
		CodeBreaker(std::string&);
		CodeBreaker(std::string&, bool);
		// should any of these return string??
		void cryptAnalysis(CipherType);
		void cryptAnalysis(CipherType, std::string&);
		void decryptAffine();
		void decryptAffine(std::string&);
		void decryptHill();
		void decryptHill(std::string&);
		void decryptSubstitution();
		void decryptSubstitution(std::string&);
		void decryptVigenere();
		void decryptVigenere(std::string&);
		std::string getMostFrequentCipherChars() const;
		void computeFrequency(std::string&);
		long double indexOfCoincidence();
		long double indexOfCoincidence(std::string&);
		// getter functions 
		std::string getPlaintext() const;
		std::string getCiphertext() const;
		// test function...
		void printCharacterFrequencyMap();
		static const long double englishIOC = 0.065L;
	private:
		PunctuationOccurrenceList punctuation;
		Integers Z;
		void initCharMap();
		void resetCharMap();
		void makeNumericCodes();
		void rankCharacters();
		void writeNumericCodesTo(std::string&, bool);
		bool isReadablePlaintext();
		int getNumericCodeFor(char) const;
		char getCharacterFor(int, bool) const;
		std::map<char, int> charFrequencyMap;
		std::vector<Integer> numericCodes;
		std::string ciphertext, plaintext;
		std::string cipherFilename;
		// ranking of ciphertext characters by how frequent they are
		// fixed length: 
		std::string mostFrequentCipherChars;
		static const std::string mostFrequentEnglishCharacters;
		// helper function for sorting map
		static bool pairCompare(std::pair<char,int> first, std::pair<char,int> second)
		{
			return (second.second < first.second);
		}
};

#endif