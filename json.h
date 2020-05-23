#include <iostream>
#include <string>
#include <exception>
#include <memory>
#include <vector>
#include <map>
#ifndef JSON_H_INCLUDED
#define JSON_H_INCLUDED
using std::string;
using std::map;
using std::vector;
using std::ostream;

namespace Json
{
const int NUMBER = 0;
const int STRING = 1;
const int BOOLEAN = 2;
const int JSON_NULL = 3;
const int ARRAY = 4;
const int OBJECT = 5;

class JsonValue;
using JsonDict = map<string, JsonValue>;
class JsonValue
{
public:
    JsonValue();
    JsonValue(const char*);
    JsonValue(string);
    JsonValue(double);
    JsonValue(bool);
    const int get_type() const;
    const string to_string() const;

    operator double() const;
    operator bool() const;
    operator vector<JsonValue>();

private:
    static const JsonValue null;
    string value;
    int type;
    bool boolean;
    double number;

};


class TypeError: public std::exception
{
public:
    TypeError(int from = -1, int to = -1);
    virtual const char* what() const noexcept;
private:
    int typeFrom, typeTo;
    string message;
};

ostream& operator << (ostream&, JsonValue&);

/**
Prends en paramètre le chemin du json et
un vecteur de dictionnaires pour stocker les objets.
Renvoie true si le fichier a pu être lu*/
bool importJson(string, vector <JsonDict>&);

/**
Prend en paramètre le chemin du json
et retourne un vector de dictionnaires (JsonDict)
contenant les objets*/
vector<JsonDict> importJson(string);
/**
newline : ajouter un retour a la ligne. espace : indentation. ecraser : remplacer un fichier existant ou pas.*/
bool exportObject(JsonDict& dict, string filename, bool newline=true, int espace = -1, bool ecraser = false);
}
#endif // JSON_H_INCLUDED
