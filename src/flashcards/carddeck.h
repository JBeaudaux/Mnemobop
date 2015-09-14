
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
		
		std::string getWord(void);
		std::string getAnswer(void);
		void removeFromDeck(void);
		void duplicateInDeck(void);
		int remainingWords(void);

	private:
		int operationMode;

		static int questionID;
		static int wayID;

		std::vector<std::vector<string> > wordlistIn;

		void _addCard(std::string myWordIn, std::string myWordOut);
};