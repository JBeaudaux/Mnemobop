#include <iostream>
#include <fstream>
#include <string>
#include <dirent.h>
#include <vector>
using namespace std;


bool listSelection(void)
{
    int i;
    DIR *dir;
    struct dirent *ent;
    std::string filename;

    std::vector<string> availableLists;
    availableLists.clear();

    std::ifstream infile;
    std::string myline;

    if((dir = opendir("./lists/")) != NULL)
    {
        // List all files in directory
        printf("Available flash-card lists :\n");
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
            cout << "\t" << i+1 << ") " << availableLists[i] << endl;
        }

        do
        {
            cin >> i;

            if(i<=availableLists.size() && i>0)
            {
                infile.open(availableLists[i-1].c_str());

                if(infile.is_open() == true)
                {
                    cout << "List opened : " << availableLists[i-1].c_str() << endl;
                }
                else
                {
                    cout << "Failed to open list : " << availableLists[i-1].c_str() << endl;
                }
            }
            else
            {
                cout << "Bad file ID entered : " << i << endl;
            }
        }while(infile.is_open() == false);

        while(getline(infile, myline))
        {
            cout << myline << endl;
        }
        
        infile.close();

        return true;
    }
    else
    {
        /// Failed to open directory
        //perror ("");
        cout << "ERROR: Failed to open lists directory" << endl;

        return false;
    }
}


int main()
{
    listSelection();

    return 0;
}