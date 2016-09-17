#include <iostream>
#include <sstream>
#include <string>

#include <vector> // remove this after you're done
#include "Integers.h"
#include "PunctuationOccurrence.h"
#include "PunctuationOccurrenceList.h"
#include "CodeBreaker.h"

using namespace std;

enum TestingObject {INTEGERS, PUNCTUATION_OCCURRENCE_LIST };

void testInverse(int x, const Integers& r)
{
	try
	{
		cout << "inverse(" << x << ") == " << (const_cast<Integers&>(r)).inverse(x) << endl;
	}
	catch (Integer& el)
	{
		cout << x << " is non-invertible" << endl;
	}
}

void testInverse(const Integer& el, const Integers& r)
{
	testInverse(el.val(), r);
}

void test(TestingObject testType)
{
	if (testType == INTEGERS)
	{
		// try creating Integers
		Integers Z(26);
		// print the ring
		cout << "Z == " << Z << endl;
		// create some Integer with specified value
		Integer c(3, Z.size()), d(4, Z.size());
		// test the operations on it
		
		cout << "c == " << c << "\nd == " << d << endl;
		cout << "c + d == " << (c + d) << endl;
		cout << "c - d == " << (c - d) << endl;
		cout << "c * d == " << (c * d) << endl;
		/*cout << "(c += d) == " << (c += d) << endl;
		cout << "(c -= d) == " << (c -= d) << endl;
		cout << "(c *= d) == " << (c *= d) << endl;*/
		cout << "c^2 - d^2 == " << (c * c - d * d) << endl;
		testInverse(const_cast<Integer&>(c), Z);
		testInverse(const_cast<Integer&>(d), Z);
		// attempt to fetch Element from Z using operator[]
		cout << "Fifth element in Z is: " << Z[5] << endl;
		// perform an actual calculation from attempt at cracking affine cipher on ciphertext2.txt
		/* a11 = 4,
		   a12,a22 = 1,
		   a21 = 19,
		   b1 = 6,
		   b2 = 25 */
		Integer a11 = Z[19],
							 a12 = Z[1],
							 a21 = Z[4],
							 a22 = a12,
							 b1 = Z[25],
							 b2 = Z[12];
		/* det = 4
		Integer a11 = Z[8],
							 a12 = Z[1],
							 a21 = Z[4],
							 a22 = a12,
							 b1 = Z[3],
							 b2 = Z[7];*/
		// compute "matrix inverse"
		
		Integer det = a11 * a22 - a21 * a12;
		try
		{
			Integer invdet = Z.inverse(det);
			cout << "invdet == " << invdet << endl;
			Integer A = invdet * (a22 * b1 - a21 * b2),
								 B = invdet * (-a12 * b1 + a11 * b2);
			cout << "A == " << A << "\nB == " << B << endl;
			cout << "A % 2 == " << A % 2 << endl;
		}
		catch (Integer& el)
		{
			cout << "det == " << det << " is not invertible." << endl;
			// attempt to visually debug code
		}
	}
	else if (testType == PUNCTUATION_OCCURRENCE_LIST)
	{
		// create PunctuationOccurrenceList initialized from sentence
		string sentence = "Some sentence that is full of punctuation (like this). It is supposed to be \"test\".";
		PunctuationOccurrenceList list(sentence);
		// print it
		cout << list << endl;
		cout << "sentence == " << sentence << endl;
		list.emptyInto(sentence);
		cout << list << endl;
		cout << "sentence == " << sentence << endl;		
	}
}

int main()
{
	//test(INTEGERS);
	/*CodeBreaker c;
	string str = "MATHEMATICA.";
	PunctuationOccurrenceList p(str);
	c.computeFrequency(str);
	c.printCharacterFrequencyMap();
	cout << "Index of coincidence : " << c.indexOfCoincidence() << endl;
	string str1 = "MAEHTIMCATA";
	c.computeFrequency(str1);
	c.printCharacterFrequencyMap();
	cout << "Index of coincidence : " << c.indexOfCoincidence() << endl;
	p.emptyInto(str);*/
	// TODO: decide implementation of interface to present to end-user (you and the teacher)
	bool PRODUCTION_MODE = true;
	if (PRODUCTION_MODE)
	{
	string userInput;
	// display informational message
	cout << "Message decrypter" << "\n"
		 << "-----------------" << "\n\n"
		 << "Written by Michael Warren" << "\n" << endl;
	int choice = 0;
	// prompt user for choice of input method
	while (choice == 0)
	{
		cout << "Please choose from the following ciphertext input modes:" << "\n";
		cout << " 1 - direct input" << "\n"
			 << " 2 - read from file" << "\n\n"
			 << " > ";
		getline(cin, userInput);
		stringstream(userInput) >> choice;
		if ((choice != 1) && (choice != 2))
		{
			cout << "Invalid choice. Please try again..." << endl;
		}
	}
	string ciphertext, filename;
	// depending on choice, get either filename or plain ciphertext
	if (choice == 1)
	{
		cout << "Please enter ciphertext : ";
		getline(cin, ciphertext);
	}
	else
	{
		cout << "Please enter filename : ";
		getline(cin, filename);			
	}
	// start CodeBreaker
	CodeBreaker c(((ciphertext.empty()) ? filename : ciphertext), (ciphertext.empty()));
	c.printCharacterFrequencyMap();
	// attempt affine decryption
	//c.decryptAffine();
	cout << "Characters in order of most frequent to least frequent: " << c.getMostFrequentCipherChars() << endl;
	cout << "Index of coincidence: " << c.indexOfCoincidence() << endl;
	}
	else
	{
		//test(PUNCTUATION_OCCURRENCE_LIST);
		//test(INTEGERS);
		//test vector
		vector<Integer> a;
		Integers Z(26);
		cout << "a.capacity == " << a.capacity() << endl;
		while (a.size() < 2400)
		{
			a.push_back(Z[0]);
		}
		cout << "a.size() == " << a.size() << endl;
		for (int j = 0; j < 26; j++)
		{
			cout << a[j] << " ";
		}
	}
	return 0;
}
