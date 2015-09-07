
#include "../common/common.h"

#include <time.h>


#define TESTMODE_ATOB 0
#define TESTMODE_BTOA 1
#define TESTMODE_BOTH 2

class CardDeck
{
	public:
		CardDeck(std::vector<string>);
		CardDeck(void);

		int importDeck(const char* myDeckFile);

		void displayDeck(void);
		void flashcardTestDefault(void);
		void flashcardTestRetry(void);
		int changeOperationMode(int mode);

	private:
		int operationMode;
		std::vector<std::vector<string> > wordlistIn;

		void _addCard(std::string myWordIn, std::string myWordOut);
};