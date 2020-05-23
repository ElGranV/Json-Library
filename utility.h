#ifndef UTILITY_H_INCLUDED
#define UTILITY_H_INCLUDED
#include <vector>
#include <string>

using std::vector;
using std::string;

bool isNumber(string);
void removeSpaces(string&);
void removeEndl(string&);
int findNextBracket(string&, int);
//int findNextComa(string&, int);
vector <string> split(string&,char sep = ' ');
string espace(char, int);
string nTimes(char c, int nb);
void checkObjectSyntax(string&);
#endif // UTILITY_H_INCLUDED
