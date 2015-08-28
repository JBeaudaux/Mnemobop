
#include "common.h"


#define TESTMODE_ATOB 0
#define TESTMODE_BTOA 1
#define TESTMODE_BOTH 2

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
		void flashcardTestDefault(int mode);
		void flashcardTestRetry(int mode);
};