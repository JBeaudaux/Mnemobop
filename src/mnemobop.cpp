#include "common/common.h"
#include "mnemobop_def.h"

#include "flashcards/carddeck.h"


/**
 * @brief Lists the flash-cards packets, and request one to load
 * @return a string containing the requested filename if successfull
 * @return an empty string otherwise
 */
std::string _listSelection(void)
{
    unsigned int i, iter = 0;

    DIR *dir;
    struct dirent *ent;
    std::string filename;

    std::vector<string> availableLists;
    availableLists.clear();

    std::ifstream infile;

    if((dir = opendir("./lists/")) != NULL)
    {
        // List all files in directory
        printf(""YELLOW"Available flash-card lists :"NORMAL"\n");
        while ((ent = readdir (dir)) != NULL)
        {
            if(ent->d_name[0] != '.')
            {
                availableLists.push_back(string("lists/") + string(ent->d_name));
            }
        }
        closedir (dir);

        if(availableLists.size() == 0)
        {
            printf(""RED"No available flash-card list"NORMAL"\n");
            return "";
        }

        for(i=0; i<availableLists.size(); i++)
        {
            printf(""YELLOW"\t%d) %s"NORMAL"\n", i+1, availableLists[i].c_str());
        }

        do
        {
            cin >> i;

            //3 attemps before error
            if(iter++ >= 3)
            {
                printf(""RED"Failed to load a list"NORMAL"\n");

                return "";
            }

            if(i>availableLists.size() || i<=0)
            {
                printf(""RED"Bad file ID entered : %d "NORMAL"\n", i);
            }
            else
            {
                return availableLists[i-1];
                //_fillFlashCard(availableLists[i-1].c_str());
            }
        }while(i>availableLists.size() || i<=0);

    }
    else
    {
        /// Failed to open directory
        perror(""RED"The following error occurred : "NORMAL"");
        //printf(""RED"ERROR: Failed to open lists directory%s "NORMAL"\n", availableLists[i-1].c_str());

        return "";
    }

    return "";
}

/**
 * @brief From a given file, extracts the information to import a new flash-card deck.
 * @return true if the new flash-card deck was successfully filled
 * @return false otherwise
 */
bool _fillFlashCard(const char* myDeckFile, CardDeck& myCardDeck)
{
    std::string myline;
    std::ifstream infile;
    vector<std::string> sublines;

    infile.open(myDeckFile);

    if(infile.is_open() == true)
    {
        printf(""GREEN"List opened : %s "NORMAL"\n", myDeckFile);

        while(getline(infile, myline))
        {
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
                myCardDeck.addCard(sublines[0], sublines[1]);
            }
        }

        printf(""GREEN"New flash-card deck successfully imported"NORMAL"\n");
    }
    else
    {
        printf(""RED"Failed to open list : %s "NORMAL"\n", myDeckFile);
    }

    infile.close();

    return true;
}


int main(int argc, char* argv[])
{
    CardDeck cards;
    std::string filename;

    int operationMode = TESTMODE_BOTH;

    if(argc > 2)
    {
        printf(""RED"USAGE: %s OPMODE "NORMAL"\n", argv[0]);
        return -1;
    }

    if(argc == 2)
    {
        if(strcmp(argv[1], "AtoB") == 0)
        {
            operationMode = TESTMODE_ATOB;
        }
        else if(strcmp(argv[1], "BtoA") == 0)
        {
            operationMode = TESTMODE_BTOA;
        }
        else
        {
            printf(""RED"USAGE: %s OPMODE "NORMAL"\n", argv[0]);
            return -1;
        }
    }

    std::cout << argv[1] << std::endl;

    filename = _listSelection();

    if(filename != "")
    {
        _fillFlashCard(filename.c_str(), cards);

        //cards.displayDeck();

        cards.flashcardTestRetry(operationMode);
    }

    return 0;
}