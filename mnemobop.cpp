#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string const inFileName("./lists/TestList.data");
    std::string myline;

    //vector<vector<int> > wordList;

    std::ifstream infile(inFileName.c_str());

    if(infile)
    {
        while(getline(infile, myline))
        {
            cout << myline << endl;
        }
    }
    else
    {
        cout << "ERREUR: Impossible d'ouvrir le fichier." << endl;
    }

    infile.close();

    return 0;
}