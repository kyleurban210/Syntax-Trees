//Kyle Urban

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
	string parsed_word[MAX]; //i fucked up here, this is an array of strings inside a structer
	char syntantic_class;    //yet fixing this will take hours and destroy the program
	char morphological_class;
	int length ;
	string grammatical_case;
	string number;
	string grammatical_gender;
	string person;
	string tense;
	string mood;
	string aspect;
	string voice;
	bool is_modal;

};



  /* *****   GUIDE  ******
  
  N == noun
  V == verb
  A == adjective
  P == prepostion
  D == determiner
  Y == adverb
  U == auxiliary
  R == pronoun
  C == conjunction
  M == degree marker
  X == in need of recheck
  ? == truly unknown



  plu == plural     ___________  N D
  sing == singular  -----------  N D
  1st == first person
  2nd == second person
  3rd == third person
  fem === female
  masc == male
  net == nuetered
  nom == nominative case --------- N
  acc == accuastive case --------- N
  dat == dative case ------------- N
  past == past tense  ------------ V
  pres == present tense ---------- V
  fut == future tense ------------ V

  ind == indicative mood
  subjn === subjunctive mood 
  imp == imperative mood (commanding verbs)

  perf
  imperf
  habit

  pass
  actv


  xxx == undetermineable grammatical feature  ---- all
  
  
  *****************************/ 

//function prototypes



void obtainSentence(string&, int&, int&, int&);
void parseSentence(string, int, int, int, Word[]);
void splitNPVP(string, int, int, int);
void twoSets(string, int, int, int, Word[], int&, bool&);      //tests for determiners
void twoSetsST3(string, int, int, int, Word[], int&, bool&);    //tests between adjective v.s noun
void prepositionTest(string, int, int, int, Word[], int&, bool&);  // tests for prepositions
void auxiliaresTest(string, int, int, int, Word[], int&); // tests for auxiliares and modals
void adverbTest(string, int, int, int, Word[], int&); //tests for adverbs
void verbTest(string, int, int, int, Word[], int&); // verb test
//void verbphraseManager(string, int, int, int, Word[], int&); // for that annoying ass error that keeps appearing

void checkAgain(string, int, int, int, Word[], int&, bool&);
void pronounTest(string, int, int, int, Word[], int&, bool&);
void properNounFilter(string, int, int, int, Word[], int&, bool&);
void determinerFilter(string, int, int, int, Word[], int&, bool&, int&);
int findNominativeCase(string, int, int, int, Word[], int&, bool&);
void syntacticTally(string, int, int, int, Word[], int&, bool&, int&, int&, int&, int&, int&, int&, int&, bool&, int&);
void fixingFalses(string, int, int, int, Word[], int&, int&, bool&, int&, int&, int&, int&, int&, int&, int&, bool&);


void displayStats(int, int, int, Word[], bool);


//driver function
int main()
{
	
	bool rerun = 0;


	

	//structure declarations

	Word parsed_word[50];
	
	
	//variables

	string sentence;
	int length_with_spaces = 0;
	int length_no_spaces = 0;
	int num_of_words = 0;
	int accumlator_chars_of_each[30] = { 0 }; //useless variable (needs to be removed)
	int test = 1;
	int word_tracker = 0; //this tracks what word we are currently analyzing (keeps for loops in sync)
	bool recheck = 0; //this is to switch function from run mode to recheck mode 
	//changes to 1 in checkAgain by default, watchout for this.

	int noun_count = 0;
	int verb_count = 0;
	int adj_count = 0;
	int prep_count = 0;
	int det_count = 0;
	int aux_count = 0;
	int adv_count = 0;
	int X_count = 0;
	bool nvn_falsity = 0; //is the switch to check for this
	bool isolated_prep_check = 0;

	
	//function calls

	
		obtainSentence(sentence, length_with_spaces, length_no_spaces, num_of_words);
		parseSentence(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word);
		//splitNPVP(sentence, length_with_spaces, length_no_spaces, num_of_words);
		
		cout << "\n\nRun test #3 (50% w/recheck) or Run Test #4 (morphosyntax)? (Enter 3 or 4)\n\n";
		cin >> test;

		if (test == 1 || test == 2)
		{
			
			test = 3;
			
		}

		if (test == 3 || test == 4)
		{
			
			prepositionTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);
			int bvp = 0;

			for (bvp = 0; bvp < num_of_words; bvp++)
			{
				if (parsed_word[bvp].syntantic_class == 'N' && (parsed_word[bvp + 1].syntantic_class != 'P'))
				{
					word_tracker = bvp + 1;

						//cout << "eoeoeoeoeoeo";


						auxiliaresTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);


				}

			}

		}
		
			

		displayStats(length_with_spaces, length_no_spaces, num_of_words, parsed_word, recheck);

		if (test == 3 || test == 4)
		{
			syntacticTally(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck, noun_count, verb_count, adj_count, prep_count, det_count, aux_count, adv_count, nvn_falsity, X_count);

			if (test == 4)
			{

				cout << "\n\n __________________________________ \n\n";

				checkAgain(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);

				cout << "\n\n\n______________________________________ \n\n\n";

			}

			displayStats(length_with_spaces, length_no_spaces, num_of_words, parsed_word, recheck);
			

			//cout << "Stubb 99";
		}



		//auxiliaresTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);



		//cout << "\n\nRerun the program? (1 for Yes / 0 for No) ";
		//cin >> rerun;

	

}

//obtains the sentence from the user
void obtainSentence(string& sentence, int& length_with_spaces, int& length_no_spaces, int& num_of_words)
{
	//gets sentence
	cout << "Please enter a sentence      *lower case only please; upper case has yet to be programmed*\n\n";
	cout << "This program is built on the assumption that what you type doesn't contain a compound phrase \n\n";
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
		if (sentence[p] == ' ' )
		{
			num_of_words += 1;

		}

		p++;
	}

	//offset fixer
	num_of_words = num_of_words + 1;

	

}

//parses each word into its own data structure
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
		

	} while (parsed_word[i].parsed_word[j] != "\0");

	parsed_word[i].length = j;

	



	cout << endl << endl << endl;

	for(int k = 0; k < num_of_words; k++)
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
void displayStats(int length_with_spaces, int length_no_spaces, int num_of_words, Word parsed_word[], bool recheck)
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
			cout << "Determiner    ";
			
		} 
		else if (parsed_word[h].syntantic_class == 'N')
		{
			cout << "Noun            ";
		}
		else if (parsed_word[h].syntantic_class == 'A')
		{
			cout << "Adjective       ";
		}
		else if (parsed_word[h].syntantic_class == 'V')
		{
			cout << "Verb            ";
		}
		else if (parsed_word[h].syntantic_class == 'P')
		{
			cout << "Preposition     ";
		}
		else if (parsed_word[h].syntantic_class == 'U')
		{
			cout << "Auxiliary       ";
		}
		else if (parsed_word[h].syntantic_class == 'Y')
		{
			cout << "Adverb          ";
		}
		else if (parsed_word[h].syntantic_class == 'X')
		{
			cout << "Falsley Labelled" ;
		}
		else
		{
			cout << "** Error **";
		}

		cout << "       " << setw(10);


		for (int b = 0; b < parsed_word[h].length; b++)
		{
			cout  <<  parsed_word[h].parsed_word[b];
		}

		if (recheck == 1)
		{
			cout << "    ";


			if (parsed_word[h].syntantic_class == 'N' || parsed_word[h].syntantic_class == 'D')
			{
				cout << parsed_word[h].number << ".";

				if (parsed_word[h].syntantic_class == 'N')
				{
					cout << parsed_word[h].grammatical_case << ".";
					cout << parsed_word[h].grammatical_gender << ".";
				}


			}

			if (parsed_word[h].syntantic_class == 'V')
			{
				cout << parsed_word[h].tense << ".";
				cout << parsed_word[h].mood << ".";
				cout << parsed_word[h].aspect << ".";

			}
		}



		cout << endl;
	}

}


//runs through possible combos of two sets

void twoSets(string sentence, int length_with_spaces, int length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck)
{

	//word_tracker = 1; //manually set; must work without this
	
	//cout << " \n\n ****keeeeeee " << word_tracker;
	

	//checking for ST2 via determiner in W1 (well, now just any word)
	int i = word_tracker;
	int f = word_tracker;
	int g = 0;

	if (parsed_word[i].length == 1)
	{
		if (parsed_word[f].parsed_word[g] == "a")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "sing";

		}
		else
		{
			//call different function for ST1 vs ST3
			//twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
		}

	}
	else if (parsed_word[i].length == 2)
	{
		//althoug these could be inside one if statement if using the or opperator, I am keeping them seperate
		//for future reasons and later improvements
		if (parsed_word[f].parsed_word[g] == "a" && parsed_word[f].parsed_word[g + 1] == "n")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "sing";

		}

		else if (parsed_word[f].parsed_word[g] == "m" && parsed_word[f].parsed_word[g + 1] == "y")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant

		}
		else
		{
			//call different function for ST1 vs ST3
			//twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
		}


	}
	else if (parsed_word[i].length == 3)
	{
		if (parsed_word[f].parsed_word[g] == "t" && parsed_word[f].parsed_word[g + 1] == "h" && parsed_word[f].parsed_word[g + 2] == "e")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant

		}
		else if (parsed_word[f].parsed_word[g] == "o" && parsed_word[f].parsed_word[g + 1] == "u" && parsed_word[f].parsed_word[g + 2] == "r")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant
		}
		else if (parsed_word[f].parsed_word[g] == "h" && parsed_word[f].parsed_word[g + 1] == "i" && parsed_word[f].parsed_word[g + 2] == "s")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant
		}
		else if (parsed_word[f].parsed_word[g] == "f" && parsed_word[f].parsed_word[g + 1] == "e" && parsed_word[f].parsed_word[g + 2] == "w")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "plu";

		}
		else if (parsed_word[f].parsed_word[g] == "a" && parsed_word[f].parsed_word[g + 1] == "n" && parsed_word[f].parsed_word[g + 2] == "y")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant

		}
		else if (parsed_word[f].parsed_word[g] == "h" && parsed_word[f].parsed_word[g + 1] == "e" && parsed_word[f].parsed_word[g + 2] == "r")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant
		}
		else
		{
			//call different function for ST1 vs ST3
			//twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
		}

	}
	else if (parsed_word[i].length == 4)
	{
		if (parsed_word[f].parsed_word[g] == "t" && parsed_word[f].parsed_word[g + 1] == "h" && parsed_word[f].parsed_word[g + 2] == "i" && parsed_word[f].parsed_word[g + 3] == "s")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "sing";

		}
		else if (parsed_word[f].parsed_word[g] == "t" && parsed_word[f].parsed_word[g + 1] == "h" && parsed_word[f].parsed_word[g + 2] == "a" && parsed_word[f].parsed_word[g + 3] == "t")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "sing";

		}
		else if (parsed_word[f].parsed_word[g] == "y" && parsed_word[f].parsed_word[g + 1] == "o" && parsed_word[f].parsed_word[g + 2] == "u" && parsed_word[f].parsed_word[g + 3] == "r")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant

		}
		else if (parsed_word[f].parsed_word[g] == "h" && parsed_word[f].parsed_word[g + 1] == "e" && parsed_word[f].parsed_word[g + 2] == "r" && parsed_word[f].parsed_word[g + 3] == "s")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant

		}
		else if (parsed_word[f].parsed_word[g] == "m" && parsed_word[f].parsed_word[g + 1] == "a" && parsed_word[f].parsed_word[g + 2] == "n" && parsed_word[f].parsed_word[g + 3] == "y")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "plu";

		}
		else if (parsed_word[f].parsed_word[g] == "m" && parsed_word[f].parsed_word[g + 1] == "u" && parsed_word[f].parsed_word[g + 2] == "c" && parsed_word[f].parsed_word[g + 3] == "h")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "sing";

		}
		else if (parsed_word[f].parsed_word[g] == "s" && parsed_word[f].parsed_word[g + 1] == "o" && parsed_word[f].parsed_word[g + 2] == "m" && parsed_word[f].parsed_word[g + 3] == "e")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "plu";
		}
		else if (parsed_word[f].parsed_word[g] == "e" && parsed_word[f].parsed_word[g + 1] == "a" && parsed_word[f].parsed_word[g + 2] == "c" && parsed_word[f].parsed_word[g + 3] == "h")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "sing";

		}
		else
		{
			//call different function for ST1 vs ST3
			//twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
		}

	}
	else if (parsed_word[i].length == 5)
	{
		if (parsed_word[f].parsed_word[g] == "t" && parsed_word[f].parsed_word[g + 1] == "h" && parsed_word[f].parsed_word[g + 2] == "e" && parsed_word[f].parsed_word[g + 3] == "s" && parsed_word[f].parsed_word[g + 4] == "e")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "plu"; 

		}
		else if (parsed_word[f].parsed_word[g] == "t" && parsed_word[f].parsed_word[g + 1] == "h" && parsed_word[f].parsed_word[g + 2] == "o" && parsed_word[f].parsed_word[g + 3] == "s" && parsed_word[f].parsed_word[g + 4] == "e")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "plu";

		}
		else if (parsed_word[f].parsed_word[g] == "t" && parsed_word[f].parsed_word[g + 1] == "h" && parsed_word[f].parsed_word[g + 2] == "e" && parsed_word[f].parsed_word[g + 3] == "i" && parsed_word[f].parsed_word[g + 4] == "r")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "xxx"; //indeterminant

		}
		else if (parsed_word[f].parsed_word[g] == "e" && parsed_word[f].parsed_word[g + 1] == "v" && parsed_word[f].parsed_word[g + 2] == "e" && parsed_word[f].parsed_word[g + 3] == "r" && parsed_word[f].parsed_word[g + 4] == "y")
		{
			parsed_word[i].morphological_class = 'D';
			parsed_word[i].syntantic_class = 'D';

			parsed_word[i].number = "sing";
		}
		else
		{
			//call different function for ST1 vs ST3
			//twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
		}
	}
	else
	{
		//twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
	}

	//cout << "!!!!!!! " << parsed_word[i].parsed_word;

	if (parsed_word[i].syntantic_class == 'D')
	{
		//parsed_word[i + 1].syntantic_class = 'N';
		word_tracker = word_tracker + 1;
		twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);

	}
	else
	{
		if (parsed_word[i - 1].syntantic_class != 'U')
		{

			twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);
		}

	}
	


	 


}


//in the event that ST2 is proven false, comes from the else statement from the twoSets Function

void twoSetsST3(string sentence, int length_with_spaces, int length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck)
{

	//word_tracker = 2; //manually set; must work without this

	int f = word_tracker;

	for (int p = 0; p < parsed_word[f].length; p++)
	{
		if (parsed_word[f].parsed_word[p] == "y" && (parsed_word[f].parsed_word[p + 1] == " " || parsed_word[f].parsed_word[p + 1] == "\0"))
		{
			//the word (you) causes some problems that needed to be addressed
			if (parsed_word[f].parsed_word[p + 1] == "o" && parsed_word[f].parsed_word[p + 2] == "u")
			{
				parsed_word[f].syntantic_class = 'N';
				break;
			}
			else 
			{
				parsed_word[f].syntantic_class = 'A';
				break;
			}
		}
		else if (parsed_word[f].parsed_word[p] == "e" && parsed_word[f].parsed_word[p + 1] == "r" && (parsed_word[f].parsed_word[p + 2] == " " || parsed_word[f].parsed_word[p + 2] == "\0"))
		{
			parsed_word[f].syntantic_class = 'A';
			break;
		}
		//this only works by virtue of being the first word
		//(will not work in questionative sentences as English is a Wh-movement langauge with verb taking first position)
		else if (parsed_word[f].parsed_word[p] == "e" && parsed_word[f].parsed_word[p + 1] == "n" && (parsed_word[f].parsed_word[p + 2] == " " || parsed_word[f].parsed_word[p + 2] == "\0"))
		{
			parsed_word[f].syntantic_class = 'A';
			break;
		}
		else if (parsed_word[f].parsed_word[p] == "e" && parsed_word[f].parsed_word[p + 1] == "s" && parsed_word[f].parsed_word[p + 2] == "t" && (parsed_word[f].parsed_word[p + 3] == " " || parsed_word[f].parsed_word[p + 3] == "\0"))
		{
			parsed_word[f].syntantic_class = 'A';
			break;
		}
		else if (parsed_word[f].parsed_word[p] == "i" && parsed_word[f].parsed_word[p + 1] == "e" && parsed_word[f].parsed_word[p + 2] == "r" && (parsed_word[f].parsed_word[p + 3] == " " || parsed_word[f].parsed_word[p + 3] == "\0"))
		{
			parsed_word[f].syntantic_class = 'A';
			break;
		}
		else if (parsed_word[f].parsed_word[p] == "i" && parsed_word[f].parsed_word[p + 1] == "s" && parsed_word[f].parsed_word[p + 2] == "h" && (parsed_word[f].parsed_word[p + 3] == " " || parsed_word[f].parsed_word[p + 3] == "\0"))
		{
			parsed_word[f].syntantic_class = 'A';
			break;
		}
		else
		{
			//in this case, the ST1 is most likely a Noun-Verb pairing.
			// though english language's reusage of derivational morphemes doesn't make this 
			//guess work any easier >:(


			//cout << "Rong 22";
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

	if (parsed_word[f].syntantic_class == 'A')
	{
		parsed_word[f].morphological_class = 'A';
		word_tracker = word_tracker + 1;
		twoSetsST3(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);
		
		//parsed_word[f + 1].morphological_class = 'N';
		//parsed_word[f + 1].syntantic_class = 'N';


	}
	else if (parsed_word[f].syntantic_class != 'A')
	{
		//noun mitigation for verbs
		/*for (int p = 0; p < parsed_word[f].length; p++)
		{
			if (parsed_word[f].parsed_word[p] != "e" && parsed_word[f].parsed_word[p + 1] != "d" && (parsed_word[f].parsed_word[p + 2] == " " || parsed_word[f].parsed_word[p + 2] == "\0"))
			{

				parsed_word[f].syntantic_class = 'N';
				parsed_word[f].morphological_class = 'N';
			}
			else if(parsed_word[f].parsed_word[p] != "i" && parsed_word[f].parsed_word[p + 1] != "n" && parsed_word[f].parsed_word[p + 2] != "g" && (parsed_word[f].parsed_word[p + 3] == " " || parsed_word[f].parsed_word[p + 3] == "\0"))
			{
				parsed_word[f].syntantic_class = 'N';
				parsed_word[f].morphological_class = 'N';

			}
		
		}*/


		parsed_word[f].syntantic_class = 'N';
		parsed_word[f].morphological_class = 'N';
		//parsed_word[f + 1].morphological_class = 'V';
		//parsed_word[f + 1].syntantic_class = 'V';

		/*
		//detects adjectives retroactively
		if (parsed_word[f - 1].syntantic_class == 'N' && parsed_word[f].syntantic_class == 'N')
		{
			parsed_word[f - 1].syntantic_class = 'A';
		}*/


		word_tracker = word_tracker + 1; 
		
		prepositionTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);


	}
	/*else if (parsed_word[f].syntantic_class != 'A' && parsed_word[f - 1].syntantic_class == 'N')
	{

		auxiliaresTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);


	}*/

}


//checks for prepositions
void prepositionTest(string sentence, int length_with_spaces, int length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck)
{


	int p = word_tracker;
	int k = 0;

	for (p = word_tracker; p < num_of_words; p++)
	{
		for (k = 0; k < parsed_word[p].length; k++)
		{
			//TWO LETTERS
			if (parsed_word[p].length == 2)
			{
				//of
				if (parsed_word[p].parsed_word[k] == "o" && parsed_word[p].parsed_word[k + 1] == "f" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}

				//at
				else if (parsed_word[p].parsed_word[k] == "a" && parsed_word[p].parsed_word[k + 1] == "t" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
				//in
				else if (parsed_word[p].parsed_word[k] == "i" && parsed_word[p].parsed_word[k + 1] == "n" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
				//to
				else if (parsed_word[p].parsed_word[k] == "t" && parsed_word[p].parsed_word[k + 1] == "o" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
				//on
				else if (parsed_word[p].parsed_word[k] == "o" && parsed_word[p].parsed_word[k + 1] == "n" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
			}

			//THREE LETTERS
			else if (parsed_word[p].length == 3)
			{
				//for
				if (parsed_word[p].parsed_word[k] == "f" && parsed_word[p].parsed_word[k + 1] == "o" && parsed_word[p].parsed_word[k + 2] == "r" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
			}

			// FOUR LETTERS
			else if (parsed_word[p].length == 4)
			{


				//from
				if (parsed_word[p].parsed_word[k] == "f" && parsed_word[p].parsed_word[k + 1] == "r" && parsed_word[p].parsed_word[k + 2] == "o" && parsed_word[p].parsed_word[k + 3] == "m" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
				//with
				else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "i" && parsed_word[p].parsed_word[k + 2] == "t" && parsed_word[p].parsed_word[k + 3] == "h" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
				//over
				else if (parsed_word[p].parsed_word[k] == "o" && parsed_word[p].parsed_word[k + 1] == "v" && parsed_word[p].parsed_word[k + 2] == "e" && parsed_word[p].parsed_word[k + 3] == "r" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
				//down
				else if (parsed_word[p].parsed_word[k] == "d" && parsed_word[p].parsed_word[k + 1] == "o" && parsed_word[p].parsed_word[k + 2] == "w" && parsed_word[p].parsed_word[k + 3] == "n" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
			}

			//FIVE LETTERS
			else if (parsed_word[p].length == 5)
			{



				//after
				if (parsed_word[p].parsed_word[k] == "a" && parsed_word[p].parsed_word[k + 1] == "f" && parsed_word[p].parsed_word[k + 2] == "t" && parsed_word[p].parsed_word[k + 3] == "e" && parsed_word[p].parsed_word[k + 4] == "r" && (parsed_word[p].parsed_word[k + 5] == " " || parsed_word[p].parsed_word[k + 5] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
				//while
				else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "h" && parsed_word[p].parsed_word[k + 2] == "i" && parsed_word[p].parsed_word[k + 3] == "l" && parsed_word[p].parsed_word[k + 4] == "e" && (parsed_word[p].parsed_word[k + 5] == " " || parsed_word[p].parsed_word[k + 5] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}

			}

			//SIX LETTERS
			else if (parsed_word[p].length == 6)
			{



				//within
			   if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "i" && parsed_word[p].parsed_word[k + 2] == "t" && parsed_word[p].parsed_word[k + 3] == "h" && parsed_word[p].parsed_word[k + 4] == "i" && parsed_word[p].parsed_word[k + 5] == "n" && (parsed_word[p].parsed_word[k + 6] == " " || parsed_word[p].parsed_word[k + 6] == "\0"))
			     {
				   parsed_word[p].syntantic_class = 'P';
			     }
			//before
			   else if (parsed_word[p].parsed_word[k] == "b" && parsed_word[p].parsed_word[k + 1] == "e" && parsed_word[p].parsed_word[k + 2] == "f" && parsed_word[p].parsed_word[k + 3] == "o" && parsed_word[p].parsed_word[k + 4] == "r" && parsed_word[p].parsed_word[k + 5] == "e" && (parsed_word[p].parsed_word[k + 6] == " " || parsed_word[p].parsed_word[k + 6] == "\0"))
			     {
				   parsed_word[p].syntantic_class = 'P';
			     }
			}
			

			//SEVEN LETTERS
			//between

			else if (parsed_word[p].length == 7)
			{
				if (parsed_word[p].parsed_word[k] == "b" && parsed_word[p].parsed_word[k + 1] == "e" && parsed_word[p].parsed_word[k + 2] == "t" && parsed_word[p].parsed_word[k + 3] == "w" && parsed_word[p].parsed_word[k + 4] == "e" && parsed_word[p].parsed_word[k + 5] == "e" && parsed_word[p].parsed_word[k + 6] == "n" && (parsed_word[p].parsed_word[k + 7] == " " || parsed_word[p].parsed_word[k + 7] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
				//without
				else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "i" && parsed_word[p].parsed_word[k + 2] == "t" && parsed_word[p].parsed_word[k + 3] == "h" && parsed_word[p].parsed_word[k + 4] == "o" && parsed_word[p].parsed_word[k + 5] == "u" && parsed_word[p].parsed_word[k + 6] == "t" && (parsed_word[p].parsed_word[k + 7] == " " || parsed_word[p].parsed_word[k + 7] == "\0"))
				{
					parsed_word[p].syntantic_class = 'P';
				}
			}

		}

		if (recheck == 0)
		{


			if (parsed_word[p].syntantic_class == 'P')
			{

				parsed_word[p].morphological_class = 'P';


				/*
				//detects false prepositions retroactively
				if (parsed_word[p - 1].syntantic_class == 'P' && parsed_word[p].syntantic_class == 'P')
				{
					parsed_word[p - 1].syntantic_class = 'N';
				}*/


				word_tracker = word_tracker + 1;    //we will analyse the word after this for Det

				//cout << " \n\n ppppp " << word_tracker;

				/**if (parsed_word[p - 1].syntantic_class == 'N')
				{
					prepositionTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);

				}
				else
				{

					twoSets(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
					break;
				}*/
			}
			else if (parsed_word[p].syntantic_class != 'P')
			{
				word_tracker = word_tracker; //remains zero

				twoSets(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);
				break;
			}
			else
			{
				cout << "error";
			}
		}
		else if (recheck == 1)
		{
			cout << "shit wad";

		}


	}

	/*cout << parsed_word[p].syntantic_class;

	if (parsed_word[p].syntantic_class == 'P')
	{

		parsed_word[p].morphological_class = 'P';
		word_tracker = 1;    //we will analyse the word after this for Det

		cout << " \n\n ppppp " << word_tracker;

		twoSets(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);

	}
	else if(parsed_word[p].syntantic_class != 'P')
	{
		word_tracker = 0; //remains zero

		twoSets(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
	}
	else
	{
		cout << "error";
	}*/



}



//tests for auxiliares and modals
void auxiliaresTest(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker)
{

	int p = word_tracker;
	cout << word_tracker;
	
	for (p = word_tracker; p < num_of_words; p++)
	{
		for (int k = 0; k < parsed_word[p].length; k++)
		{
			//MODALS
			if (parsed_word[p].parsed_word[k] == "s" && parsed_word[p].parsed_word[k + 1] == "h" && parsed_word[p].parsed_word[k + 2] == "o" && parsed_word[p].parsed_word[k + 3] == "u" && parsed_word[p].parsed_word[k + 4] == "l" && parsed_word[p].parsed_word[k + 5] == "d" && (parsed_word[p].parsed_word[k + 6] == " " || parsed_word[p].parsed_word[k + 6] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "c" && parsed_word[p].parsed_word[k + 1] == "o" && parsed_word[p].parsed_word[k + 2] == "u" && parsed_word[p].parsed_word[k + 3] == "l" && parsed_word[p].parsed_word[k + 4] == "d" && (parsed_word[p].parsed_word[k + 5] == " " || parsed_word[p].parsed_word[k + 5] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "o" && parsed_word[p].parsed_word[k + 2] == "u" && parsed_word[p].parsed_word[k + 3] == "l" && parsed_word[p].parsed_word[k + 4] == "d" && (parsed_word[p].parsed_word[k + 5] == " " || parsed_word[p].parsed_word[k + 5] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "m" && parsed_word[p].parsed_word[k + 1] == "i" && parsed_word[p].parsed_word[k + 2] == "g" && parsed_word[p].parsed_word[k + 3] == "h" && parsed_word[p].parsed_word[k + 4] == "t" && (parsed_word[p].parsed_word[k + 5] == " " || parsed_word[p].parsed_word[k + 5] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "m" && parsed_word[p].parsed_word[k + 1] == "a" && parsed_word[p].parsed_word[k + 2] == "y" && parsed_word[p].parsed_word[k + 3] == "b" && parsed_word[p].parsed_word[k + 4] == "e" && (parsed_word[p].parsed_word[k + 5] == " " || parsed_word[p].parsed_word[k + 5] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "s" && parsed_word[p].parsed_word[k + 1] == "h" && parsed_word[p].parsed_word[k + 2] == "a" && parsed_word[p].parsed_word[k + 3] == "l" && parsed_word[p].parsed_word[k + 4] == "l" && (parsed_word[p].parsed_word[k + 5] == " " || parsed_word[p].parsed_word[k + 5] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			//!!!!
			else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "o" && parsed_word[p].parsed_word[k + 2] == "n" && parsed_word[p].parsed_word[k + 3] == "'" && parsed_word[p].parsed_word[k + 4] == "t" && (parsed_word[p].parsed_word[k + 5] == " " || parsed_word[p].parsed_word[k + 5] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "i" && parsed_word[p].parsed_word[k + 2] == "l" && parsed_word[p].parsed_word[k + 3] == "l" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "m" && parsed_word[p].parsed_word[k + 1] == "a" && parsed_word[p].parsed_word[k + 2] == "y" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "c" && parsed_word[p].parsed_word[k + 1] == "a" && parsed_word[p].parsed_word[k + 2] == "n" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 1;
				break;
			}
			//Other Auxiliares
			else if (parsed_word[p].parsed_word[k] == "h" && parsed_word[p].parsed_word[k + 1] == "a" && parsed_word[p].parsed_word[k + 2] == "v" && parsed_word[p].parsed_word[k + 3] == "e" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 0;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "h" && parsed_word[p].parsed_word[k + 1] == "a" && parsed_word[p].parsed_word[k + 2] == "d" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 0;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "h" && parsed_word[p].parsed_word[k + 1] == "a" && parsed_word[p].parsed_word[k + 2] == "s" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 0;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "b" && parsed_word[p].parsed_word[k + 1] == "e" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 0;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "i" && parsed_word[p].parsed_word[k + 1] == "s" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 0;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "a" && parsed_word[p].parsed_word[k + 1] == "m" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 0;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "a" && parsed_word[p].parsed_word[k + 2] == "s" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 0;
				break;
			}
			else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "e" && parsed_word[p].parsed_word[k + 2] == "r" && parsed_word[p].parsed_word[k + 3] == "e" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
			{
				parsed_word[p].syntantic_class = 'U';
				parsed_word[p].is_modal = 0;
				break;
			}
			else
			{
				//cout << "error 2";
			}

			//not included, hadn't, haven't, aren't, weren't, wasn't, isn't, ain't

			

		}

		if (parsed_word[p].syntantic_class == 'U')
		{
			word_tracker = word_tracker + 1;

			//auxiliaresTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);


		}
		else if (parsed_word[p].syntantic_class != 'U')
		{
			//cout << "Stubby";

			word_tracker = word_tracker;


			adverbTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);
			break;

		}




	}

	/*if (parsed_word[p].syntantic_class == 'U')
	{
		word_tracker = word_tracker + 1;

		auxiliaresTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);


	}
	else if (parsed_word[p].syntantic_class != 'U')
	{
		cout << "Stubby";

		word_tracker = word_tracker;

		
		adverbTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);

	}*/





}
void adverbTest(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker)
{
	int p = word_tracker;
	int k = 0;
	int repeater = 0;
	
		for (k = 0; k < parsed_word[p].length; k++)
		{
			if (parsed_word[p].parsed_word[k] == "y" && (parsed_word[p].parsed_word[k + 1] == " " || parsed_word[p].parsed_word[k + 1] == "\0"))
			{
				//cout << "Yaya";
				parsed_word[p].syntantic_class = 'Y';

			}
			/*else if ((parsed_word[p - 1].syntantic_class == 'N' || parsed_word[p - 1].syntantic_class == 'U') && parsed_word[p].syntantic_class == 'A')
			{
				//cout << "Ebeb";
				parsed_word[p].syntantic_class = 'Y';
			}*/

		}

		//idk if a string of adverbs is possible without a conjunction in the middle?
		if (parsed_word[p].syntantic_class == 'Y')
		{
			word_tracker = word_tracker + 1;
			
			verbTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);


		}
		else if (parsed_word[p].syntantic_class != 'Y')
		{
			word_tracker = word_tracker; //stays same
			

			
			verbTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);



		}


	

}


void verbTest(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker)
{

	parsed_word[word_tracker].syntantic_class = 'V';

	//word_tracker = word_tracker + 1;

	//adverbTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);



}

/*void verbphraseManager(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker)
{


}*/

//rechecks the sentence for errors
void checkAgain(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck)
{
	//turns on recheck mode
	recheck = 1;
	word_tracker = 0;

	//trying the other method










	
	//checking for pronouns  //solves for false nouns, but not false adjectives
	for (int p = word_tracker; p < num_of_words; p++)
	{
		if (parsed_word[p].syntantic_class == 'N')
		{
			//cout << "gaga";

			word_tracker = p;
			pronounTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);
			
			if (parsed_word[p].morphological_class != 'R')
			{
				//cout << "racha";

				//proper noun filter
				properNounFilter(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);

			}

		}

	}

	

}

//hunts for pronouns
void pronounTest(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck)
{
	int p = word_tracker;
	int k = 0;

	//i you he she it we they

	//nominative*******
	if (parsed_word[p].parsed_word[k] == "t"  && parsed_word[p].parsed_word[k + 1] == "h" && parsed_word[p].parsed_word[k + 2] == "e" && parsed_word[p].parsed_word[k + 3] == "y" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';
		parsed_word[p].grammatical_case = "nom";
		parsed_word[p].grammatical_gender = "net";
		parsed_word[p].number = "plu";
		parsed_word[p].person = "3rd";


	}
	else if (parsed_word[p].parsed_word[k] == "y" && parsed_word[p].parsed_word[k + 1] == "o" && parsed_word[p].parsed_word[k + 2] == "u" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';
		
		//********** Checks for ambiguous grammatical case ********
		if (p == 0)
		{
			parsed_word[p].grammatical_case = "nom";
		}
		else if (parsed_word[p - 1].syntantic_class == 'P')
		{
			parsed_word[p].grammatical_case = "dat";

		}
		else
		{
			parsed_word[p].grammatical_case = "acc";

		}
		//*********************************************

		parsed_word[p].grammatical_gender = "net";
		parsed_word[p].number = "sing";
		parsed_word[p].person = "2nd";

	}
	else if (parsed_word[p].parsed_word[k] == "s" && parsed_word[p].parsed_word[k + 1] == "h" && parsed_word[p].parsed_word[k + 2] == "e" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';
		parsed_word[p].grammatical_case = "nom";
		parsed_word[p].grammatical_gender = "fem";
		parsed_word[p].number = "sing";
		parsed_word[p].person = "3rd";

	}
	else if (parsed_word[p].parsed_word[k] == "h" && parsed_word[p].parsed_word[k + 1] == "e" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';
		parsed_word[p].grammatical_case = "nom";
		parsed_word[p].grammatical_gender = "masc";
		parsed_word[p].number = "sing";
		parsed_word[p].person = "3rd";

	}
	else if (parsed_word[p].parsed_word[k] == "i" && parsed_word[p].parsed_word[k + 1] == "t" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';
		
		//********** Checks for ambiguous grammatical case ********
		if (p == 0)
		{
			parsed_word[p].grammatical_case = "nom";
		}
		else if (parsed_word[p - 1].syntantic_class == 'P')
		{
			parsed_word[p].grammatical_case = "dat";

		}
		else
		{
			parsed_word[p].grammatical_case = "acc";

		}
		//*********************************************

		parsed_word[p].grammatical_gender = "net";
		parsed_word[p].number = "sing";
		parsed_word[p].person = "3rd";

	}
	else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "e" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';
		parsed_word[p].grammatical_case = "nom";
		parsed_word[p].grammatical_gender = "net";
		parsed_word[p].number = "plu";
		parsed_word[p].person = "1st";

	}
	else if (parsed_word[p].parsed_word[k] == "i" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';
		parsed_word[p].grammatical_case = "nom"; 
		parsed_word[p].grammatical_gender = "net";
		parsed_word[p].number = "sing";
		parsed_word[p].person = "1st";

	}
	//accusative or dative // me us you-- him her it-- them
	else if (parsed_word[p].parsed_word[k] == "t" && parsed_word[p].parsed_word[k + 1] == "h" && parsed_word[p].parsed_word[k + 2] == "e" && parsed_word[p].parsed_word[k + 3] == "m" && (parsed_word[p].parsed_word[k + 4] == " " || parsed_word[p].parsed_word[k + 4] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';
		
		if (parsed_word[p - 1].syntantic_class == 'P')
		{
			parsed_word[p].grammatical_case = "dat";
		}
		else
		{
			parsed_word[p].grammatical_case = "acc";

		}

		parsed_word[p].grammatical_gender = "net";
		parsed_word[p].number = "plu";
		parsed_word[p].person = "3rd";


	}
	else if (parsed_word[p].parsed_word[k] == "h" && parsed_word[p].parsed_word[k + 1] == "i" && parsed_word[p].parsed_word[k + 2] == "m" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';

		if (parsed_word[p - 1].syntantic_class == 'P')
		{
			parsed_word[p].grammatical_case = "dat";
		}
		else
		{
			parsed_word[p].grammatical_case = "acc";

		}

		parsed_word[p].grammatical_gender = "masc";
		parsed_word[p].number = "sing";
		parsed_word[p].person = "3rd";


	}
	else if (parsed_word[p].parsed_word[k] == "h" && parsed_word[p].parsed_word[k + 1] == "e" && parsed_word[p].parsed_word[k + 2] == "r" && (parsed_word[p].parsed_word[k + 3] == " " || parsed_word[p].parsed_word[k + 3] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';

		if (parsed_word[p - 1].syntantic_class == 'P')
		{
			parsed_word[p].grammatical_case = "dat";
		}
		else
		{
			parsed_word[p].grammatical_case = "acc";

		}

		parsed_word[p].grammatical_gender = "fem";
		parsed_word[p].number = "sing";
		parsed_word[p].person = "3rd";


	}
	else if (parsed_word[p].parsed_word[k] == "m" && parsed_word[p].parsed_word[k + 1] == "e" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';

		if (parsed_word[p - 1].syntantic_class == 'P')
		{
			parsed_word[p].grammatical_case = "dat";
		}
		else
		{
			parsed_word[p].grammatical_case = "acc";

		}

		parsed_word[p].grammatical_gender = "net";
		parsed_word[p].number = "sing";
		parsed_word[p].person = "1st";


	}
	else if (parsed_word[p].parsed_word[k] == "w" && parsed_word[p].parsed_word[k + 1] == "e" && (parsed_word[p].parsed_word[k + 2] == " " || parsed_word[p].parsed_word[k + 2] == "\0"))
	{
		parsed_word[p].syntantic_class = 'N';
		parsed_word[p].morphological_class = 'R';

		if (parsed_word[p - 1].syntantic_class == 'P')
		{
			parsed_word[p].grammatical_case = "dat";
		}
		else
		{
			parsed_word[p].grammatical_case = "acc";

		}

		parsed_word[p].grammatical_gender = "net";
		parsed_word[p].number = "plu";
		parsed_word[p].person = "1st";


	}
	else
	{
		word_tracker = word_tracker;

	}


}

void properNounFilter(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck)
{
	int num_of_nouns;

	//one way to check for errors is to see if the number (plurality or singular) of the
	// determiners matches with the supposed nouns

	//cout << word_tracker << " ddddd " << endl;
	//cout << num_of_words - word_tracker << endl ;

	int what_det = 0;
	int p = word_tracker;

	for (int r = 0; r < word_tracker; r++)
	{
		if (parsed_word[r].syntantic_class == 'D' && parsed_word[r].syntantic_class != 'P')
		{
			what_det = r;
			determinerFilter(sentence,  length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck, what_det);


			//sees if determiner and noun have agreement on number
			if (parsed_word[r].number != "xxx")
			{
				if (parsed_word[r].number == parsed_word[p].number )
				{
					
					parsed_word[p].syntantic_class = 'N';
					cout << "\n *** Noun and Determiner should have number agreement \n\n";


				}
				else if (parsed_word[r].number != parsed_word[p].number)
				{
					//add in an element to your structure telling grammaticallity
					//parsed_word[p].syntantic_class = 'X';
					cout << "\n *** Noun and Determiner should NOT have number agreement \n\n";

				}

			}
			else if (parsed_word[r].number == "xxx")
			{

				cout << "\n *** No agreement between Noun and Determiner exists, thus it can't be tested \n\n";
				//we first need to pull data about the noun from the nom case finder function
				// then we test for SV agreement
				//we can reuse this find nominative function for cases where we also don't have a determiner
				num_of_nouns = findNominativeCase(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);

			}

		}

	}


}
void determinerFilter(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck, int& what_det)
{
	int r = what_det;
	int p = word_tracker;

	//cout << r << " eekkekekekekekekekkekekek ";

	if (parsed_word[r].number == "plu")
	{
		//should check for plural in noun
		for (int k = 0; k < parsed_word[p].length; k++)
		{
			if (parsed_word[p].parsed_word[k] == "s" && (parsed_word[p].parsed_word[k + 1] == " " || parsed_word[p].parsed_word[k + 1] == "\0" ))
			{

				parsed_word[p].number = "plu";
				

			}
			//in the event the grammatical number of the determiner and noun do not match
			//then that noun is not truly a noun
			

		}

	}
	else if (parsed_word[r].number == "sing")
	{

		//should check for singular in noun
		//swapped rules of the previous
		for (int k = 0; k < parsed_word[p].length; k++)
		{
			if (parsed_word[p].parsed_word[k] != "s" && (parsed_word[p].parsed_word[k + 1] == " " || parsed_word[p].parsed_word[k + 1] == "\0"))
			{

				parsed_word[p].number = "sing";

			}
			//in the event the grammatical number of the determiner and noun do not match
			//then that noun is not truly a noun
			

		}

	}
	else if(parsed_word[r].number == "xxx")
	{
		parsed_word[p].number = "xxx";

	}
	


}

//finds the nominative case for propernouns via word order
int findNominativeCase(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck)
{
	int num_of_nouns = 0;  //used to talley the number of nouns within a sentence
	int num_of_nouns_before_verb = 0; // talley the number of nouns in the subject NP
	int temp_talley_1 = 0;
	int temp_talley_2 = 0;

	//what to do if there are more than four nouns in a sentence?
	for (int b = 0; b < num_of_words; b++)
	{
		if (parsed_word[b].syntantic_class == 'N')
		{
			num_of_nouns += 1;

		}
		if (parsed_word[b].syntantic_class == 'V')
		{
			num_of_nouns_before_verb = num_of_nouns;
			temp_talley_2 = temp_talley_1;

		}
		
		temp_talley_1++;

	}

	//for counting nouns before verb
	for (int b = 0; b < num_of_words; b++)
	{
		if (parsed_word[b].syntantic_class == 'N' && b < temp_talley_2)
		{
			parsed_word[b].grammatical_case = "nom";

		}
		else if (parsed_word[b].syntantic_class == 'N' && b >= temp_talley_2)
		{
			//cout << "check 1";

			for (int w = temp_talley_2; w < num_of_words; w++)
			{
				//cout << "check 2";

				//hunts for preps only before the noun in question
				if (parsed_word[w].syntantic_class == 'P' && w < b)
				{
					//cout << "check 3  "  << b ;

					parsed_word[b].grammatical_case = "dat";
					break;

				}
				else if(parsed_word[w].syntantic_class != 'P')
				{
					//cout << "check 4  ";


					parsed_word[b].grammatical_case = "acc";

				}


			}


		}

	}



	cout << "\n\n\n the number of nouns in the sentence is: " << num_of_nouns << endl;

	return num_of_nouns;
}


//to take the talley of syntactic classes
void syntacticTally(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, bool& recheck, int& noun_count, int& verb_count, int& adj_count, int& prep_count, int& det_count, int& aux_count, int& adv_count, bool& nvn_falsity, int& X_count)
{
	// in theory, I could have just crammed this inside the display function 
	// ie; display function also talleys when recheck is zero

	

	int noun_falsity = 0;
	int verb_falsity = 0;
	int verb_falsity_2 = 0;
	int break_point = 0; //where the verb head occurs
	bool saftey_switch = 0;

	//basic talley
	for (int b = 0; b < num_of_words; b++)
	{
		if (parsed_word[b].syntantic_class == 'N')
		{
			noun_count += 1;

			if (noun_count == 1)
			{
				noun_falsity = b;
			}
		}
		else if(parsed_word[b].syntantic_class == 'V')
		{
			verb_count += 1;

			if (verb_count == 1)
			{
				verb_falsity = b;
				break_point = b;
			}

			if (verb_count == 2)
			{
				verb_falsity_2 = b;
			}

		}
		else if (parsed_word[b].syntantic_class == 'A')
		{
			adj_count += 1;
		}
		else if (parsed_word[b].syntantic_class == 'P')
		{
			prep_count += 1;
		}
		else if (parsed_word[b].syntantic_class == 'D')
		{
			det_count += 1;
		}
		else if (parsed_word[b].syntantic_class == 'U')
		{
			aux_count += 1;
		}
		else if (parsed_word[b].syntantic_class == 'Y')
		{
			adv_count += 1;
		}
		else if (parsed_word[b].syntantic_class == 'X')
		{
			X_count += 1;
		}
		


	}

	cout << " \n\n\n_____________________\n\n";
	cout << "Tally of Syntactic Classes Present\n";
	cout << "Nouns: " << noun_count << endl;
	cout << "Verbs: " << verb_count << endl;
	cout << "Adjec: " << adj_count << endl;
	cout << "Preps: " << prep_count << endl;
	cout << "Dets : " << det_count << endl;
	cout << "Auxes: " << aux_count << endl;
	cout << "Advs : " << adv_count << endl;
	cout << "X count: " << X_count << endl << endl;
	cout << "Bre-Pnt: " << break_point << endl;

	//checks for NVNV error
	if (verb_count > 1)
	{

		
		if (parsed_word[verb_falsity + 1].syntantic_class == 'N' && parsed_word[verb_falsity - 1].syntantic_class == 'N')
		{
			word_tracker = noun_falsity + 1;

			for (int k = noun_falsity; k < num_of_words; k++)
			{
				parsed_word[k].syntantic_class = 'X';
			}

			nvn_falsity = 1;

			if (nvn_falsity == 1)
			{
				//cout << "Check 33";

				prepositionTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);
				int bvp = 0;

				for (bvp = 0; bvp < num_of_words; bvp++)
				{
					if (parsed_word[bvp].syntantic_class == 'N' && (parsed_word[bvp + 1].syntantic_class != 'P'))
					{
						word_tracker = bvp + 1;

						//cout << "ldldldldldldldldld";


						auxiliaresTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker);


					}

				}

			}

	

			/*
			//idk if this is the right spot

			if (parsed_word[num_of_words].syntantic_class == 'V' || parsed_word[num_of_words].syntantic_class == 'Y')
			{
				parsed_word[num_of_words].syntantic_class = 'X';

			}
			*/





           // this is the right spot

		   //check again again

			noun_count = 0;
			verb_count = 0;
			adj_count = 0;
			prep_count = 0;
			det_count = 0;
			aux_count = 0;
			adv_count = 0;
			X_count = 0;



			syntacticTally(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck, noun_count, verb_count, adj_count, prep_count, det_count, aux_count, adv_count, nvn_falsity, X_count);


	
		
		}

    
		//check again again
	    /*
		noun_count = 0;
		verb_count = 0;
		adj_count = 0;
		prep_count = 0;
		det_count = 0;
		aux_count = 0;
		adv_count = 0;
		X_count = 0;



		syntacticTally(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck, noun_count, verb_count, adj_count, prep_count, det_count, aux_count, adv_count, nvn_falsity, X_count);
		*/

	}

	//idk if this is the right spot
	if (verb_count > 1)
	{

		cout << " ppdppdp " << break_point << "  " << verb_falsity_2;


		for (int h = verb_falsity_2; h > break_point + 1; h--)
		{

			if (parsed_word[h].syntantic_class != 'D' && parsed_word[h].syntantic_class != 'P')
			{
				
				
				parsed_word[h].syntantic_class = 'X';

				//will label  the only verb as false if their are two adjectives in each NP
				
			}

			parsed_word[num_of_words - 1].syntantic_class = 'N';

		}
		

	}

	

	if (verb_count > 1)
	{
		noun_count = 0;
		verb_count = 0;
		adj_count = 0;
		prep_count = 0;
		det_count = 0;
		aux_count = 0;
		adv_count = 0;
		X_count = 0;




		syntacticTally(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck, noun_count, verb_count, adj_count, prep_count, det_count, aux_count, adv_count, nvn_falsity, X_count);

	}

	//cout << "  &*&#*&# " << break_point;
	//cout << recheck;
	

	/*if (X_count > 0)
	{
		recheck = 0;
	}*/


	//if (recheck == 0)
	//{
		fixingFalses(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, X_count, recheck, noun_count, verb_count, adj_count, prep_count, det_count, aux_count, adv_count, nvn_falsity);
	//}

	/*if (recheck == 1)
	{
		displayStats(length_with_spaces, length_no_spaces, num_of_words, parsed_word, recheck);

	}*/

}


//fixes the falses once they have been found
void fixingFalses(string sentence, int length_with_spaces, int  length_no_spaces, int num_of_words, Word parsed_word[], int& word_tracker, int& X_count, bool& recheck, int& noun_count, int& verb_count, int& adj_count, int& prep_count, int& det_count, int& aux_count, int& adv_count, bool& nvn_falsity)
{
	word_tracker = 0;
	bool switch_1 = 0;
	int cut_point = 0;
	int X_betwixt = 0;
	int stop_point = 0;
	bool switch_2 = 0;

	//cout << " check 99999";

	if (X_count > 0)
	{
		//changing falses to adjectives

		//for det first
		for (int g = 0; g < num_of_words; g++)
		{
			if (parsed_word[g].syntantic_class == 'D' && parsed_word[g + 1].syntantic_class == 'X')
			{

				cut_point = g;
				switch_1 = 1;
				break;
			}

		}

		if (switch_1)
		{
			cout << "check 66";

			for (int y = cut_point; y < num_of_words; y++)
			{
				if (parsed_word[y].syntantic_class == 'X')
				{
					X_betwixt += 1;

				}
				if (parsed_word[y].syntantic_class == 'N')
				{

					stop_point = y;
					break;

				}
				if (parsed_word[y].syntantic_class == 'P')
				{

					stop_point = y - 1;
					parsed_word[y - 1].syntantic_class = 'N';
					break;

				}


			}


			for (int k = cut_point; k < stop_point; k++)
			{
				if (parsed_word[k].syntantic_class == 'X')
				{
					parsed_word[k].syntantic_class = 'A';
				}


			}

			

		}

		//if no determiner first.... can only occur before verb. (actually this can happen afte the verb)
		int verb_point = 0;

		if (switch_1 == 0)
		{
			for (int p = 0; p < num_of_words; p++)
			{
				if (parsed_word[p].syntantic_class == 'V')
				{

					verb_point = p;
				}

			}

			//counts up the ass end
			for (int h = num_of_words - 1; h >= 0; h--)
			{
				if (parsed_word[h].syntantic_class == 'N' && parsed_word[h - 1].syntantic_class == 'X')
				{
					cut_point = h;
					switch_2 = 1;
					break;

				}

			}
		}

		if (switch_2)
		{
			cout << "  test check 47  ";

			/*for (int j = cut_point; j >= verb_point; j--)
			{
				if (parsed_word[j].syntantic_class == 'X')
				{

					parsed_word[j].syntantic_class = 'A';

				}


			}*/



		}


	}

	//incase of the N after N problem

	for (int r = 0; r < num_of_words; r++)
	{
		if (parsed_word[r].syntantic_class == 'N' && parsed_word[r + 1].syntantic_class == 'N')
		{
			//cout << " kdkdkdkdkd  check 990303";

			parsed_word[r].syntantic_class = 'A';

		}

	}

	//for false adverb or adjective at end of sentence
	if (parsed_word[num_of_words - 1].syntantic_class == 'A' || parsed_word[num_of_words - 1].syntantic_class == 'Y')
	{
		parsed_word[num_of_words - 1].syntantic_class = 'N';

	}

	//for standalone nouns
	if (parsed_word[num_of_words - 1].syntantic_class == 'D' && num_of_words != 1)
	{
		parsed_word[num_of_words - 1].syntantic_class = 'N';
	}

	//incase of falses between an adjective and a noun
	for (int t = 0; t < num_of_words; t++)
	{
		if (parsed_word[t].syntantic_class == 'X' && parsed_word[t - 1].syntantic_class == 'A' && parsed_word[t + 1].syntantic_class == 'N')
		{
			//cout << " \nhhigigigigigig\n " << t << parsed_word[t].syntantic_class;
			parsed_word[t].syntantic_class = 'A';
		}


	}

	//incase the verb is the lexeme TO BE  (as it is labelled as an Auxiliary by default)
	for (int f = 0; f < num_of_words; f++)
	{
		if (parsed_word[f].syntantic_class == 'U' && parsed_word[f].is_modal == 0)
		{
			recheck = 1;
			word_tracker = f + 1;
			prepositionTest(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck);
			
			if (parsed_word[f].syntantic_class == 'U' && parsed_word[f + 1].syntantic_class == 'P')
			{
				parsed_word[f].syntantic_class = 'V';
				

			}


			recheck = 0;
			f = 0;
			break;

		}
		

	}

	//incase it is a sentence with a commanding verb  (imperative mood)

	if (parsed_word[0].syntantic_class == 'X' && parsed_word[1].syntantic_class == 'D')
	{
		parsed_word[0].syntantic_class = 'V';
		parsed_word[0].mood = "imp";


	}



	//for things between prepositions


	//will have to run this function multiple times in case a fix causes more errors
	// that is fixed by a if-else statement that is above the one that did the original fix


	displayStats(length_with_spaces, length_no_spaces, num_of_words, parsed_word, recheck);

	/*
	recheck = 1;

	if (recheck == 1)
	{
		noun_count = 0;
		verb_count = 0;
		adj_count = 0;
		prep_count = 0;
		det_count = 0;
		aux_count = 0;
		adv_count = 0;
		X_count = 0;

		syntacticTally(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck, noun_count, verb_count, adj_count, prep_count, det_count, aux_count, adv_count, nvn_falsity, X_count);


	}
	*/



	//recount of X_count
	X_count = 0;

	for (int f = 0; f < num_of_words; f++)
	{
		if (parsed_word[f].syntantic_class == 'X')
		{
			X_count += 1;
		}

	}

	/*if (X_count > 0)
	{

		fixingFalses(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, X_count, recheck, noun_count, verb_count, adj_count, prep_count, det_count, aux_count, adv_count, nvn_falsity);

	}*/

	/*
	if (X_count > 0)
	{
		noun_count = 0;
		verb_count = 0;
		adj_count = 0;
		prep_count = 0;
		det_count = 0;
		aux_count = 0;
		adv_count = 0;
		X_count = 0;


		syntacticTally(sentence, length_with_spaces, length_no_spaces, num_of_words, parsed_word, word_tracker, recheck, noun_count, verb_count, adj_count, prep_count, det_count, aux_count, adv_count, nvn_falsity, X_count);
	}

	*/



}





