#include "carddeck.h"

CardDeck::CardDeck(std::vector<std::string> myDeck)
{
	CardDeck::operationMode = TESTMODE_BOTH;
}

CardDeck::CardDeck()
{
	CardDeck::operationMode = TESTMODE_BOTH;
}

/**
 * @brief Randomly selects words in the deck to translate.
 * 	      If correctly answered, a word is removed from the deck.
 *
 * @param myDeckFile Name of the file containing the words list to import.
 *
 * @return -1 if imort was unsuccessful, the number of imported words otherwise
 */
int CardDeck::importDeck(const char* myDeckFile)
{
	std::string myline;
	std::ifstream infile;
	vector<std::string> sublines;
	int resLines = 0; //Number of lines

	infile.open(myDeckFile);

	if(infile.is_open() == true)
	{
		printf(""GREEN"List opened : %s "NORMAL"\n", myDeckFile);

		while(getline(infile, myline))
		{
			resLines += 1;

			sublines = splitString(myline, ' ');
			if(sublines.size() != 2)
			{
				printf(""RED"Incorrect flash-card list format"NORMAL"\n");

				infile.close();
				return false;
			}
			else
			{
				/// Fill here FlashDeck filler
				CardDeck::_addCard(sublines[0], sublines[1]);
			}
		}

		printf(""GREEN"New flash-card deck successfully imported"NORMAL"\n");
	}
	else
	{
		printf(""RED"Failed to open list : %s "NORMAL"\n", myDeckFile);
		infile.close();

		return -1;
	}

	return resLines;
}

void CardDeck::_addCard(std::string myWordIn, std::string myWordOut)
{
	std::vector<string> myWord;

	myWord.push_back(myWordIn);
	myWord.push_back(myWordOut);

	wordlistIn.push_back(myWord);

	printf(""YELLOW"New flash-card word added (%ld)"NORMAL"\n", wordlistIn.size());
}


/**
 * @brief Displays the current content of the flash-card deck.
 */
void CardDeck::displayDeck(void)
{
	unsigned int i;

	printf(""BLUE"Deck display (%ld):"NORMAL"\n", wordlistIn.size());

	for(i=0; i<wordlistIn.size(); i++)
	{
		printf(""BLUE"\t%d) In %s , Out %s"NORMAL"\n", i, wordlistIn[i][0].c_str(), wordlistIn[i][1].c_str());
	}
}


/**
 * @brief Randomly selects words in the deck to translate.
 * 	      If correctly answered, a word is removed from the deck.
 */
void CardDeck::flashcardTestDefault(void)
{
	int mistakes = 0;
	int randomNmb, randomWay;
	std::string givenWord;

	srand(time(NULL));

	while(wordlistIn.size() > 0)
	{
		randomNmb = rand() % wordlistIn.size();

		if(CardDeck::operationMode == TESTMODE_ATOB || CardDeck::operationMode == TESTMODE_BTOA)
		{
			randomWay = CardDeck::operationMode;
		}
		else
		{
			randomWay = rand() % 2;
		}

		printf(""BLUE"What is the translation for : %s"NORMAL"\n", wordlistIn[randomNmb][randomWay].c_str());

		cin >> givenWord;
		if(givenWord == wordlistIn[randomNmb][!randomWay])
		{
			wordlistIn.erase(wordlistIn.begin() + randomNmb);
			printf(""GREEN"Correct :-D"NORMAL"\n\n");
		}
		else
		{
			mistakes+=1;
			printf(""RED"Incorrect :'("NORMAL"\n");
		}
	}

	printf(""GREEN"Congratulations, you have completed this deck! You made %d mistakes"NORMAL"\n", mistakes);
}

/**
 * @brief Randomly selects words in the deck to translate (both A->B and B->A).
 * 	      If correctly answered, a word is removed from the deck. Otherwise, a word duplicate is added to the deck.
 */
void CardDeck::flashcardTestRetry(void)
{
	int mistakes = 0;
	int randomNmb, randomWay;
	std::string givenWord;

	std::vector<string> myWord;

	srand(time(NULL));

	while(wordlistIn.size() > 0)
	{
		randomNmb = rand() % wordlistIn.size();
		randomWay = rand() % 2;

		printf(""BLUE"What is the translation for : %s"NORMAL"\n", wordlistIn[randomNmb][randomWay].c_str());

		cin >> givenWord;
		if(givenWord == wordlistIn[randomNmb][!randomWay])
		{
			wordlistIn.erase(wordlistIn.begin() + randomNmb);
			printf(""GREEN"Correct :-D"NORMAL"\n\n");
		}
		else
		{
			mistakes+=1;

			myWord.push_back(wordlistIn[randomNmb][0]);
			myWord.push_back(wordlistIn[randomNmb][1]);
			wordlistIn.push_back(myWord);

			printf(""RED"Incorrect :'("NORMAL"\n");
		}
	}

	printf(""GREEN"Congratulations, you have completed this deck! You made %d mistakes"NORMAL"\n", mistakes);
}


/**
 * @brief Changes the mode of operation of the program.
 * @param mode The operation mode (AtoB, BtoA or both)
 */
int CardDeck::changeOperationMode(int mode)
{
	if(mode < 0 || mode > TESTMODE_BOTH)
	{
		return -1;
	}
	else
	{
		CardDeck::operationMode = mode;
		return mode;
	}
}