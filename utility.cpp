#include "utility.h"
using namespace std;
bool isNumber(string s)
{
    if (s.size()==0) return false;
    for (auto& c: s)
    {
        if (!isdigit(c) && c!='.') return false;
    }
    return true;
}

void removeSpaces(string& s)
{
    bool quote = false, doubleQuote = false;
    for (int i=0; i<s.size(); i++)
    {
        if (s[i]=='"' && !quote) doubleQuote = !doubleQuote;
        if (s[i]=="'"[0] && !doubleQuote) quote = !quote;
        if (!quote && !doubleQuote)
        {
            if (s[i]==' ' || s[i]=='\t')
            {
                s.erase(i, 1);
                i--;
            }
        }
    }
}

void removeEndl(string& s)
{
    bool quote = false, doubleQuote = false;
    for (int i=0; i<s.size(); i++)
    {
        if (s[i]=='"' && !quote) doubleQuote = !doubleQuote;
        if (s[i]=="'"[0] && !doubleQuote) quote = !quote;
        if (!quote && !doubleQuote)
        {
            if (s[i]=='\n')
            {
                s.erase(i, 1);
                i--;
            }
        }
    }
}

int findNextBracket(string& s, int pos)
{
    if (s[pos]!='{') return -1;
    int bracketCount = 1;
    for (int i=pos+1; i<s.size(); i++)
    {
        if (s[i]=='{') bracketCount++;
        if (s[i]=='}') bracketCount--;
        if (bracketCount==0) return i;
    }
    return -1;
}

int findNextComa(string& s, int pos)
{
    int comaCount = 1;
    bool entreGuillemets = false;
    for (int i=pos+1; i<s.size(); i++)
    {
        if (s[i]=='"' && !entreGuillemets) entreGuillemets=!entreGuillemets;
        if (s[i]=="'"[0] && !entreGuillemets) entreGuillemets=!entreGuillemets;
        if (s[i]==',' && !entreGuillemets) return i;
    }
    return -1;
}


vector <string> split(string& s, char sep)
{
    vector<string> v= {""};
    bool quote = false, doubleQuote = false;
    int crochets = 0, accolades = 0;
    for (auto& c:s)
    {
        if (c=='"' && !quote) doubleQuote = !doubleQuote;
        if (c=="'"[0] && !doubleQuote) quote = !quote;
        if (c=='[') crochets++;
        if (c==']') crochets--;
        if (c=='{') accolades++;
        if (c=='}') accolades--;
        if (c==sep && v.back()!="" && !quote && !doubleQuote && crochets==0 && accolades==0) v.push_back("");
        if (c!=sep || quote || doubleQuote) v.back()+=c;
    }
    if (v.back()=="") v.pop_back();
    return v;

}

string nTimes(char c, int nb)
{
    string s = "";
    for (int i = 0; i < nb; i++) s+= c;
    return s;
}
