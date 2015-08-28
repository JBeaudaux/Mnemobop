
#include <vector>
#include <string>
#include <sstream>

#include <iostream>
#include <fstream>

#include <dirent.h>

#include <stdlib.h>

using namespace std;

#define NORMAL    "\x1B[0m"
#define RED       "\x1B[31m"
#define GREEN     "\x1B[32m"
#define YELLOW    "\x1B[33m"
#define BLUE      "\x1B[34m"
#define MAGENTA   "\x1B[35m"
#define CYAN      "\x1B[36m"
#define WHITE     "\x1B[37m"

#define BLACKBOLD "\033[1m"
#define REDBOLD   "\033[31m"


std::vector<std::string> mySplit(const std::string &s, char delim, std::vector<std::string> &elems);

std::vector<std::string> splitString(const std::string &s, char delim);