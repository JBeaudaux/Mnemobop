
#include "common.h"

class CardDeck
{
	std::vector<std::vector<string> > wordlistIn;

	public:
		//Constructors
		CardDeck(std::vector<string>);
		CardDeck(void);

		//Other methods
		void addCard(std::string myWordIn, std::string myWordOut);
		void displayDeck(void);
		void defaultFlashcardTest(void);
};