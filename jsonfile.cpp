#include "json.h"
#include "utility.h"
#include <fstream>
#include <vector>
#include <map>

using namespace std;
namespace Json
{

void GetSeparateObjects(vector<string>& objects, string& s)
{
    int fin;
    for (int i=0; i<s.size(); i++)
    {
        if (s[i]=='{') fin = findNextBracket(s, i);
        if (fin==-1) throw "GetSeparateObjects";
        objects.push_back(s.substr(i+1, fin-i-1));
        checkObjectSyntax(objects.back());
        i = fin;
    }
}

JsonDict extractDict(string& s)
{
    JsonDict dict;
    for (auto& paire: split(s, ','))
    {
        auto cle_valeur = split(paire, ':');
        if (cle_valeur[0][0]!='"' || cle_valeur[0].back()!='"') throw invalid_argument(paire);
        if (cle_valeur.size()!=2) throw invalid_argument(paire);
        dict[cle_valeur[0]] = JsonValue(cle_valeur[1]);

    }
    return dict;
}

bool importJson(string filename, vector <JsonDict>& dicts)
{
    string json;
    vector <string> objects;
    ifstream file(filename.c_str());
    if (file)
    {for (string s; getline(file, s);)
    {
        removeSpaces(s);
        json += s;
    }
    GetSeparateObjects(objects, json);
    for (auto& object: objects)
    {
          dicts.push_back(extractDict(object));
    }
    }
    return file.is_open();

}
vector<JsonDict> importJson(string filename)
{
    string json;
    vector <string> objects;
    vector <JsonDict> dicts;
    ifstream file(filename.c_str());

    for (string s; getline(file, s);)
    {
        json += s;
    }
    removeSpaces(json);
    GetSeparateObjects(objects, json);
    for (auto& object: objects)
    {
          dicts.push_back(extractDict(object));
    }
    return dicts;
}

bool exportObject(JsonDict& dict, string filename, bool newline, int espace, bool ecraser)
{
    ofstream file(filename.c_str(), (ecraser)?ios::trunc:ios::app);
    if (file)
    {
    file << "{";
    if (newline) file << endl;
    for (auto& p : dict)
    {
        if (espace==-1) file << '\t';
        else file << nTimes(' ', espace);
        file << p.first << " : " << p.second;
        if (newline) file << endl;
    }
    if (newline) file << endl;
    file << "}";
    }
    return file.is_open();
}



}
