#include "carddeck.h"
#include "common.h"

#include <time.h>

CardDeck::CardDeck(std::vector<std::string> myDeck)
{
	printf("String vector constructor\n");
}

CardDeck::CardDeck()
{
	printf("Void constructor\n");
}

void CardDeck::addCard(std::string myWordIn, std::string myWordOut)
{
	std::vector<string> myWord;
	
	myWord.push_back(myWordIn);
	myWord.push_back(myWordOut);

	wordlistIn.push_back(myWord);

	printf(""YELLOW"New flash-card word (%ld): In %s , Out %s"NORMAL"\n", wordlistIn.size(),
		wordlistIn[wordlistIn.size()-1][0].c_str(), wordlistIn[wordlistIn.size()-1][1].c_str());
}

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
 * @brief Randomly selects words in the deck to translate (both A->B and B->A) 
 */
void CardDeck::defaultFlashcardTest(void)
{
	int mistakes = 0;
	int randomNmb, randomWay;
	std::string givenWord;

	srand(time(NULL));

	while(wordlistIn.size() > 0)
	{
		randomNmb = rand() % wordlistIn.size();
		randomWay = rand() % 2;

		printf("What is the translation for : %s\n", wordlistIn[randomNmb][randomWay].c_str());

		cin >> givenWord;
		if(givenWord == wordlistIn[randomNmb][!randomWay])
		{
			wordlistIn.erase(wordlistIn.begin() + randomNmb);
			printf("Correct :-D\n\n");
		}
		else
		{
			mistakes+=1;
			printf("Incorrect :'(\n");
		}
	}

	printf("Congratulations, you have completed this deck! You made %d mistakes\n", mistakes);
}