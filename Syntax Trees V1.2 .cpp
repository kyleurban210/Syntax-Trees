// Version 1.2 of Kyle Urban's Syntax Tree Program

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//global consts

const int MAX = 50;
const int MAX2 = 30;

//structure prototypes
struct Word
{
	string parsed_word; //i fucked up here, this is an array of strings inside a structer
	char syntantic_class;    //yet fixing this will take hours and destroy the program
	char morphological_class;
	int length;

};



//function prototypes

void obtainSentence(string&, int&, int&, int&);
void parseSentence(string, int, int, int, Word[]);
void displayStats(int, int, int, Word[]);

void twoSets(string, int, int, int, Word[]);
void twoSetsST3(string, int, int, int, Word[]);

/*___________________________________________________________*/



int main()
{
	//structure declarations

	Word parsed_word[50];


	//variables

	string sentence;
	int length_with_spaces = 0;
	int length_no_spaces = 0;
	int num_of_words = 0;

	//function calls

	obtainSentence(sentence, length_with_spaces, length_no_spaces, num_of_words);
	parseSentence(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
	
	if (num_of_words == 2)
	{
		twoSets(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
	}

	displayStats(length_with_spaces, length_no_spaces, num_of_words, parsed_word);


}



/*--------------------------------------------------------*/

void obtainSentence(string& sentence, int& length_with_spaces, int& length_no_spaces, int& num_of_words)
{
	//gets sentence
	cout << "Please enter a sentence      *lower case only please; upper case has yet to be programmed*\n\n";
	getline(cin, sentence);

	//finds length of sentence with spaces
	length_with_spaces = 0;

	int i = 0;
	while (sentence[i] != NULL)
	{
		length_with_spaces += 1;
		i++;
	}

	//finds length of sentence without spaces
	length_no_spaces = 0;
	int j = 0;
	while (sentence[j] != NULL)
	{
		if (sentence[j] != ' ')
		{
			length_no_spaces += 1;
		}
		j++;
	}

	//finds total number of words in the sentence (assuming no clitics)
	num_of_words = 0;
	int p = 0;
	while (sentence[p] != NULL)
	{
		if (sentence[p] == ' ')
		{
			num_of_words += 1;
		}

		p++;
	}

	//offset fixer
	num_of_words = num_of_words + 1;
}

void parseSentence(string sentence, int length_with_spaces, int length_no_spaces, int num_of_words, Word parsed_word[])
{

	int i = 0;
	int j = 0;
	int h = 0;
	int holder_count = 0;

	do
	{
		parsed_word[i].parsed_word[j] = sentence[h];
		j += 1;

		if (sentence[h] == ' ' || sentence[h] == NULL)
		{
			parsed_word[i].length = j - 1;
		}
		if (sentence[h] == ' ')
		{
			i += 1;
			j = 0;
		}
		h += 1;
	} while (sentence[h] != NULL);

	//final word char count   --- nerdly neerrrr

	j = 0;
	i = num_of_words - 1;

	do
	{
		j++;
	} while (parsed_word[i].parsed_word[j] != '\0');

	parsed_word[i].length = j;

	cout << endl << endl << endl;

	for (int k = 0; k < num_of_words; k++)
	{
		for (int n = 0; n < MAX; n++)
		{
			cout << parsed_word[k].parsed_word[n];
		}
		cout << "::  " << endl;
	}

	for (int qw = 0; qw < num_of_words; qw++)
	{

		cout << " the length of word " << qw + 1 << " is " << parsed_word[qw].length << endl;

	}
}

//display statistical information about the sentence
void displayStats(int length_with_spaces, int length_no_spaces, int num_of_words, Word parsed_word[])
{
	cout << " \n\n _________________________ \n\n";

	cout << "Length of whole string: " << length_with_spaces << endl;

	cout << "Length without spaces: " << length_no_spaces << endl;

	cout << "Number of Words in the Sentence: " << num_of_words << endl;

	for (int h = 0; h < num_of_words; h++)
	{
		cout << "\n\nThe syntatic class of word " << h + 1 << " is :    ";

		if (parsed_word[h].syntantic_class == 'D')
		{
			cout << "Determiner";
		}
		else if (parsed_word[h].syntantic_class == 'N')
		{
			cout << "Noun";
		}
		else if (parsed_word[h].syntantic_class == 'A')
		{
			cout << "Adjective";
		}
		else if (parsed_word[h].syntantic_class == 'V')
		{
			cout << "Verb";
		}
		else
		{
			cout << "Bratas";
		}

		cout << endl;
	}

}


void twoSets(string sentence, int length_with_spaces, int length_no_spaces, int num_of_words, Word parsed_word[])
{




	parsed_word[0].syntantic_class = 'B';

	//checking for ST2 via determiner in W1
	int i = 0;
	int f = 0;
	int g = 0;

	if (parsed_word[i].length == 1)
	{
		if (parsed_word[f].parsed_word[g] == 'a')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else
		{
			//call different function for ST1 vs ST3
			twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
		}

	}
	else if (parsed_word[i].length == 2)
	{
		//althoug these could be inside one if statement if using the or opperator, I am keeping them seperate
		//for future reasons and later improvements
		if (parsed_word[f].parsed_word[g] == 'a' && parsed_word[f].parsed_word[g + 1] == 'n')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}

		else if (parsed_word[f].parsed_word[g] == 'm' && parsed_word[f].parsed_word[g + 1] == 'y')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else
		{
			//call different function for ST1 vs ST3
			twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
		}


	}
	else if (parsed_word[i].length == 3)
	{
		if (parsed_word[f].parsed_word[g] == 't' && parsed_word[f].parsed_word[g + 1] == 'h' && parsed_word[f].parsed_word[g + 2] == 'e')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'o' && parsed_word[f].parsed_word[g + 1] == 'u' && parsed_word[f].parsed_word[g + 2] == 'r')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'h' && parsed_word[f].parsed_word[g + 1] == 'i' && parsed_word[f].parsed_word[g + 2] == 's')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'f' && parsed_word[f].parsed_word[g + 1] == 'e' && parsed_word[f].parsed_word[g + 2] == 'w')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'a' && parsed_word[f].parsed_word[g + 1] == 'n' && parsed_word[f].parsed_word[g + 2] == 'y')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'h' && parsed_word[f].parsed_word[g + 1] == 'e' && parsed_word[f].parsed_word[g + 2] == 'r')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';
		}
		else
		{
			//call different function for ST1 vs ST3
			twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
		}

	}
	else if (parsed_word[i].length == 4)
	{
		if (parsed_word[f].parsed_word[g] == 't' && parsed_word[f].parsed_word[g + 1] == 'h' && parsed_word[f].parsed_word[g + 2] == 'i' && parsed_word[f].parsed_word[g + 3] == 's')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 't' && parsed_word[f].parsed_word[g + 1] == 'h' && parsed_word[f].parsed_word[g + 2] == 'a' && parsed_word[f].parsed_word[g + 3] == 't')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'y' && parsed_word[f].parsed_word[g + 1] == 'o' && parsed_word[f].parsed_word[g + 2] == 'u' && parsed_word[f].parsed_word[g + 3] == 'r')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'h' && parsed_word[f].parsed_word[g + 1] == 'e' && parsed_word[f].parsed_word[g + 2] == 'r' && parsed_word[f].parsed_word[g + 3] == 's')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'm' && parsed_word[f].parsed_word[g + 1] == 'a' && parsed_word[f].parsed_word[g + 2] == 'n' && parsed_word[f].parsed_word[g + 3] == 'y')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'm' && parsed_word[f].parsed_word[g + 1] == 'u' && parsed_word[f].parsed_word[g + 2] == 'c' && parsed_word[f].parsed_word[g + 3] == 'h')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 's' && parsed_word[f].parsed_word[g + 1] == 'o' && parsed_word[f].parsed_word[g + 2] == 'm' && parsed_word[f].parsed_word[g + 3] == 'e')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'e' && parsed_word[f].parsed_word[g + 1] == 'a' && parsed_word[f].parsed_word[g + 2] == 'c' && parsed_word[f].parsed_word[g + 3] == 'h')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else
		{
			//call different function for ST1 vs ST3
			twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
		}

	}
	else if (parsed_word[i].length == 5)
	{
		if (parsed_word[f].parsed_word[g] == 't' && parsed_word[f].parsed_word[g + 1] == 'h' && parsed_word[f].parsed_word[g + 2] == 'e' && parsed_word[f].parsed_word[g + 3] == 's' && parsed_word[f].parsed_word[g + 4] == 'e')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 't' && parsed_word[f].parsed_word[g + 1] == 'h' && parsed_word[f].parsed_word[g + 2] == 'o' && parsed_word[f].parsed_word[g + 3] == 's' && parsed_word[f].parsed_word[g + 4] == 'e')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 't' && parsed_word[f].parsed_word[g + 1] == 'h' && parsed_word[f].parsed_word[g + 2] == 'e' && parsed_word[f].parsed_word[g + 3] == 'i' && parsed_word[f].parsed_word[g + 4] == 'r')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else if (parsed_word[f].parsed_word[g] == 'e' && parsed_word[f].parsed_word[g + 1] == 'v' && parsed_word[f].parsed_word[g + 2] == 'e' && parsed_word[f].parsed_word[g + 3] == 'r' && parsed_word[f].parsed_word[g + 4] == 'y')
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

		}
		else
		{
			//call different function for ST1 vs ST3
			twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
		}
	}
	else
	{
		twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
	}

	if (parsed_word[i].syntantic_class == 'D' && num_of_words == 2)
	{
		parsed_word[i + 1].syntantic_class = 'N';
	}





}


//in the event that ST2 is proven false, comes from the else statement from the twoSets Function

void twoSetsST3(string sentence, int length_with_spaces, int length_no_spaces, int num_of_words, Word parsed_word[])
{



	for (int p = 0; p < parsed_word[0].length; p++)
	{
		if (parsed_word[0].parsed_word[p] == 'y')
		{
			//the word (you) causes some problems that needed to be addressed
			if (parsed_word[0].parsed_word[p + 1] == 'o' && parsed_word[0].parsed_word[p + 2] == 'u')
			{
				parsed_word[0].syntantic_class = 'N';
				break;
			}
			else
			{
				parsed_word[0].syntantic_class = 'A';
				break;
			}
		}
		else if (parsed_word[0].parsed_word[p] == 'l' && parsed_word[0].parsed_word[p + 1] == 'y')
		{
			parsed_word[0].syntantic_class = 'A';
			break;

		}
		else if (parsed_word[0].parsed_word[p] == 'e' && parsed_word[0].parsed_word[p + 1] == 'r')
		{
			parsed_word[0].syntantic_class = 'A';
			break;
		}
		//this only works by virtue of being the first word
		//(will not work in questionative sentences as English is a Wh-movement langauge with verb taking first position)
		else if (parsed_word[0].parsed_word[p] == 'e' && parsed_word[0].parsed_word[p + 1] == 'n')
		{
			parsed_word[0].syntantic_class = 'A';
			break;
		}
		else if (parsed_word[0].parsed_word[p] == 'e' && parsed_word[0].parsed_word[p + 1] == 's' && parsed_word[0].parsed_word[p + 2] == 't')
		{
			parsed_word[0].syntantic_class = 'A';
			break;
		}
		else if (parsed_word[0].parsed_word[p] == 'i' && parsed_word[0].parsed_word[p + 1] == 'e' && parsed_word[0].parsed_word[p + 2] == 'r')
		{
			parsed_word[0].syntantic_class = 'A';
			break;
		}
		else if (parsed_word[0].parsed_word[p] == 'i' && parsed_word[0].parsed_word[p + 1] == 's' && parsed_word[0].parsed_word[p + 2] == 'h')
		{
			parsed_word[0].syntantic_class = 'A';
			break;
		}
		else
		{
			//in this case, the ST1 is most likely a Noun-Verb pairing.
			// though english language's reusage of derivational morphemes doesn't make this 
			//guess work any easier >:(


			//cout << 'Rong 22';
			//sets us to ST1

			/*
			parsed_word[0].syntantic_class = 'N';
			parsed_word[1].syntantic_class = 'V';

			parsed_word[0].morphological_class = 'N';
			parsed_word[1].morphological_class = 'V';
			break;
			*/

		}






	}

	if (parsed_word[0].syntantic_class == 'A')
	{
		parsed_word[0].morphological_class = 'A';
		parsed_word[1].morphological_class = 'N';
		parsed_word[1].syntantic_class = 'N';


	}
	if (parsed_word[0].syntantic_class != 'A')
	{
		parsed_word[0].syntantic_class = 'N';
		parsed_word[0].morphological_class = 'N';
		parsed_word[1].morphological_class = 'V';
		parsed_word[1].syntantic_class = 'V';


	}

}

