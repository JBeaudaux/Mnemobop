#include "common.h"
#include "mnemobop_def.h"

#include "carddeck.h"


/**
 * @brief Lists the flash-cards packets, and open the selected one
 * @return true if the file containing flash-cards was successfully opened
 * @return false otherwise
 */
static bool _listSelection(void)
{
    unsigned int i;
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

        for(i=0; i<availableLists.size(); i++)
        {
            printf(""YELLOW"\t%d) %s"NORMAL"\n", i+1, availableLists[i].c_str());
        }

        do
        {
            cin >> i;

            if(i>availableLists.size() || i<=0)
            {
                printf(""RED"Bad file ID entered : %d "NORMAL"\n", i);
            }
            else
            {
                _fillFlashCard(availableLists[i-1].c_str());
            }
        }while(i>availableLists.size() || i<=0);

        return true;
    }
    else
    {
        /// Failed to open directory
        perror(""RED"The following error occurred : "NORMAL"");
        //printf(""RED"ERROR: Failed to open lists directory%s "NORMAL"\n", availableLists[i-1].c_str());

        return false;
    }
}

static bool _fillFlashCard(const char* myDeckFile)
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

                printf(""YELLOW"New flash-card : In %s , Out %s"NORMAL"\n", sublines[0].c_str(), sublines[1].c_str());
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


int main(void)
{
    //CardDeck foo();
    _listSelection();

    return 0;
}