#include "carddeck.h"


class CardDeck
{
	std::vector<string> wordlistIn;

	public:
		CardDeck(std::vector<string>);
		CardDeck(void);
		bool addCard(char* myWordIn, char* myWordOut);

};

CardDeck(std::vector<string>)
{
	printf("String vector constructor\n");
}

CardDeck(void)
{
	printf("Void constructor\n");
}

bool addCard(char* myWordIn, char* myWordOut)
{

}